#include "EmbeddingLoader.h"
#include <fstream>

vector<Embedding> EmbeddingLoader::load(
    const string& filename,
    int dimension)
{
    ifstream in(filename, ios::binary);

    vector<Embedding> embeddings;

    while (true)
    {
        Embedding e;
        e.values.resize(dimension);

        in.read(
            reinterpret_cast<char*>(e.values.data()),
            dimension * sizeof(float));

        if (!in)
            break;

        embeddings.push_back(move(e));
    }

    return embeddings;
}