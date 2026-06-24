#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H


#include <bits/stdc++.h>

using namespace std;


// Trie is present inside search.cpp
class Trie;



class SearchEngine {


private:

    unordered_map<
        string,
        unordered_map<string, vector<int>>
    > global_index;


    Trie* trie;


    unordered_set<string> non_imp_words;



    string normalize(string word);



    bool binarySearch(
        vector<int>& positions,
        int target
    );


    int phraseMatchCount(
        string phrase,
        string filename
    );



public:


    SearchEngine();



    void loadDocuments(
        string path
    );



    vector<pair<string,int>> searchWord(
        string word
    );



    vector<pair<string,int>> searchPhrase(
        string phrase
    );



    void autocomplete(
        string word
    );



    unordered_map<
        string,
        unordered_map<string, vector<int>>
    >& getIndex();



};



#endif