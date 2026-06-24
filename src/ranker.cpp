#include "ranker.h"
#include <bits/stdc++.h>


double Ranker::calculateTF(
    string word,
    string document,
    unordered_map<
        string,
        unordered_map<string,vector<int>>
    >& index
)
{


    if(index.find(word)==index.end())
        return 0;



    if(index[word].find(document)
        == index[word].end())
        return 0;



    int frequency =
    index[word][document].size();



    int totalWords = 0;



    for(auto &entry:index)
    {

        if(entry.second.find(document)
            != entry.second.end())
        {

            totalWords +=
            entry.second[document].size();

        }

    }



    if(totalWords==0)
        return 0;



    return (double)frequency/totalWords;

}









double Ranker::calculateIDF(
    string word,
    unordered_map<
        string,
        unordered_map<string,vector<int>>
    >& index
)
{


    int totalDocuments = 0;


    unordered_set<string> docs;



    for(auto &entry:index)
    {

        for(auto &doc:entry.second)
        {
            docs.insert(doc.first);
        }

    }


    totalDocuments = docs.size();



    int containingDocuments = 0;



    if(index.find(word)!=index.end())
    {
        containingDocuments =
        index[word].size();
    }



    if(containingDocuments==0)
        return 0;



    return log(
        (double)totalDocuments /
        containingDocuments
    );

}








double Ranker::calculateTFIDF(
    string word,
    string document,
    unordered_map<
        string,
        unordered_map<string,vector<int>>
    >& index
)
{

    return calculateTF(
        word,
        document,
        index
    )
    *
    calculateIDF(
        word,
        index
    );

}



vector<pair<string,double>>
Ranker::rankDocuments(
    vector<string> queryWords,
    unordered_map<
        string,
        unordered_map<string,vector<int>>
    >& index
)
{

    unordered_map<string,double> scores;


    for(string word : queryWords)
    {

        if(index.find(word)==index.end())
            continue;


        for(auto &doc : index[word])
        {

            string filename = doc.first;


            // TF-IDF part
            double tfidf =
            calculateTFIDF(
                word,
                filename,
                index
            );


            // Frequency boost
            double frequency =
            doc.second.size();



            // normalize frequency
            frequency =
            frequency / 100.0;



            double finalScore =
            (0.7 * tfidf)
            +
            (0.3 * frequency);



            scores[filename]
            += finalScore;


        }

    }



    vector<pair<string,double>> result;



    for(auto &x : scores)
    {
        result.push_back(x);
    }




    sort(
        result.begin(),
        result.end(),

        [](auto &a, auto &b)
        {
            return a.second > b.second;
        }

    );



    return result;

}