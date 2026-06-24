#ifndef EVALUATION_H
#define EVALUATION_H

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>


using namespace std;



class Evaluation
{


public:



    double precision(
        vector<string> retrieved,
        vector<string> relevant
    );




    double recall(
        vector<string> retrieved,
        vector<string> relevant
    );



};



#endif