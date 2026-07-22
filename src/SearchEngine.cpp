#include "SearchEngine.h"

#include <algorithm>
#include <cmath>


float SearchEngine::cosineSimilarity(
    const Embedding& a,
    const Embedding& b)
{
    float score = 0.0f;

    for (size_t i = 0; i < a.values.size(); i++)
    {
        score += a.values[i] * b.values[i];
    }

    return score;
}


vector<pair<int,float>> SearchEngine::search(
    const vector<Embedding>& embeddings,
    const Embedding& query,
    int topK)
{
    vector<pair<int,float>> results;


    for(int i = 0; i < embeddings.size(); i++)
    {
        float score = cosineSimilarity(
            query,
            embeddings[i]
        );

        results.push_back({i, score});
    }


    sort(
        results.begin(),
        results.end(),
        [](auto& a, auto& b)
        {
            return a.second > b.second;
        }
    );


    if(results.size() > topK)
        results.resize(topK);


    return results;
}