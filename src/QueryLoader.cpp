#include "QueryLoader.h"
#include <fstream>

vector<float> QueryLoader::load(const string& filename)
{
    ifstream in(filename, ios::binary);

    vector<float> embedding(384);

    in.read(
        reinterpret_cast<char*>(embedding.data()),
        384 * sizeof(float));

    return embedding;
}