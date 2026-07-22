#pragma once

#include <bits/stdc++.h>
#include <filesystem>

using namespace std;

class FileScanner
{
public:
    vector<string> scanProject(const string& projectPath);

private:
    bool isSourceFile(const filesystem::path& filePath);
};