#include "evaluation.h"
#include <bits/stdc++.h>


double Evaluation::precision(
    vector<string> retrieved,
    vector<string> relevant
)
{


    if(retrieved.empty())
        return 0;



    int correct=0;



    unordered_set<string> rel(
        relevant.begin(),
        relevant.end()
    );



    for(string x:retrieved)
    {

        if(rel.find(x)!=rel.end())
            correct++;

    }



    return (double)correct /
           retrieved.size();

}








double Evaluation::recall(
    vector<string> retrieved,
    vector<string> relevant
)
{


    if(relevant.empty())
        return 0;



    int correct=0;



    unordered_set<string> rel(
        relevant.begin(),
        relevant.end()
    );



    for(string x:retrieved)
    {

        if(rel.find(x)!=rel.end())
            correct++;

    }



    return (double)correct /
           relevant.size();

}