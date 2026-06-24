# 🧭 Mini Search Engine (C++)

A mini text search engine built using C++ data structures and algorithms.
It supports Word Search, Phrase Search, and Trie-based Autocomplete across multiple text documents.

## Features

- Document indexing using inverted index
- Stores word positions for efficient retrieval
- Frequency-based word ranking
- Exact phrase matching using positional indexing
- Trie-based autocomplete
- Text normalization (lowercase + punctuation removal)
- Persistent index storage

## How It Works

1. Load text documents
2. Normalize and process words
3. Build inverted index:
unordered_map<string, unordered_map<string, vector<int>>>


4. Perform search operations:
   - Word search
   - Phrase search
   - Autocomplete

## Word Search

Retrieves documents containing a word and ranks them based on occurrence frequency.

## Phrase Search

Uses stored word positions to verify exact sequential phrase matches.

## Autocomplete

Uses Trie data structure to return matching word prefixes.

## How to Run

```bash
g++ src/main.cpp src/search_engine.cpp src/storage.cpp src/ranker.cpp -Iinclude -std=c++17 -o search

./search