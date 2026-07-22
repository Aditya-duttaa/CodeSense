#include <iostream>
#include <cstdlib>

#include "FunctionDatabase.h"
#include "EmbeddingLoader.h"
#include "QueryLoader.h"
#include "HNSWIndex.h"
#include "Indexer.h"

using namespace std;

int main()
{
    while (true)
    {
        cout << "\n========== CodeSense ==========\n";
        cout << "1. Index Project\n";
        cout << "2. Search\n";
        cout << "3. Exit\n";
        cout << "\nChoice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            string path;

            cout << "Project Path: ";
            getline(cin, path);

            buildIndex(path);

            cout << "\nGenerating embeddings...\n";

            if (system("cd ../python && python embed.py") != 0)
            {
                cout << "Embedding generation failed.\n";
            }
            else
            {
                cout << "Index completed successfully.\n";
            }
        }
        else if (choice == 2)
        {
            auto functions = FunctionDatabase::load("../functions.json");
            auto embeddings = EmbeddingLoader::load("../embeddings.bin");

            cout << "Loaded functions: " << functions.size() << endl;
            cout << "Loaded embeddings: " << embeddings.size() << endl;

            const int EMBEDDING_DIM = embeddings[0].values.size();

            HNSWIndex index(EMBEDDING_DIM);

            vector<vector<float>> vectors;

            for (auto &e : embeddings)
                vectors.push_back(e.values);

            index.build(vectors);

            while (true)
            {
                cout << "\nEnter query (or exit): ";

                string query;
                getline(cin, query);

                if (query == "exit")
                    break;

                string command =
                    "cd ../python && python query_embed.py \"" +
                    query +
                    "\"";

                if (system(command.c_str()) != 0)
                {
                    cout << "Failed to generate query embedding.\n";
                    continue;
                }

                auto queryVector = QueryLoader::load("../query.bin");

                auto results = index.search(queryVector, 5);

                cout << "\n====================\n\n";

                for (auto &r : results)
                {
                    auto &f = functions[r.first];

                    cout << "Function : " << f.name << endl;
                    cout << "File     : " << f.file << endl;
                    cout << "Score    : " << r.second << endl;
                    cout << endl;
                    cout << f.code << endl;
                    cout << "--------------------\n\n";
                }
            }
        }
        else
        {
            break;
        }
    }

    return 0;
}