#include "SymbolTable.h"
#include <iostream>
#include <sstream>
using namespace std;

SymbolEntry::SymbolEntry(Type *type, int kind) 
{
    this->type = type;
    this->kind = kind;
}
SymbolEntry::SymbolEntry(Type *type, int kind, bool is_const) 
{
    this->type = type;
    this->kind = kind;
    this->is_const=is_const;
}

ConstantSymbolEntry::ConstantSymbolEntry(Type *type, int value) : SymbolEntry(type, SymbolEntry::CONSTANT)
{
    this->ivalue = value;
}
ConstantSymbolEntry::ConstantSymbolEntry(Type *type, float value) : SymbolEntry(type, SymbolEntry::CONSTANT)
{
    this->fvalue = value;
}

std::string ConstantSymbolEntry::toStr()
{
    std::ostringstream buffer;
    buffer << ivalue;
    return buffer.str();
}
std::string ConstantSymbolEntry::toStrf()
{
    std::ostringstream buffer;
    buffer << fvalue;
    return buffer.str();
}

IdentifierSymbolEntry::IdentifierSymbolEntry(Type *type, std::string name, int scope) : SymbolEntry(type, SymbolEntry::VARIABLE), name(name)
{
    this->scope = scope;
}
IdentifierSymbolEntry::IdentifierSymbolEntry(Type *type, std::string name, int scope, bool is_const) : SymbolEntry(type, SymbolEntry::VARIABLE, is_const), name(name)
{
    this->scope = scope;
}
std::string IdentifierSymbolEntry::toStr()
{
    return name;
}
std::string IdentifierSymbolEntry::toStrf()
{
    return name;
}
TemporarySymbolEntry::TemporarySymbolEntry(Type *type, int label) : SymbolEntry(type, SymbolEntry::TEMPORARY)
{
    this->label = label;
}

std::string TemporarySymbolEntry::toStr()
{
    std::ostringstream buffer;
    buffer << "t" << label;
    return buffer.str();
}
std::string TemporarySymbolEntry::toStrf()
{
    std::ostringstream buffer;
    buffer << "t" << label;
    return buffer.str();
}
SymbolTable::SymbolTable()
{
    prev = nullptr;
    level = 0;
}

SymbolTable::SymbolTable(SymbolTable *prev)
{
    this->prev = prev;
    this->level = prev->level + 1;
}

/*
    Description: lookup the symbol entry of an identifier in the symbol table
    Parameters: 
        name: identifier name
    Return: pointer to the symbol entry of the identifier

    hint:
    1. The symbol table is a stack. The top of the stack contains symbol entries in the current scope.
    2. Search the entry in the current symbol table at first.
    3. If it's not in the current table, search it in previous ones(along the 'prev' link).
    4. If you find the entry, return it.
    5. If you can't find it in all symbol tables, return nullptr.
*/
ConstIdentifierSymbolEntry::ConstIdentifierSymbolEntry(Type *type, std::string name, int scope) : SymbolEntry(type, SymbolEntry::VARIABLE), name(name)
{
    this->scope = scope;
}
ConstIdentifierSymbolEntry::ConstIdentifierSymbolEntry(Type *type, std::string name, int scope, bool is_const) : SymbolEntry(type, SymbolEntry::VARIABLE, is_const), name(name)
{
    this->scope = scope;
}
std::string ConstIdentifierSymbolEntry::toStr()
{
    return name;
}
std::string ConstIdentifierSymbolEntry::toStrf()
{
    return name;
}



SymbolEntry* SymbolTable::lookup(std::string name)
{
    SymbolTable* currentTable = this;

    while (currentTable)
    {
        // Search the entry in the current symbol table.
        auto it = currentTable->symbolTable.find(name);
        if (it != currentTable->symbolTable.end())
        {
            return it->second;
        }

        // Move to the previous table.
        currentTable = currentTable->prev;
    }
    //
    // If we've gone through all tables and haven't found the symbol, return nullptr.
    return nullptr;
}


// install the entry into current symbol table.
void SymbolTable::install(std::string name, SymbolEntry* entry)
{
   // std::cout << "Installing " << name << " in " << this << std::endl;
    symbolTable[name] = entry;
}

int SymbolTable::counter = 0;
static SymbolTable t;
SymbolTable *identifiers = &t;
SymbolTable *globals = &t;
SymbolTable *constidentifiers = &t;
