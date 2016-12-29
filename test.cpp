// #include <iostream>
#include <cstdio>
#include <string>
#include "SimpleJsonEmitter.hpp"

using namespace std;
using SimpleJsonEmitter::JsonStreamEmitter;
using SimpleJsonEmitter::SimpleJsonEmitterBase;

class PrintfJsonEmitter : public SimpleJsonEmitterBase
{
    public:
    void WriteJson(string const json) override;
    PrintfJsonEmitter(void);
};

void PrintfJsonEmitter::WriteJson(string const json)
{
    std::printf("%s", json.c_str());
}

PrintfJsonEmitter::PrintfJsonEmitter(void) : SimpleJsonEmitterBase()
{

}

int main(int argc, char **argv)
{
    JsonStreamEmitter jsonEmitter(cout);
    jsonEmitter.SetPrettyPrint(true);
    string key = "string key";
    string val = "string value";
    jsonEmitter.StartDict();
    jsonEmitter.Emit(key, val);
    jsonEmitter.Emit<string>("other key", "other value");
    jsonEmitter.Emit("key for int", 311459);
    jsonEmitter.StartArray("an array");

    for (int i = 0; i < 4000000000; i++)
    {
        jsonEmitter.Emit(i);
    }

    jsonEmitter.EndArray();
    jsonEmitter.EndDict();

    cout << endl;
    return 0;
}