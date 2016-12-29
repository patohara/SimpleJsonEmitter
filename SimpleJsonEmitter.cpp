#include <string>
#include <iostream>
#include <stack>

#include "SimpleJsonEmitter.hpp"

using std::string;

namespace SimpleJsonEmitter
{

template<>
string JsonEncode<int>(int const value)
{
    return std::to_string(value);
}

template<>
string JsonEncode<uint>(uint const value)
{
    return std::to_string(value);
}

template<>
string JsonEncode<float>(float const value)
{
    return std::to_string(value);
}

template<>
string JsonEncode<double>(double const value)
{
    return std::to_string(value);
}

template<>
string JsonEncode<string>(string const value)
{
    string jsonValue = "\"";

    for (int i = 0; i < value.length(); i++)
    {
        char c = value[i];

        switch (c)
        {
            case '\n':
                jsonValue += "\\n";
                break;
            case '\f':
                jsonValue += "\\f";
                break;
            case '\b':
                jsonValue += "\\b";
                break;
            case '\r':
                jsonValue += "\\r";
                break;
            case '"':
                jsonValue += "\\\"";
                break;
            case '\\':
                jsonValue += "\\\\";
                break;
            default:
                jsonValue += c;
                break;
        }
    }

    jsonValue += "\"";
    return jsonValue;
}

SimpleJsonEmitterBase::SimpleJsonEmitterBase(void) : itemCounts(), prettyPrint(false), indentLevel(0)
{
    this->itemCounts.push(0);
}

void SimpleJsonEmitterBase::StartObject(const string openingToken)
{
    this->WriteWithComma(openingToken);
    this->Indent();

    if (this->prettyPrint)
    {
        this->WriteJson("\n");
    }

    this->itemCounts.push(0);
}

void SimpleJsonEmitterBase::StartObject(const string name, const string openingToken)
{
    this->WriteWithComma(JsonEncode(name));

    if (this->prettyPrint)
    {
        this->WriteJson(": " + openingToken);
    }
    else
    {
        this->WriteJson(":" + openingToken);
    }

    this->Indent();

    if (this->prettyPrint)
    {
        this->WriteJson("\n");
    }

    this->itemCounts.push(0);
}

void SimpleJsonEmitterBase::EndObject(const string closingToken)
{
    this->Dedent();

    if (this->prettyPrint)
    {
        this->WriteJson("\n");
        this->WriteIndent();
    }

    this->WriteJson(closingToken);
    this->itemCounts.pop();
}

void SimpleJsonEmitterBase::WriteWithComma(const string json)
{
    int numItems = this->itemCounts.top();

    if (numItems > 0)
    {
        if (this->prettyPrint)
        {
            this->WriteJson(",\n");
        }
        else
        {
            this->WriteJson(",");
        }
    }

    if (this->prettyPrint)
    {
        this->WriteIndent();
    }

    this->WriteJson(json);
    ++numItems;
    this->itemCounts.pop();
    this->itemCounts.push(numItems);
}

using namespace std;

JsonStreamEmitter::JsonStreamEmitter(std::ostream& outStream) : SimpleJsonEmitterBase(), outStream(outStream)
{
}

void JsonStreamEmitter::WriteJson(const string json)
{
    this->outStream << json;
}

}