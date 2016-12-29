#include <string>
#include <iostream>
#include <stack>

#pragma once

using std::string;

namespace SimpleJsonEmitter
{

/**
 * Encodes the given value as JSON.
 * @typename T Type of parameter to encode.
 * @param value Value to be encoded.
 * @return The string representing the encoded JSON value.
 */
template<typename T>
string JsonEncode(T const value);

class SimpleJsonEmitterBase
{
    protected:
    int indentLevel;
    bool prettyPrint;
    std::stack<int> itemCounts;
    
    inline void Indent(void)
    {
        ++this->indentLevel;
    }

    inline void Dedent(void)
    {
        if (this->indentLevel > 0)
        {
            --this->indentLevel;
        }
    }

    inline void WriteIndent(void)
    {
        for (int i = 0; i < this->indentLevel; i++)
        {
            this->WriteJson("\t");
        }
    }

    template<typename T>
    string EncodePair(string const name, T const value) const
    {
        string json = JsonEncode(name);
        
        if (this->prettyPrint)
        {
            json += ": ";
        }
        else
        {
            json += ":";
        }

        json += JsonEncode<T>(value);

        return json;
    }

    void StartObject(const string openingToken);
    void StartObject(const string name, const string openingToken);
    void EndObject(const string closingToken);
    void WriteWithComma(const string json);
    
    public:
    SimpleJsonEmitterBase(void);
    virtual void WriteJson(const string json) = 0;
    int GetIndentLevel(void) const
    {
        return this->indentLevel;
    }

    template <typename T>
    void Emit(const T value)
    {
        this->WriteWithComma(JsonEncode<T>(value));
    }

    template <typename T>
    void Emit(const string name, const T value)
    {
        this->WriteWithComma(this->EncodePair(name, value));
    }

    inline void SetPrettyPrint(bool doPrettyPrint)
    {
        this->prettyPrint = doPrettyPrint;
    }

    inline void StartDict(void)
    {
        this->StartObject("{");
    }

    inline void StartDict(const string name)
    {
        this->StartObject(name, "{");
    }

    inline void EndDict(void)
    {
        this->EndObject("}");
    }

    inline void StartArray(void)
    {
        this->StartObject("[");
    }

    inline void StartArray(const string name)
    {
        this->StartObject(name, "[");
    }

    inline void EndArray(void)
    {
        this->EndObject("]");
    }
};

class JsonStreamEmitter : public SimpleJsonEmitterBase
{
    private:
    std::ostream& outStream;
    protected:
    
    public:
    JsonStreamEmitter(std::ostream& outStream);
    void WriteJson(const string json) override;
};

}