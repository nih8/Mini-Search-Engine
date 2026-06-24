#include "ranker.h"

#include <cmath>


Ranker::Ranker(
    unordered_map<string, vector<string>> docs
){

    documents = docs;

}




double Ranker::calculateTF(
    string word,
    string document
){

    if(documents.find(document)==documents.end())
        return 0;


    int count = 0;


    for(string &w : documents[document]){

        if(w == word)
            count++;

    }


    if(documents[document].size()==0)
        return 0;


    return (double)count /
           documents[document].size();

}





double Ranker::calculateIDF(
    string word
){

    int totalDocuments =
        documents.size();


    int containingDocuments = 0;


    for(auto &doc:documents){


        bool found=false;


        for(string &w:doc.second){

            if(w==word){

                found=true;
                break;

            }

        }


        if(found)
            containingDocuments++;

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
    string document
){

    return calculateTF(word,document)
           *
           calculateIDF(word);

}





vector<pair<string,double>>
Ranker::rankDocuments(
    string query
){

    vector<pair<string,double>> result;


    stringstream ss(query);

    vector<string> words;

    string temp;


    while(ss>>temp)
        words.push_back(temp);



    for(auto &doc:documents){


        double score=0;


        for(string &word:words){

            score += calculateTFIDF(
                word,
                doc.first
            );

        }


        if(score>0)
            result.push_back({
                doc.first,
                score
            });

    }




    sort(
        result.begin(),
        result.end(),
        [](auto &a, auto &b){

            return a.second>b.second;

        }
    );


    return result;

}