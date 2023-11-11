#include "Type.h"
#include <sstream>

IntType TypeSystem::commonInt = IntType(4);
VoidType TypeSystem::commonVoid = VoidType();
FloatType TypeSystem::commonFloat = FloatType(4);
CharType TypeSystem::commonChar = CharType(1);

Type* TypeSystem::intType = &commonInt;
Type* TypeSystem::voidType = &commonVoid;
Type* TypeSystem::floatType = &commonFloat;
Type* TypeSystem::charType = &commonChar;

std::string IntType::toStr()
{
    return "int";
}
std::string FloatType::toStr()
{
    return "float";
}
std::string CharType::toStr()
{
    return "char";
}
std::string ArrayType::toStr()
{
    return "array";
}
std::string VoidType::toStr()
{
    return "void";
}

std::string FunctionType::toStr()
{
    std::ostringstream buffer;
    buffer << returnType->toStr() << "()";
    return buffer.str();
}
void FunctionType::SetParamsType(std::vector<Type*> in)
{
    paramsType = in;
}
