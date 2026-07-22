# CodeSense

> **Semantic Code Search Engine built with C++, Tree-sitter, Sentence Transformers, and HNSW**

CodeSense is a semantic code search engine that understands the **meaning** of code instead of relying solely on keyword matching. It indexes source code, converts each function into a high-dimensional vector embedding, and retrieves the most relevant code snippets using natural language queries.

```text
parse file

binary search implementation

function that reads a JSON file

calculate shortest path
```

Instead of searching for exact words, CodeSense performs **semantic similarity search**, allowing developers to find relevant functions even when the query and the code use completely different terminology.

---

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Architecture Overview](#architecture-overview)
- [How CodeSense Works](#how-codesense-works)
- [Project Indexing Pipeline](#project-indexing-pipeline)
- [Semantic Search Pipeline](#semantic-search-pipeline)
- [Vector Embeddings Explained](#vector-embeddings-explained)
- [HNSW Algorithm Explained](#hnsw-algorithm-explained)
- [Project Structure](#project-structure)
- [Technology Stack](#technology-stack)
- [Installation](#installation)
- [Usage](#usage)
- [Example Search](#example-search)
- [Current Limitations](#current-limitations)
- [Future Improvements](#future-improvements)
- [License](#license)

---

## Project Highlights

- 🔍 Semantic code search using natural language
- 🌳 Tree-sitter based function extraction
- 🧠 Sentence Transformer embeddings (384-dimensional vectors)
- ⚡ HNSW Approximate Nearest Neighbor (ANN) search
- 💻 Built primarily in modern C++ with Python for embedding generation
- 📦 Modular architecture with separate indexing and search pipelines

---

## Example Query

```text
Query:
parse file
```

```text
Top Result:
TreeSitterParser::parseFile()
```

---

## Repository Status

> 🚧 CodeSense is a learning project built to explore semantic code search, vector embeddings, and Approximate Nearest Neighbor (ANN) search algorithms. It demonstrates how modern AI-based search techniques can be integrated into a high-performance C++ application.



---

# Introduction

Traditional code search tools work by matching **keywords**. This approach is fast, but it often fails when the code and the search query use different names for the same concept.

For example, suppose a project contains the following function:

```cpp
std::vector<std::string> tokenize(const std::string& text)
```

Searching for:

```text
split sentence into words
```

may return **no results**, even though `tokenize()` is exactly what you're looking for.

This happens because traditional search engines compare **text**, not **meaning**.

---

## The Problem

Traditional search relies on exact words.

```text
User Query
───────────────
split sentence

        │

        ▼

Keyword Search

        │

        ▼

Looks for:
"split"
"sentence"

        │

        ▼

❌ No Match
```

If the code uses different terminology such as:

- tokenize
- parse
- lex
- process

the search engine cannot understand that these words may describe the same operation.

---

## The CodeSense Approach

Instead of matching words, CodeSense compares the **semantic meaning** of code and queries.

```text
User Query
───────────────
split sentence

        │

        ▼

Sentence Transformer

        │

        ▼

384-Dimensional Vector

        │

        ▼

Compare with all code vectors

        │

        ▼

Most Similar Functions

        │

        ▼

✅ tokenize()
```

This allows CodeSense to retrieve relevant code even when the query and the implementation use completely different wording.

---

## Why Semantic Search?

Imagine searching a large codebase.

| Query | Function Name | Traditional Search | CodeSense |
|-------|---------------|-------------------|-----------|
| parse file | `readFile()` | ❌ | ✅ |
| split sentence | `tokenize()` | ❌ | ✅ |
| add two numbers | `add()` | ✅ | ✅ |
| shortest path | `dijkstra()` | ❌ | ✅ |

Semantic search focuses on **what the code does**, rather than **what it is called**.

---

## How CodeSense Solves This

CodeSense combines several modern technologies into a single pipeline:

```text
                 Source Code
                      │
                      ▼
              Tree-sitter Parser
                      │
                      ▼
            Extract Individual Functions
                      │
                      ▼
        Sentence Transformer Embeddings
                      │
                      ▼
           384-Dimensional Vectors
                      │
                      ▼
                 HNSW Index
                      │
                      ▼
           Natural Language Search
                      │
                      ▼
             Ranked Search Results
```

Each function in the project is converted into a numerical vector that captures its semantic meaning.

When a user enters a natural language query, the same embedding model converts the query into another vector. CodeSense then finds the nearest vectors using the **HNSW (Hierarchical Navigable Small World)** algorithm, returning the most semantically relevant functions instead of relying on keyword matches.

By combining **Tree-sitter**, **Sentence Transformers**, and **HNSW**, CodeSense provides a fast and intelligent way to explore large codebases using natural language.



---

# Features

CodeSense is designed to provide fast and intelligent code search by combining source code parsing, semantic embeddings, and Approximate Nearest Neighbor (ANN) search. Instead of relying on keyword matching, it understands the intent behind a query and retrieves the most relevant code.

---

## Current Features

### Semantic Code Search

Search an entire project using natural language.

**Example Queries**

```text
parse json file

binary search implementation

calculate shortest path

read a text file

function that adds two numbers
```

Instead of matching keywords, CodeSense searches for functions with similar semantic meaning.

---

### Tree-sitter Based Parsing

CodeSense uses **Tree-sitter** to parse the source code into an Abstract Syntax Tree (AST).

This provides reliable function extraction without relying on regular expressions.

```
Source File
     │
     ▼
 Tree-sitter Parser
     │
     ▼
 Abstract Syntax Tree (AST)
     │
     ▼
 Extract Functions
```

---

### Automatic Function Extraction

Every discovered function is extracted together with important metadata.

Each indexed function stores:

- Function name
- File path
- Source code
- Starting line number
- Ending line number

Example:

```cpp
int add(int a, int b)
{
    return a + b;
}
```

Stored as:

```text
Name      : add
File      : sample.cpp
Lines     : 1-4
Embedding : 384 floating point values
```

---

### AI-Powered Embeddings

Each function is converted into a **384-dimensional embedding vector** using the Sentence Transformers model.

```
Function

int add(int a, int b)

        │

        ▼

Embedding Model

        │

        ▼

[0.18, -0.42, 0.31, ...]
```

These vectors capture the semantic meaning of the code rather than its exact wording.

---

### Approximate Nearest Neighbor Search (HNSW)

Searching every vector one by one becomes inefficient as projects grow.

CodeSense uses the **HNSW (Hierarchical Navigable Small World)** algorithm to quickly locate the most relevant vectors.

Benefits:

- Fast search
- High accuracy
- Scales to large codebases
- Suitable for semantic search applications

---

### Command Line Interface

The project currently provides a simple CLI.

```
========== CodeSense ==========

1. Index Project
2. Search
3. Exit
```

Users can:

- Index a project
- Generate embeddings
- Perform semantic search
- View ranked results

---

### Modular Architecture

Each major responsibility is separated into its own module.

```
File Scanner
      │
      ▼
Code Parser
      │
      ▼
Indexer
      │
      ▼
Embedding Generator
      │
      ▼
Vector Search
```

This makes the project easier to understand, maintain, and extend.

---

## Supported Languages

Current support includes:

- C++
- C
- Header files

The file scanner is already capable of detecting additional languages such as:

- Java
- JavaScript
- TypeScript
- Go
- Rust
- C#

Future versions can support these languages by integrating the corresponding Tree-sitter grammars.

---

## Performance Highlights

- Fast project indexing
- Lightweight C++ implementation
- AI-powered semantic retrieval
- Approximate Nearest Neighbor search using HNSW
- Natural language queries
- Modular and extensible design
- Modern C++ architecture
- Easy to build using CMake



---

# Architecture Overview

CodeSense follows a modular pipeline where each component is responsible for a single task. This makes the project easy to understand, maintain, and extend.

The entire workflow can be divided into two phases:

1. **Indexing Phase** – Executed once for a project.
2. **Search Phase** – Executed whenever the user performs a search.

---

## High-Level Architecture

```text
                    ┌─────────────────────┐
                    │     Source Code     │
                    │ (.cpp, .h, etc.)    │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │    File Scanner     │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │   Tree-sitter AST   │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │ Function Extraction │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │   functions.json    │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │ Sentence Transformer│
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │  embeddings.bin     │
                    └──────────┬──────────┘
                               │
                  ┌────────────┴────────────┐
                  │                         │
                  ▼                         ▼
         User Query                Query Embedding
                  │                         │
                  └────────────┬────────────┘
                               ▼
                    ┌─────────────────────┐
                    │     HNSW Search      │
                    └──────────┬──────────┘
                               ▼
                    ┌─────────────────────┐
                    │   Ranked Results     │
                    └─────────────────────┘
```

---

## Project Components

### 1. File Scanner

**Responsibility**

- Recursively scans the project directory.
- Finds supported source files.
- Passes file paths to the parser.

**Input**

```text
Project Folder
```

**Output**

```text
List of Source Files
```

---

### 2. Tree-sitter Parser

Tree-sitter parses each source file into an **Abstract Syntax Tree (AST)**.

Unlike regular expressions, AST parsing understands the structure of the programming language.

Example:

```cpp
int add(int a, int b)
{
    return a + b;
}
```

becomes

```text
Function Definition
├── Return Type
├── Function Name
├── Parameters
└── Body
```

The parser extracts:

- Function name
- Source code
- File path
- Start line
- End line

---

### 3. Indexer

The indexer combines all extracted functions and stores them inside:

```text
functions.json
```

Each function is stored independently.

Example:

```json
{
  "name": "add",
  "file": "sample.cpp",
  "line": 10,
  "endLine": 13,
  "code": "int add(int a,int b){...}"
}
```

---

### 4. Embedding Generator

The Python embedding script loads every function from `functions.json`.

Each function is converted into a **384-dimensional vector** using the Sentence Transformer model.

```
Function

↓

Embedding Model

↓

384 Numbers

↓

embeddings.bin
```

These vectors represent the semantic meaning of each function.

---

### 5. HNSW Search Engine

Instead of comparing every function one by one, CodeSense builds an **HNSW index**.

```
Embedding Vectors

↓

HNSW Graph

↓

Fast Similarity Search
```

This significantly reduces search time while maintaining high retrieval quality.

---

### 6. Search Pipeline

When the user enters a query:

```text
parse file
```

the exact same embedding model converts it into another vector.

```
Query

↓

Embedding

↓

HNSW Search

↓

Top K Results
```

The returned vectors are mapped back to their original functions and displayed in the CLI.

---

## Module Relationships

```text
main.cpp
    │
    ▼
Indexer
    │
    ├────────────► FileScanner
    │
    ├────────────► CodeParser
    │                     │
    │                     ▼
    │             TreeSitterParser
    │
    ▼
functions.json
    │
    ▼
Python Embedder
    │
    ▼
embeddings.bin
    │
    ▼
EmbeddingLoader
    │
    ▼
HNSWIndex
    │
    ▼
Search Results
```

---

## Why This Architecture?

Separating the project into independent modules provides several advantages:

- Clear separation of responsibilities
- Easy debugging
- Easier maintenance
- Better scalability
- Individual components can be replaced without affecting the rest of the pipeline

For example, the embedding model can be replaced with a newer model without changing the parser, and a different vector search algorithm can replace HNSW without modifying the indexing logic.



---

# How CodeSense Works

CodeSense operates in two independent phases:

1. **Project Indexing** *(performed once)*
2. **Semantic Search** *(performed whenever the user searches)*

The indexing phase prepares the project for searching, while the search phase retrieves the most relevant functions in milliseconds.

---

# Phase 1 — Project Indexing

When the user selects **Index Project**, CodeSense processes the entire project and builds a searchable database.

```
Project Folder
      │
      ▼
 Scan Source Files
      │
      ▼
 Parse Each File
      │
      ▼
 Extract Functions
      │
      ▼
 Save Metadata
      │
      ▼
 Generate Embeddings
      │
      ▼
 Store Vector Database
```

---

## Step 1 — Scan the Project

The File Scanner recursively scans the project directory.

```
Project

├── src
│   ├── main.cpp
│   ├── SearchEngine.cpp
│   └── ...
│
├── include
│   ├── SearchEngine.h
│   └── ...
```

Only supported source files are collected.

```
.cpp
.c
.cc
.cxx
.h
.hpp
```

---

## Step 2 — Parse Every File

Each discovered source file is parsed using **Tree-sitter**.

```
SearchEngine.cpp

        │

        ▼

Tree-sitter Parser

        │

        ▼

Abstract Syntax Tree
```

Unlike text parsing, Tree-sitter understands the structure of C++ code.

---

## Step 3 — Extract Individual Functions

Each function definition becomes an independent search document.

Example:

```cpp
int add(int a, int b)
{
    return a + b;
}
```

Stored as:

```
Function Name : add

File : sample.cpp

Lines : 10-13

Code :
int add(...)
```

Every function is treated as a separate searchable unit.

---

## Step 4 — Build functions.json

All extracted functions are stored in a JSON file.

```
functions.json

↓

[
  {
    "name":"add",
    "file":"sample.cpp",
    "code":"..."
  },
  ...
]
```

This file acts as the metadata database.

---

## Step 5 — Generate Embeddings

The Python embedding script loads every function from `functions.json`.

```
Function

↓

Sentence Transformer

↓

Embedding Vector
```

Example:

```
[0.42,
-0.17,
0.93,
...
384 values]
```

Every function now has a numerical representation.

---

## Step 6 — Store Embeddings

All vectors are stored inside

```
embeddings.bin
```

This binary file is later loaded during semantic search.

---

# Phase 2 — Semantic Search

Once indexing is complete, searching becomes very fast.

```
User Query

↓

Generate Query Embedding

↓

Search Similar Vectors

↓

Retrieve Functions

↓

Display Results
```

---

## Step 1 — User Enters a Query

Example:

```
parse file
```

---

## Step 2 — Convert Query to a Vector

The exact same embedding model converts the query into a 384-dimensional vector.

```
parse file

↓

Embedding Model

↓

[0.18,
0.55,
-0.31,
...]
```

Because both code and queries use the same embedding model, they exist in the same semantic space.

---

## Step 3 — Search Similar Vectors

Instead of comparing against every function manually,

CodeSense searches the HNSW graph.

```
Query Vector

↓

HNSW Index

↓

Nearest Neighbors
```

Only the most relevant vectors are explored.

---

## Step 4 — Retrieve Function Metadata

The nearest vectors correspond to function IDs.

Those IDs are mapped back to

```
functions.json
```

to obtain

- Function name
- File path
- Source code
- Line numbers

---

## Step 5 — Display Results

Example output:

```text
Function : TreeSitterParser::parseFile

File : src/TreeSitterParser.cpp

Score : 0.513
```

The user immediately receives the most relevant functions ranked by semantic similarity.

---

# Complete Workflow

```
                     INDEXING

Source Code
      │
      ▼
File Scanner
      │
      ▼
Tree-sitter
      │
      ▼
Extract Functions
      │
      ▼
functions.json
      │
      ▼
Sentence Transformer
      │
      ▼
embeddings.bin



                     SEARCHING

User Query
      │
      ▼
Sentence Transformer
      │
      ▼
Query Vector
      │
      ▼
HNSW Search
      │
      ▼
Top K Vectors
      │
      ▼
functions.json
      │
      ▼
Display Results
```

---

## Why Separate Indexing and Searching?

Separating these two phases provides significant performance benefits.

- Parsing happens only once.
- Embeddings are generated only once.
- Search only loads precomputed vectors.
- Large projects can be searched almost instantly after indexing.

This design is commonly used in production search systems because indexing is expensive, while searching must remain fast and responsive.




---

# Vector Embeddings Explained

The core idea behind CodeSense is **Vector Embeddings**.

Instead of searching for matching words, CodeSense converts both **source code** and **user queries** into numerical vectors that capture their semantic meaning.

Two pieces of code that perform similar tasks will have vectors that are close together, even if they use completely different variable names or function names.

---

## What is an Embedding?

An embedding is simply a list of numbers that represents the meaning of a piece of text.

Instead of storing

```cpp
int add(int a, int b)
{
    return a + b;
}
```

CodeSense stores something similar to

```text
[0.314,
-0.217,
0.841,
...
384 values]
```

These numbers are called the **embedding vector**.

Each function in the project has its own unique embedding.

---

## Why Convert Code into Numbers?

Computers cannot compare the *meaning* of text directly.

However, they can compare numbers very efficiently.

By converting code into vectors, we can calculate how similar two pieces of code are.

```
Source Code
      │
      ▼
Embedding Model
      │
      ▼
384-Dimensional Vector
```

---

## The Same Process for User Queries

When the user searches

```text
parse file
```

the exact same embedding model is used.

```
Natural Language Query

        │

        ▼

Sentence Transformer

        │

        ▼

384-Dimensional Vector
```

Now both the **query** and the **source code** are represented as vectors in the same mathematical space.

---

## A Simple Visualization

Imagine every function is represented as a point.

```
                parseFile()

                     ●



        readFile()          loadFile()

             ●                 ●



                              tokenize()

                                  ●



add()

●



multiply()

          ●
```

Now suppose the user searches

```
parse file
```

The query is also converted into a point.

```
                     Query

                      X

                      │

                      ▼

                parseFile()

                     ●



        readFile()          loadFile()

             ●                 ●



                              tokenize()

                                  ●
```

The nearest functions are returned.

---

## Similar Meaning = Nearby Vectors

Consider these functions.

```cpp
readFile()
```

```cpp
loadFile()
```

```cpp
openFile()
```

Although the names are different, they all perform similar tasks.

Their vectors become close together.

```
readFile()

      ●

          ● loadFile()

               ● openFile()
```

Now consider

```cpp
sortArray()
```

Its vector will be much farther away.

```
readFile()

      ●

          ● loadFile()

               ● openFile()




                         sortArray()

                               ●
```

---

## Why Keyword Search Fails

Suppose your project contains

```cpp
tokenize()
```

The user searches

```
split sentence into words
```

Traditional search:

```
Looking for

split

sentence

words

↓

No Match
```

Semantic search:

```
split sentence

↓

Embedding

↓

Nearest Meaning

↓

tokenize()
```

The wording is different, but the intent is the same.

---

## Cosine Similarity

Once vectors are created, CodeSense compares them using **Cosine Similarity**.

Instead of comparing the actual words, it compares the direction of two vectors.

```
Query Vector

      →

Function Vector

      →

High Similarity
```

If the vectors point in nearly the same direction,

they likely represent similar meanings.

If they point in very different directions,

the functions are probably unrelated.

---

## Why 384 Dimensions?

The Sentence Transformer model used by CodeSense generates vectors containing **384 floating-point values**.

```
[
0.23,
-0.11,
0.84,
...
384 values
]
```

Each dimension captures a small part of the function's semantic meaning.

Although humans cannot interpret individual dimensions, together they form a rich mathematical representation of the code.

---

## Benefits of Embeddings

- Understands semantic meaning instead of exact words.
- Finds related functions even with different names.
- Handles natural language queries.
- Enables fast similarity search using vector databases.
- Forms the foundation of modern AI-powered search systems.

---

## Summary

```
Source Code
      │
      ▼
Embedding Model
      │
      ▼
384-D Vector
      │
      │
      ├─────────────┐
      │             │
      ▼             ▼
User Query      Function Vector
      │             │
      └──────┬──────┘
             ▼
      Cosine Similarity
             ▼
     Most Similar Functions
```

Vector embeddings are what allow CodeSense to search by **meaning** instead of simple keyword matching, making semantic code search far more flexible and powerful than traditional text-based search.





---

# HNSW Algorithm Explained

After converting every function into a vector, CodeSense must search through all of them to find the most similar ones.

A simple approach would be to compare the query with **every single vector**.

```
Query

↓

Vector 1 ✓

↓

Vector 2 ✓

↓

Vector 3 ✓

↓

...

↓

Vector N ✓
```

This is called **Brute Force Search**.

While it works well for small projects, it becomes increasingly slow as the number of indexed functions grows.

If a project contains:

- 10,000 functions
- 100,000 functions
- 1,000,000 functions

then comparing every vector for every search quickly becomes impractical.

---

# The Solution: Approximate Nearest Neighbor Search

Instead of checking every vector, CodeSense uses an **Approximate Nearest Neighbor (ANN)** algorithm.

The idea is simple:

> Rather than searching the entire dataset, intelligently navigate toward the most promising candidates.

CodeSense uses one of the most popular ANN algorithms:

> **HNSW (Hierarchical Navigable Small World)**

---

# What is HNSW?

HNSW organizes vectors into a graph instead of storing them in a simple list.

Each vector becomes a **node**, and every node is connected to several nearby nodes.

Example:

```
            A
          / | \
         /  |  \
        B---C---D
       / \  |  / \
      E---F-G---H
          |
          I
```

Nearby vectors are connected together.

This allows the search algorithm to "walk" through the graph instead of checking every vector.

---

# Why is it Called "Hierarchical"?

HNSW builds **multiple layers**.

The higher layers contain fewer nodes and provide a rough overview of the entire dataset.

The lower layers contain more nodes and provide greater detail.

```
Layer 3

        A


Layer 2

    B       C


Layer 1

 D   E   F   G   H


Layer 0

Every Indexed Function
```

Think of it like a map.

- The highest layer is similar to viewing an entire country.
- The middle layer is like viewing a city.
- The lowest layer is like viewing individual streets.

The search gradually zooms in until it reaches the closest functions.

---

# How Searching Works

Suppose the user searches:

```
parse file
```

First, the query is converted into an embedding vector.

```
Query

↓

Embedding Vector
```

Instead of comparing against every indexed function,

the algorithm starts from an entry point.

```
Query

↓

Entry Node

↓

Move to Better Neighbor

↓

Move Again

↓

Closest Region

↓

Top Results
```

Each step moves only if it finds a node that is closer to the query.

Eventually the search reaches a local optimum.

---

# Example

Imagine the indexed functions are distributed like this.

```
                parseFile()

                     ●



        readFile()          loadFile()

             ●                 ●



sortArray()                 tokenize()

      ●                         ●



binarySearch()

          ●
```

The query

```
parse file
```

starts somewhere in the graph.

Instead of checking every point,

HNSW follows nearby connections.

```
Start

↓

loadFile()

↓

readFile()

↓

parseFile()

✓ Found
```

Only a small portion of the graph is explored.

---

# Why is HNSW Fast?

Suppose we have:

```
100,000 vectors
```

Brute Force:

```
Compare against

100,000 vectors
```

HNSW:

```
Visit only a few hundred nodes
```

This dramatically reduces search time while still producing highly accurate results.

---

# Approximate vs Exact Search

HNSW is an **approximate** search algorithm.

That means it may not always return the mathematically perfect nearest neighbor.

Instead, it returns results that are extremely close while being much faster.

```
Exact Search

100% Accuracy

Very Slow



Approximate Search

~99% Accuracy

Very Fast
```

For semantic search, this trade-off is ideal.

---

# Why HNSW is Used

HNSW has become one of the most widely used ANN algorithms because it provides an excellent balance between speed and accuracy.

It is used in many modern vector search systems.

Advantages:

- Extremely fast search
- High recall (very accurate results)
- Efficient graph traversal
- Scales to millions of vectors
- Well suited for semantic search and AI applications

---

# HNSW in CodeSense

After all functions have been converted into embeddings,

CodeSense builds an HNSW graph.

```
Function

↓

Embedding

↓

HNSW Graph

↓

Ready for Search
```

During a search:

```
User Query

↓

Embedding

↓

HNSW Search

↓

Top 5 Most Similar Functions
```

This allows CodeSense to return relevant functions in a fraction of the time required by brute-force comparison.

---

# Summary

```
                 Without HNSW

Query

↓

Compare Every Vector

↓

Slow Search



                 With HNSW

Query

↓

HNSW Graph

↓

Navigate Nearby Nodes

↓

Nearest Functions

↓

Fast Search
```

HNSW is the engine that makes semantic search practical for large codebases. By organizing embeddings into a hierarchical graph, CodeSense can efficiently locate functions with similar meaning while avoiding expensive comparisons against every indexed vector.




---

# Project Structure

The project is organized into independent modules, where each component is responsible for a single task. This modular design makes CodeSense easier to understand, maintain, and extend.

```text
CodeSense
│
├── include/               # Header files
│
├── src/                   # C++ source files
│
├── python/                # Embedding generation scripts
│
├── third_party/           # External libraries
│
├── models/                # Sentence Transformer model
│
├── build/                 # CMake build directory
│
├── sample.cpp             # Sample project
│
├── functions.json         # Extracted function metadata
│
├── embeddings.bin         # Function embeddings
│
├── query.bin              # Query embedding
│
├── CMakeLists.txt
│
└── README.md
```

---

## include/

The **include/** directory contains all header files that define the interfaces used throughout the project.

```text
include/

├── CodeChunk.h
├── CodeParser.h
├── Config.h
├── Embedder.h
├── Embedding.h
├── EmbeddingLoader.h
├── FileScanner.h
├── FunctionDatabase.h
├── HNSWIndex.h
├── Indexer.h
├── QueryLoader.h
├── SearchEngine.h
├── TreeSitterParser.h
└── Utils.h
```

These headers define the public interfaces while keeping implementations inside the `src` directory.

---

## src/

The **src/** directory contains the implementation of the entire semantic search engine.

```text
src/

├── main.cpp
├── FileScanner.cpp
├── TreeSitterParser.cpp
├── CodeParser.cpp
├── Indexer.cpp
├── FunctionDatabase.cpp
├── EmbeddingLoader.cpp
├── Embedder.cpp
├── QueryLoader.cpp
├── HNSWIndex.cpp
├── SearchEngine.cpp
└── Utils.cpp
```

Each file is responsible for one major component of the project.

---

## python/

The Python scripts are responsible for generating embeddings using the Sentence Transformers model.

```text
python/

├── embed.py
├── query_embed.py
└── app.py
```

### embed.py

- Reads `functions.json`
- Generates embeddings for every function
- Saves them to `embeddings.bin`

---

### query_embed.py

- Converts a user query into an embedding
- Stores the result inside `query.bin`

---

### app.py

Utility script for testing or experimentation.

---

## third_party/

This directory contains all external dependencies required by the project.

Examples include:

- Tree-sitter
- HNSWLIB
- ONNX Runtime
- Tokenizers
- JSON library

Keeping third-party libraries separate makes the project easier to maintain and update.

---

## models/

Contains the Sentence Transformer model used for embedding generation.

The model is loaded by the Python scripts and is responsible for converting source code and natural language into vector embeddings.

---

## Generated Files

These files are automatically created during indexing.

### functions.json

Stores metadata for every extracted function.

Example:

```json
{
    "name": "parseFile",
    "file": "TreeSitterParser.cpp",
    "line": 20,
    "endLine": 65,
    "code": "..."
}
```

---

### embeddings.bin

Binary file containing the embedding vector for every indexed function.

```
Function 1

↓

384-dimensional vector

↓

Binary Storage
```

---

### query.bin

Stores the embedding vector generated from the user's search query.

This file is recreated for every search.

---

## Data Flow Between Modules

```
File Scanner
      │
      ▼
TreeSitter Parser
      │
      ▼
Code Parser
      │
      ▼
Indexer
      │
      ▼
functions.json
      │
      ▼
Python Embedding Generator
      │
      ▼
embeddings.bin
      │
      ▼
Embedding Loader
      │
      ▼
HNSW Search
      │
      ▼
Search Results
```

---

## Why This Structure?

This organization provides several benefits:

- Clear separation of responsibilities
- Easy navigation through the codebase
- Independent modules that can be modified without affecting others
- Easier debugging and maintenance
- Straightforward addition of new features

For example:

- A new embedding model can be integrated without changing the parser.
- Another vector search algorithm can replace HNSW without modifying the indexing pipeline.
- Additional programming languages can be supported by adding new Tree-sitter grammars while keeping the rest of the system unchanged.

This modular architecture makes CodeSense a solid foundation for experimenting with semantic code search and future improvements.




---

# Technology Stack

CodeSense combines modern C++ with AI-powered embedding models to enable semantic code search. Each technology is responsible for a specific part of the search pipeline.

---

## Overview

| Technology | Purpose |
|------------|---------|
| **C++20** | Core application and search engine |
| **Python 3** | Embedding generation scripts |
| **Tree-sitter** | Source code parsing |
| **Sentence Transformers** | Semantic embedding generation |
| **HNSWLIB** | Approximate Nearest Neighbor search |
| **ONNX Runtime** | Running embedding models efficiently |
| **nlohmann/json** | Reading and writing JSON files |
| **CMake** | Cross-platform build system |

---

# C++20

The entire search engine is implemented in **Modern C++**.

It is responsible for:

- Project indexing
- File scanning
- Source code parsing
- Metadata management
- Loading embeddings
- HNSW vector search
- Command-line interface

Why C++?

- High performance
- Low memory overhead
- Efficient vector processing
- Excellent ecosystem for systems programming

---

# Tree-sitter

Tree-sitter is an incremental parsing library used to build an **Abstract Syntax Tree (AST)** from source code.

```
Source Code

↓

Tree-sitter

↓

Abstract Syntax Tree

↓

Extract Functions
```

Unlike regular expressions, Tree-sitter understands the syntax of the programming language, making function extraction much more reliable.

It extracts:

- Function names
- Function bodies
- File paths
- Line numbers

---

# Sentence Transformers

Sentence Transformers generate semantic embeddings for both source code and natural language queries.

```
Source Code

↓

Sentence Transformer

↓

384-Dimensional Vector
```

The same model is also used for user queries.

```
Natural Language

↓

Sentence Transformer

↓

384-Dimensional Vector
```

Since both are embedded using the same model, meaningful similarity comparisons become possible.

---

# HNSWLIB

HNSWLIB is used for Approximate Nearest Neighbor (ANN) search.

Instead of comparing the query against every function, HNSW searches a graph of connected vectors.

```
Embedding Vectors

↓

HNSW Graph

↓

Nearest Functions
```

Benefits include:

- Fast search
- High accuracy
- Efficient scaling to large datasets

---

# ONNX Runtime

The embedding model is stored in ONNX format.

ONNX Runtime loads and executes the model efficiently.

```
ONNX Model

↓

ONNX Runtime

↓

Embedding Vector
```

Using ONNX provides:

- Fast inference
- Cross-platform compatibility
- Efficient CPU execution

---

# Python

Python is used only for AI-related tasks.

Responsibilities include:

- Loading the embedding model
- Generating function embeddings
- Generating query embeddings

Keeping AI components in Python allows the C++ application to remain lightweight while leveraging mature machine learning libraries.

---

# nlohmann/json

This library simplifies reading and writing JSON files.

It is used to create and load:

```
functions.json
```

Example:

```cpp
json output = json::array();

output.push_back({
    {"name", chunk.symbolName},
    {"file", chunk.filePath},
    {"line", chunk.startLine},
    {"code", chunk.code}
});
```

---

# CMake

CMake manages the build process.

It handles:

- Compiler configuration
- Source file management
- Third-party libraries
- Executable generation

Typical build process:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

---

# How Everything Works Together

```
              C++ Application
                     │
                     ▼
              Tree-sitter Parser
                     │
                     ▼
             Extract Functions
                     │
                     ▼
              functions.json
                     │
                     ▼
              Python Scripts
                     │
                     ▼
          Sentence Transformer
                     │
                     ▼
             embeddings.bin
                     │
                     ▼
              HNSWLIB Search
                     │
                     ▼
             Ranked Results
```

---

# Why This Stack?

Each technology was selected because it is well-suited for its specific task:

| Requirement | Technology |
|-------------|------------|
| High-performance application | C++20 |
| Reliable code parsing | Tree-sitter |
| Semantic understanding | Sentence Transformers |
| Fast vector search | HNSWLIB |
| Efficient model inference | ONNX Runtime |
| Structured data storage | JSON |
| Cross-platform builds | CMake |

Together, these technologies form a complete semantic code search pipeline that is fast, modular, and easy to extend.





---

# Installation

## Prerequisites

Before building CodeSense, make sure the following software is installed on your system.

| Software | Version |
|----------|---------|
| C++ Compiler | C++20 Compatible |
| CMake | 3.20+ |
| Python | 3.10+ |
| Git | Latest |

Recommended compiler:

- GCC 13+
- Clang 16+
- MSVC 2022

---

# Clone the Repository

```bash
git clone https://github.com/Aditya-duttaa/CodeSense.git

cd CodeSense
```

---

# Build the Project

Create a build directory.

```bash
mkdir build
cd build
```

Generate the build files.

```bash
cmake ..
```

Compile the project.

```bash
cmake --build .
```

After compilation, the executable will be available inside the **build** directory.

```
build/

└── CodeSense.exe
```

---

# Install Python Dependencies

Navigate to the Python directory.

```bash
cd ../python
```

Install the required packages.

```bash
pip install -r requirements.txt
```

If you do not have a `requirements.txt` file yet, install the dependencies manually.

```bash
pip install sentence-transformers torch numpy
```

---

# Download the Embedding Model

The Sentence Transformer model must be downloaded before generating embeddings.

The default model used by CodeSense is:

```
all-MiniLM-L6-v2
```

The first execution automatically downloads the model from Hugging Face and caches it locally.

No additional setup is required.

---

# Index a Project

Run the executable.

```bash
CodeSense.exe
```

Select:

```
1. Index Project
```

Then enter the project path.

Example:

```
C:\Projects\MyCppProject
```

CodeSense will:

```
Scan Project

↓

Parse Source Files

↓

Extract Functions

↓

Generate Embeddings

↓

Index Complete
```

Generated files:

```
functions.json

embeddings.bin
```

---

# Search the Project

Run the application.

```bash
CodeSense.exe
```

Choose:

```
2. Search
```

Enter a natural language query.

Example:

```
parse file

read json

binary search

tokenize string
```

The application returns the most semantically relevant functions ranked by similarity.

---

# Typical Workflow

```
Clone Repository

        │

        ▼

Build Project

        │

        ▼

Install Python Packages

        │

        ▼

Index Project

        │

        ▼

Generate Embeddings

        │

        ▼

Search Using Natural Language
```

---

# Verify the Installation

If everything is configured correctly, running the executable should display:

```text
========== CodeSense ==========

1. Index Project
2. Search
3. Exit
```

After indexing a project, you should see output similar to:

```text
Scanning files...

Files found: 18

Generating embeddings...

Index completed successfully.
```

You are now ready to perform semantic searches on your codebase.




---

# Usage

After building the project and installing the required dependencies, CodeSense can be used in two simple steps:

1. **Index a project**
2. **Perform semantic searches**

---

# Step 1 — Launch CodeSense

Run the executable.

**Windows**

```bash
CodeSense.exe
```

**Linux / macOS**

```bash
./CodeSense
```

You will see:

```text
========== CodeSense ==========

1. Index Project
2. Search
3. Exit
```

---

# Step 2 — Index a Project

Choose:

```text
1
```

Enter the path of the project you want to index.

Example:

```text
C:\Users\Aditya\Desktop\MyProject
```

CodeSense will automatically:

```
Project Folder
      │
      ▼
Scan Source Files
      │
      ▼
Extract Functions
      │
      ▼
Generate Embeddings
      │
      ▼
Save Search Database
```

Example output:

```text
Scanning files...

Files found: 18

Parsing:
sample.cpp

Functions: 6

Generating embeddings...

Index completed successfully.
```

---

# Step 3 — Search

Choose:

```text
2
```

CodeSense loads the indexed database.

Example:

```text
Loaded functions: 18

Loaded embeddings: 18
```

Now enter a natural language query.

Example:

```text
parse file
```

---

# Example Session

```text
Enter query (or exit):

parse file
```

CodeSense converts the query into a semantic embedding and searches for the most similar functions.

Example output:

```text
Function : TreeSitterParser::parseFile

File :
src/TreeSitterParser.cpp

Score : 0.513526
```

The complete source code of the matching function is then displayed.

---

# Example Queries

Because CodeSense performs **semantic search**, users are not limited to exact function names.

Try queries like:

```text
parse file
```

```text
read json
```

```text
load configuration
```

```text
find shortest path
```

```text
binary search implementation
```

```text
tokenize string
```

```text
calculate gcd
```

Even if the function names differ from the query, CodeSense can still retrieve relevant results based on meaning.

---

# Search Workflow

```
User Query

↓

Generate Query Embedding

↓

HNSW Search

↓

Find Similar Functions

↓

Display Ranked Results
```

---

# Exit the Search Mode

To stop searching, simply type:

```text
exit
```

This returns you to the main menu.

```
========== CodeSense ==========

1. Index Project
2. Search
3. Exit
```

Choose:

```text
3
```

to close the application.

---

# Tips

✔ Index a project only once unless the source code changes.

✔ Re-index after adding, removing, or modifying functions.

✔ Use descriptive natural language queries instead of exact function names.

✔ Short queries work, but complete descriptions often produce better semantic matches.

Example:

Instead of

```text
json
```

try

```text
function that reads a JSON file
```

or

```text
parse configuration file
```

---

# Complete Workflow

```
Build Project
      │
      ▼
Run CodeSense
      │
      ▼
Index Project
      │
      ▼
Generate Embeddings
      │
      ▼
Semantic Search
      │
      ▼
Relevant Functions
```

CodeSense is now ready to help you explore large codebases using natural language instead of traditional keyword-based searches.




---

# Example Search

The following example demonstrates how CodeSense performs semantic search on an indexed C++ project.

---

## Step 1 — Start the Application

```text
========== CodeSense ==========

1. Index Project
2. Search
3. Exit
```

Select:

```text
2
```

---

## Step 2 — Load the Search Database

After selecting **Search**, CodeSense loads the indexed metadata and embedding vectors.

```text
Loaded functions: 18
Loaded embeddings: 18
```

---

## Step 3 — Enter a Natural Language Query

Example query:

```text
parse file
```

Unlike traditional code search, the query does **not** need to match the function name exactly.

---

## Step 4 — Generate the Query Embedding

The query is converted into a 384-dimensional embedding.

```text
"parse file"

        │

        ▼

Sentence Transformer

        │

        ▼

Query Embedding
```

---

## Step 5 — Search Using HNSW

The embedding is searched against the indexed vector database.

```text
Query Vector

        │

        ▼

HNSW Graph

        │

        ▼

Nearest Function Embeddings

        │

        ▼

Top 5 Results
```

---

## Search Result

Example output:

```text
Function : TreeSitterParser::parseFile

File     : src/TreeSitterParser.cpp

Score    : 0.513526
```

CodeSense also displays the complete source code of the matched function.

---

## Why Was This Function Returned?

The user searched:

```text
parse file
```

The function returned was:

```cpp
TreeSitterParser::parseFile(...)
```

Although the search query is only two words, the embedding model understands that the query is semantically related to a function responsible for parsing source files.

Instead of comparing text directly, CodeSense compares the **meaning** of the query with the **meaning** of every indexed function.

---

## Ranking Results

Results are ranked according to their semantic similarity score.

Example:

| Rank | Function | Similarity Score |
|------|----------|-----------------:|
| 1 | `TreeSitterParser::parseFile()` | 0.513 |
| 2 | `buildIndex()` | 0.459 |
| 3 | `CodeParser::parseFile()` | 0.447 |
| 4 | `FileScanner::isSourceFile()` | 0.406 |
| 5 | `FunctionDatabase::load()` | 0.377 |

A higher score indicates that the function is more semantically related to the user's query.

---

## Another Example

Query:

```text
load function metadata
```

Expected top results might include:

- `FunctionDatabase::load()`
- `EmbeddingLoader::load()`
- `QueryLoader::load()`

Even if the words are not identical, CodeSense retrieves functions with similar intent.

---

## End-to-End Search Pipeline

```text
User Query

        │

        ▼

Generate Query Embedding

        │

        ▼

HNSW Search

        │

        ▼

Nearest Function Vectors

        │

        ▼

Retrieve Function Metadata

        │

        ▼

Display Ranked Results
```

---

## Example Search Session

```text
========== CodeSense ==========

1. Index Project
2. Search
3. Exit

Choice: 2

Loaded functions: 18
Loaded embeddings: 18

Enter query:

parse file

--------------------------------------------

Function : TreeSitterParser::parseFile

File     : src/TreeSitterParser.cpp

Score    : 0.513526

--------------------------------------------
```

This example demonstrates how CodeSense transforms a natural language query into a semantic search, allowing users to find relevant code even when the query does not exactly match function names or keywords.




---

# Current Limitations

CodeSense is a functional prototype that demonstrates semantic code search using modern AI techniques. While it performs well for small and medium-sized projects, there are several limitations in the current implementation.

---

## Supported Languages

Although the file scanner detects multiple source file extensions, the parser currently uses the **C++ Tree-sitter grammar**.

Current support:

- ✅ C++
- ✅ C
- ✅ Header files

Future versions can support additional languages by integrating the corresponding Tree-sitter grammars.

---

## Whole Function Embeddings

Each function is converted into **a single embedding vector**.

```
Entire Function

        │

        ▼

Single Embedding
```

For very large functions, important information may be compressed into one vector, reducing search precision.

A chunk-based indexing approach could improve retrieval quality.

---

## No Incremental Indexing

Whenever the source code changes, the entire project must be indexed again.

Current workflow:

```
Modify Source Code

        │

        ▼

Re-index Entire Project
```

A smarter indexing system would only update modified files.

---

## CLI Only

CodeSense currently provides a command-line interface.

```
========== CodeSense ==========

1. Index Project
2. Search
3. Exit
```

Although suitable for development and testing, a graphical interface would improve usability.

---

## Limited Ranking Strategy

Search results are ranked using only **vector similarity**.

Current ranking does not consider:

- Function popularity
- Number of references
- Call graph relationships
- File importance
- Project structure

Combining semantic similarity with static analysis could produce better rankings.

---

## Exact Code Display

When a result is selected, the entire function is displayed.

There is currently no:

- Syntax highlighting
- Line highlighting
- Search term highlighting
- Code preview

---

## Local Search Only

CodeSense indexes projects stored on the local machine.

It does not currently support:

- Remote Git repositories
- GitHub projects
- GitLab repositories
- Online code search

---

## Single Embedding Model

The current implementation uses a single Sentence Transformer model.

Different programming languages or specialized domains may benefit from different embedding models.

---

## Memory Usage

The entire embedding database is loaded into memory before searching.

While acceptable for smaller projects, this approach may become inefficient for very large repositories.

---

## Future Scalability

The current implementation has been tested on relatively small codebases.

For very large projects, additional optimizations such as:

- Incremental indexing
- Disk-based vector storage
- Parallel embedding generation
- Distributed indexing

would improve performance.

---

# Summary

Current limitations include:

- C++ parser only
- Full project re-indexing
- Command-line interface only
- Single embedding per function
- Basic vector-based ranking
- Local project support only
- In-memory embedding storage

Despite these limitations, CodeSense successfully demonstrates the complete semantic code search pipeline—from source code parsing and embedding generation to fast vector search using HNSW—providing a solid foundation for future improvements.





---

# Future Improvements

Although CodeSense already provides a complete semantic code search pipeline, there are many opportunities to extend its capabilities. The current modular architecture makes it easy to integrate new features without major changes to the existing codebase.

---

## Planned Improvements

### Incremental Indexing

Currently, the entire project is re-indexed whenever the source code changes.

A future version could detect only modified files and update the corresponding embeddings.

```
Current

Modify File

↓

Re-index Entire Project



Future

Modify File

↓

Re-index Changed File Only
```

---

### Multi-Language Support

The current implementation focuses on C++.

By integrating additional Tree-sitter grammars, CodeSense could support languages such as:

- Python
- Java
- JavaScript
- TypeScript
- Go
- Rust
- C#
- Kotlin

---

### Graphical User Interface

A desktop or web interface would make CodeSense more accessible.

Possible features include:

- Search bar
- Syntax-highlighted code viewer
- Search history
- File explorer
- Dark mode
- One-click project indexing

---

### VS Code Extension

A Visual Studio Code extension could allow developers to search directly within their editor.

Possible workflow:

```
Developer

↓

Open VS Code

↓

Search

"parse json"

↓

Relevant Functions
```

---

### Improved Ranking

Search quality can be further improved by combining semantic similarity with additional information.

Possible ranking signals:

- Function call relationships
- File importance
- Symbol references
- Project structure
- Documentation comments

---

### Better Code Chunking

Instead of embedding an entire function as one vector, large functions could be divided into smaller logical chunks.

```
Large Function

↓

Split into Chunks

↓

Generate Embeddings

↓

Higher Search Accuracy
```

---

### Faster Embedding Generation

Embedding generation currently processes functions sequentially.

Future versions could use:

- Parallel processing
- Batch inference
- GPU acceleration

to significantly reduce indexing time.

---

### Smarter Search

Future versions could understand more complex queries such as:

```text
Find every function that reads a file and returns JSON.
```

or

```text
Show authentication-related functions.
```

This would move beyond simple semantic similarity toward intent-aware code search.

---

### Larger Model Support

Different embedding models could be evaluated to improve retrieval quality.

Potential options include:

- CodeBERT
- UniXcoder
- E5
- BGE
- Other code-specific embedding models

---

### Git Repository Support

Instead of indexing only local projects, CodeSense could directly index remote repositories.

Example workflow:

```
GitHub Repository

↓

Clone Repository

↓

Index Automatically

↓

Search
```

---

### Rich Search Results

Future search results could include:

- Syntax highlighting
- Matching line numbers
- Code previews
- Jump-to-definition
- Related functions
- Confidence indicators

---

## Long-Term Vision

The long-term goal of CodeSense is to evolve from a command-line semantic search engine into a complete AI-assisted code exploration platform.

```
Today

CLI Semantic Search

        │

        ▼

Desktop / Web Application

        │

        ▼

IDE Integration

        │

        ▼

AI-Powered Code Assistant
```

Potential capabilities include:

- Conversational code search
- Repository-wide code understanding
- Automatic documentation generation
- Code summarization
- AI-assisted navigation
- Context-aware developer assistance

---

## Roadmap

| Feature | Status |
|---------|:------:|
| Semantic Search | ✅ |
| Tree-sitter Parsing | ✅ |
| Vector Embeddings | ✅ |
| HNSW Search | ✅ |
| CLI Application | ✅ |
| Multi-Language Support | ⏳ |
| Incremental Indexing | ⏳ |
| GUI | ⏳ |
| VS Code Extension | ⏳ |
| GitHub Repository Indexing | ⏳ |
| Advanced Ranking | ⏳ |
| AI Code Assistant | 🚀 |

CodeSense has established the core components of a semantic code search engine. Future development will focus on improving scalability, usability, and intelligent code understanding while preserving the modular architecture of the current implementation.




---

# License

This project is licensed under the **MIT License**.

The MIT License is a permissive open-source license that allows anyone to:

- ✅ Use the project for personal or commercial purposes
- ✅ Modify the source code
- ✅ Distribute copies of the project
- ✅ Create derivative works
- ✅ Include the project in larger software systems

The only requirement is that the original copyright and license notice remain included in all copies or substantial portions of the software.

See the [LICENSE](LICENSE) file for the complete license text.

---

# Acknowledgements

CodeSense was made possible by several outstanding open-source projects and libraries.

Special thanks to:

- **Tree-sitter** — Robust incremental parsing library for source code.
- **Sentence Transformers** — Semantic embedding generation for code and natural language.
- **HNSWLIB** — High-performance Approximate Nearest Neighbor search.
- **nlohmann/json** — Modern C++ JSON library.
- **CMake** — Cross-platform build system.
- **Python** — Used for embedding generation and model integration.

Their contributions to the open-source ecosystem made this project possible.

---

# Author

**Aditya Dutta**

- GitHub: **https://github.com/Aditya-duttaa**

If you found this project interesting, consider giving it a ⭐ on GitHub. Feedback, suggestions, and contributions are always welcome!

---

# Project Summary

CodeSense demonstrates how modern AI techniques can transform traditional code search into semantic search.

By combining:

- 🌳 Tree-sitter for accurate code parsing
- 🧠 Sentence Transformers for semantic embeddings
- ⚡ HNSW for efficient vector search
- 💻 Modern C++ for high-performance implementation

the project enables developers to search large codebases using natural language instead of exact keyword matching.

Whether you're exploring unfamiliar repositories, locating specific functionality, or learning about semantic search systems, CodeSense showcases the fundamental ideas behind AI-powered code retrieval.

---

<div align="center">

### ⭐ If you like this project, consider giving it a star!

**Thanks for visiting the repository!**

</div>