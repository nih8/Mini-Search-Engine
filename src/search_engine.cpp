#include "search_engine.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <cctype>

#include "../src/search.cpp"


namespace fs = std::filesystem;



SearchEngine::SearchEngine(){

    trie = new Trie();


    non_imp_words = {

        "a","an","the","and","or","but",
        "if","about","against",
        "between","into","through",
        "during","before","after",
        "above","below","to","from",
        "up","down","in","out",
        "on","off","over","under",
        "again","then","once",
        "here","there","when",
        "where","why","how",
        "all","any","both",
        "each","few","more",
        "most","other","some",
        "such","no","nor",
        "not","only","own",
        "same","so","than",
        "too","very","can",
        "will","just","is",
        "am","are","was",
        "were","be","been",
        "being","have","has",
        "had","having",
        "do","does","did",
        "this","that",
        "these","those"

    };

}





string SearchEngine::normalize(string word){


    for(char &c : word)
        c = tolower(c);



    while(!word.empty() && ispunct(word.back()))
        word.pop_back();



    while(!word.empty() && ispunct(word.front()))
        word.erase(word.begin());



    return word;

}







bool SearchEngine::binarySearch(
    vector<int>& positions,
    int target
){

    int left = 0;
    int right = positions.size()-1;


    while(left <= right){

        int mid = (left+right)/2;


        if(positions[mid] == target)
            return true;


        else if(positions[mid] < target)
            left = mid+1;


        else
            right = mid-1;

    }


    return false;

}









void SearchEngine::loadDocuments(string path){


    for(auto &entry : fs::directory_iterator(path))
    {


        if(entry.path().extension() != ".txt")
            continue;



        string filename = entry.path().string();



        ifstream file(filename);



        if(!file)
            continue;



        string line;
        string word;


        int position = 1;



        while(getline(file,line))
        {

            stringstream ss(line);



            while(ss >> word)
            {

                word = normalize(word);



                if(word.empty())
                    continue;



                global_index[word][filename]
                    .push_back(position);



                trie->insert(word);



                position++;

            }

        }


        file.close();

    }

}









vector<pair<string,int>>
SearchEngine::searchWord(string word)
{


    word = normalize(word);



    vector<pair<string,int>> result;



    if(global_index.find(word)
        == global_index.end())
    {
        return result;
    }




    for(auto &doc : global_index[word])
    {

        result.push_back({

            doc.first,

            (int)doc.second.size()

        });

    }




    sort(
        result.begin(),
        result.end(),

        [](auto &a, auto &b){

            return a.second > b.second;

        }

    );



    return result;

}









int SearchEngine::phraseMatchCount(
    string phrase,
    string filename
){


    stringstream ss(phrase);


    vector<string> words;


    string temp;



    while(ss >> temp)
    {
        words.push_back(
            normalize(temp)
        );
    }




    if(words.empty())
        return 0;



    int count = 0;




    for(int pos : global_index[words[0]][filename])
    {


        bool match = true;


        int current = pos;




        for(int i=1;i<words.size();i++)
        {


            vector<int> &next =
                global_index[words[i]][filename];



            if(!binarySearch(
                    next,
                    current+1
                ))
            {

                match=false;
                break;

            }



            current++;

        }



        if(match)
            count++;

    }



    return count;

}









vector<pair<string,int>>
SearchEngine::searchPhrase(string phrase)
{


    vector<pair<string,int>> result;



    for(auto &word : global_index)
    {


        for(auto &doc : word.second)
        {


            int freq =
                phraseMatchCount(
                    phrase,
                    doc.first
                );



            if(freq > 0)
            {

                result.push_back({

                    doc.first,

                    freq

                });


                break;

            }

        }

    }




    sort(
        result.begin(),
        result.end(),

        [](auto &a, auto &b){

            return a.second > b.second;

        }

    );



    return result;

}









void SearchEngine::autocomplete(string word)
{

    trie->autocomplete(word);

}









unordered_map<
string,
unordered_map<string,vector<int>>
>& SearchEngine::getIndex()
{

    return global_index;

}