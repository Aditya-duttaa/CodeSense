#include "CodeParser.h"

vector<CodeChunk> CodeParser::parseFile(const string& filePath)
{
    vector<CodeChunk> chunks;

    auto functions = treeParser.parseFile(filePath);

    for (const auto& fn : functions)
    {
        CodeChunk chunk;

        chunk.filePath = fn.file;
        chunk.symbolName = fn.name;
        chunk.code = fn.code;
        chunk.startLine = fn.startLine;
        chunk.endLine = fn.endLine;

        chunks.push_back(std::move(chunk));
    }

    return chunks;
}