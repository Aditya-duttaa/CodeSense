#pragma once

#include <string>
#include <vector>

#include "CodeChunk.h"
#include "TreeSitterParser.h"

using namespace std;

class CodeParser
{
public:
    vector<CodeChunk> parseFile(const string& filePath);

private:
    TreeSitterParser treeParser;
};