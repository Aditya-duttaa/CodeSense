#include "FileScanner.h"

vector<string> FileScanner::scanProject(const string& projectPath)
{
    vector<string> sourceFiles;

    static const unordered_set<string> ignoredDirectories = {
    "node_modules",
    ".git",
    "build",
    "dist",
    "out",
    "bin",
    "obj",
    ".idea",
    ".vscode",
    ".vs",
    "coverage",
    ".next",
    ".cache",
    "include",
    "third_party",
    "models"
};

    filesystem::recursive_directory_iterator it(projectPath), end;

    while (it != end)
    {
        if (it->is_directory())
        {
            string name = it->path().filename().string();

            if (ignoredDirectories.count(name))
            {
                it.disable_recursion_pending();
            }
        }
        else if (it->is_regular_file() && isSourceFile(it->path()))
        {
            sourceFiles.push_back(it->path().string());
        }

        ++it;
    }

    sort(sourceFiles.begin(), sourceFiles.end());

    return sourceFiles;
}

bool FileScanner::isSourceFile(const filesystem::path& filePath)
{
    static const unordered_set<string> extensions = {
        ".cpp", ".cc", ".cxx", ".c",
        ".h", ".hpp",
        ".java",
        ".js", ".jsx",
        ".ts", ".tsx",
        ".go",
        ".rs",
        ".cs"
    };

    string extension = filePath.extension().string();

    transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    return extensions.count(extension);
}