#pragma once

#include <hnswlib/hnswlib.h>
#include <vector>

using namespace std;


class HNSWIndex
{
private:

    hnswlib::HierarchicalNSW<float>* index;

    int dimension;


public:

    HNSWIndex(int dim);

    ~HNSWIndex();


    void build(
        const vector<vector<float>>& embeddings
    );


    vector<pair<int,float>> search(
        const vector<float>& query,
        int topK
    );
};