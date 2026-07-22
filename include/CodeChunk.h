#pragma once

#include <string>

using namespace std;

struct CodeChunk
{
    string filePath;
    string symbolName;
    string code;
    int startLine;
    int endLine;
};