# Mini Search Engine (C++)

A simple search engine in C++ using inverted indexing, TF-IDF ranking, phrase search, and trie-based autocomplete.

## Features

- Inverted index (word → document → positions)
- Word search with TF-IDF + frequency ranking
- Phrase search using positional matching
- Autocomplete using Trie
- Index storage and loading support
- Evaluation module (WIP, not integrated)

## Build

```bash
g++ src/main.cpp src/search_engine.cpp src/ranker.cpp src/preprocessing.cpp src/storage.cpp src/evaluation.cpp -Iinclude -o search