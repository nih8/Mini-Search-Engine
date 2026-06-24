#ifndef RANKER_H
#define RANKER_H

#include <bits/stdc++.h>

using namespace std;


class Ranker {

private:

    unordered_map<string, vector<string>> documents;


public:

    Ranker(
        unordered_map<string, vector<string>> docs
    );


    double calculateTF(
        string word,
        string document
    );


    double calculateIDF(
        string word
    );


    double calculateTFIDF(
        string word,
        string document
    );


    vector<pair<string,double>> rankDocuments(
        string query
    );

};


#endif