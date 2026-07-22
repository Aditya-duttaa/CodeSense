#pragma once

#include <string>
#include <vector>

using namespace std;

struct FunctionInfo
{
    string name;
    string file;
    string code;

    int startLine;
    int endLine;
};

class FunctionDatabase
{
public:
    static vector<FunctionInfo> load(const string& filename);
};