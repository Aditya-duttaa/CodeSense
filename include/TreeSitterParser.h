#pragma once

#include <string>
#include <vector>

using namespace std;

struct ParsedFunction
{
    string name;
    string file;
    string code;
    int startLine;
    int endLine;
};

class TreeSitterParser
{
public:
    vector<ParsedFunction> parseFile(const string& path);
};