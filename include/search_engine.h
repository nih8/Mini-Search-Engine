#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Trie;


class SearchEngine
{

private:

    unordered_map<
        string,
        unordered_map<string, vector<int>>
    > global_index;


    unordered_map<string,bool> stop_words;


    Trie* trie;



public:

    SearchEngine();


    ~SearchEngine();



    void loadDocuments(string path);



    vector<pair<string,double>>
    searchWord(string query);



    vector<pair<string,double>>
    searchPhrase(string phrase);



    void autocomplete(string prefix);



    unordered_map<
        string,
        unordered_map<string, vector<int>>
    >& getIndex();



    vector<string> getDocuments();



private:


    string normalize(string word);



    bool binarySearch(
        vector<int>& positions,
        int target
    );



    int phraseMatchCount(
        string phrase,
        string filename
    );


};

#endif