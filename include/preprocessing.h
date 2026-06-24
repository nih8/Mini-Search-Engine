#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>


using namespace std;



class Preprocessor
{


private:


    unordered_set<string> stopWords;



public:


    Preprocessor();



    string normalize(string word);



    vector<string>
    tokenize(string text);



    bool isStopWord(string word);



};



#endif