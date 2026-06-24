#ifndef RANKER_H
#define RANKER_H


#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <unordered_set>
#include <algorithm>


using namespace std;



class Ranker
{


public:


    double calculateTF(
        string word,
        string document,
        unordered_map<
            string,
            unordered_map<string, vector<int>>
        >& index
    );




    double calculateIDF(
        string word,
        unordered_map<
            string,
            unordered_map<string, vector<int>>
        >& index
    );





    double calculateTFIDF(
        string word,
        string document,
        unordered_map<
            string,
            unordered_map<string, vector<int>>
        >& index
    );





    vector<pair<string,double>>
    rankDocuments(
        vector<string> queryWords,
        unordered_map<
            string,
            unordered_map<string, vector<int>>
        >& index
    );



};



#endif