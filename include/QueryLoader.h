#pragma once

#include <vector>
#include <string>

using namespace std;

class QueryLoader
{
public:
    static vector<float> load(const string& filename);
};