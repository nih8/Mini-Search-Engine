#include "preprocessing.h"
#include <cctype>
#include <bits/stdc++.h>

Preprocessor::Preprocessor()
{

    string words[] = {

        "a","an","the",
        "and","or","but",
        "if","is","am",
        "are","was","were",
        "be","been",
        "to","from",
        "in","on","at",
        "for","with",
        "of","this",
        "that","these",
        "those","it",
        "they","we",
        "you"

    };


    for(string w : words)
    {
        stopWords.insert(w);
    }

}





string Preprocessor::normalize(string word)
{


    for(char &c : word)
    {
        c = tolower(c);
    }



    while(!word.empty() && ispunct(word.back()))
    {
        word.pop_back();
    }



    while(!word.empty() && ispunct(word.front()))
    {
        word.erase(word.begin());
    }



    return word;

}






vector<string>
Preprocessor::tokenize(string text)
{


    vector<string> tokens;


    string current;


    for(char c : text)
    {


        if(c==' ')
        {

            if(!current.empty())
            {

                current = normalize(current);


                if(!isStopWord(current))
                    tokens.push_back(current);


                current.clear();

            }

        }

        else
        {
            current+=c;
        }

    }



    if(!current.empty())
    {

        current = normalize(current);


        if(!isStopWord(current))
            tokens.push_back(current);

    }



    return tokens;

}







bool Preprocessor::isStopWord(string word)
{

    return stopWords.find(word)
            != stopWords.end();

}