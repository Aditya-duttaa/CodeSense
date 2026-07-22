cmake_minimum_required(VERSION 3.20)

project(CodeSense)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    include
    C:/Libraries/onnxruntime/onnxruntime-win-x64-1.27.1/include

    third_party/tree-sitter/lib/include
    third_party/hnswlib
    third_party/tree-sitter/lib/src
    third_party/tree-sitter-cpp/src
)

link_directories(
    C:/Libraries/onnxruntime/onnxruntime-win-x64-1.27.1/lib
)

add_executable(CodeSense
    src/main.cpp
    src/FileScanner.cpp
    src/CodeParser.cpp
    src/Embedder.cpp
    src/HNSWIndex.cpp
    src/SearchEngine.cpp
    src/Utils.cpp
    src/EmbeddingLoader.cpp
    src/QueryLoader.cpp
    src/FunctionDatabase.cpp
    src/TreeSitterParser.cpp
    src/Indexer.cpp
    third_party/tree-sitter/lib/src/lib.c
    third_party/tree-sitter-cpp/src/parser.c
    third_party/tree-sitter-cpp/src/scanner.c
)

target_link_libraries(CodeSense
    onnxruntime
)