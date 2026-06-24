#ifndef STORAGE_H
#define STORAGE_H

#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>


using namespace std;



class Storage
{


public:


    void saveIndex(
        unordered_map<
            string,
            unordered_map<string,vector<int>>
        >& index,

        string filename = "index.txt"
    );




    unordered_map<
        string,
        unordered_map<string,vector<int>>
    >

    loadIndex(
        string filename = "index.txt"
    );



};



#endif