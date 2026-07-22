#include "FunctionDatabase.h"
#include "json.hpp"

#include <fstream>

using json = nlohmann::json;

vector<FunctionInfo> FunctionDatabase::load(const string& filename)
{
    ifstream in(filename);

    if (!in.is_open())
    {
        throw runtime_error("Cannot open functions.json");
    }

    json j;
    in >> j;

    vector<FunctionInfo> functions;

    for (auto& item : j)
    {
        FunctionInfo f;

        f.name = item["name"];
        f.file = item["file"];
        f.code = item["code"];

        if (item.contains("line"))
        {
            f.startLine = item["line"];
        }
        else
        {
            f.startLine = 0;
        }

        if (item.contains("endLine"))
        {
            f.endLine = item["endLine"];
        }
        else
        {
            f.endLine = f.startLine;
        }

        functions.push_back(f);
    }

    return functions;
}