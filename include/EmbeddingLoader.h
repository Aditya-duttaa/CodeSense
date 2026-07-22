#pragma once

#include "Embedding.h"
#include <vector>
#include <string>

using namespace std;

class EmbeddingLoader
{
public:
    static vector<Embedding> load(
        const string& filename,
        int dimension = 384);
};