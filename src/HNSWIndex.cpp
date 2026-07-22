#include "HNSWIndex.h"



HNSWIndex::HNSWIndex(int dim)
{
    dimension = dim;


    auto space =
        new hnswlib::InnerProductSpace(dim);


    index =
        new hnswlib::HierarchicalNSW<float>(
            space,
            10000
        );
}



HNSWIndex::~HNSWIndex()
{
    delete index;
}



void HNSWIndex::build(
    const vector<vector<float>>& embeddings
)
{

    for(int i=0;i<embeddings.size();i++)
    {
        index->addPoint(
            (void*)embeddings[i].data(),
            i
        );
    }

}



vector<pair<int,float>> HNSWIndex::search(
    const vector<float>& query,
    int topK
)
{
    auto result =
        index->searchKnn(
            (void*)query.data(),
            topK
        );


    vector<pair<int,float>> ans;


    while(!result.empty())
    {
        auto item = result.top();


        int id = (int)item.second;


        // Convert HNSW distance to similarity
        float similarity = 1.0f - item.first;


        ans.push_back(
            {
                id,
                similarity
            }
        );


        result.pop();
    }


    reverse(
        ans.begin(),
        ans.end()
    );


    return ans;
}