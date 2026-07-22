#include "FileScanner.h"
#include "CodeParser.h"

#include "json.hpp"

#include <fstream>
#include <iostream>

using namespace std;
using json = nlohmann::json;

void buildIndex(const string& projectPath)
{
    cout << "Scanning files...\n";

    FileScanner scanner;
    CodeParser parser;

    auto files = scanner.scanProject(projectPath);

    cout << "Files found: " << files.size() << endl;

    json output = json::array();

    int count = 0;

    for (const auto& file : files)
    {
        cout << "Parsing: " << file << endl;

        auto chunks = parser.parseFile(file);

        cout << "Functions: " << chunks.size() << endl;

        for (const auto& chunk : chunks)
        {
            output.push_back({
                {"name", chunk.symbolName},
                {"file", chunk.filePath},
                {"line", chunk.startLine},
                {"endLine", chunk.endLine},
                {"code", chunk.code}
            });
        }

        count++;

    }

    ofstream out("../functions.json");

    out << output.dump(4);

    cout << "Generated functions.json\n";
}