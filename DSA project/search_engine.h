#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <bits/stdc++.h>

using namespace std;


class SearchEngine {

private:

    // word -> document -> positions
    unordered_map<string, unordered_map<string, vector<int>>> index;


    // document -> total words
    unordered_map<string, int> documentWordCount;


    unordered_set<string> stopWords;


    string normalize(string word);

    bool binarySearch(vector<int>& arr, int target);


    int phraseFrequency(
        string phrase,
        string filename
    );


public:


    SearchEngine();


    // indexing
    void loadDocuments(string path);

    void addDocument(string filename);



    // searching
    vector<pair<string,int>> searchWord(string word);


    vector<pair<string,int>> searchPhrase(string phrase);



    // getters for ranker/storage

    unordered_map<string,
    unordered_map<string, vector<int>>>& getIndex();


    unordered_map<string,int>& getDocumentWordCount();


};


#endif