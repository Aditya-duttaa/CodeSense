#pragma once

#include <vector>
#include <string>
#include "EmbeddingLoader.h"

using namespace std;

class SearchEngine
{
public:
    static vector<pair<int,float>> search(
        const vector<Embedding>& embeddings,
        const Embedding& query,
        int topK = 5);

private:
    static float cosineSimilarity(
        const Embedding& a,
        const Embedding& b);
};