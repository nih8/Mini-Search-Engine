#include "search_engine.h"
#include <bits/stdc++.h>
#include "preprocessing.h"
#include "ranker.h"

#include "../src/search.cpp"

#include <filesystem>
#include <algorithm>


namespace fs = std::filesystem;



SearchEngine::SearchEngine()
{

    trie = new Trie();


}



SearchEngine::~SearchEngine()
{

    delete trie;

}






string SearchEngine::normalize(string word)
{

    Preprocessor p;

    return p.normalize(word);

}








void SearchEngine::loadDocuments(string path)
{


    for(auto &entry : fs::directory_iterator(path))
    {


        if(entry.path().extension() != ".txt")
            continue;



        string filename =
        entry.path().string();



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









vector<pair<string,double>>
SearchEngine::searchWord(string query)
{


    query = normalize(query);



    vector<string> words;

    words.push_back(query);



    Ranker ranker;



    return ranker.rankDocuments(
        words,
        global_index
    );

}









vector<pair<string,double>>
SearchEngine::searchPhrase(string phrase)
{


    vector<pair<string,double>> result;



    vector<string> documents;



    for(auto &word:global_index)
    {

        for(auto &doc:word.second)
        {

            if(find(
                documents.begin(),
                documents.end(),
                doc.first
            )
            ==
            documents.end())
            {
                documents.push_back(doc.first);
            }

        }

    }




    for(string doc:documents)
    {


        int count =
        phraseMatchCount(
            phrase,
            doc
        );



        if(count>0)
        {

            result.push_back(
            {
                doc,
                (double)count
            });

        }


    }




    sort(
        result.begin(),
        result.end(),

        [](auto&a,auto&b)
        {
            return a.second>b.second;
        }

    );



    return result;


}









int SearchEngine::phraseMatchCount(
    string phrase,
    string filename
)
{


    stringstream ss(phrase);



    vector<string> words;


    string temp;



    while(ss>>temp)
    {

        words.push_back(
            normalize(temp)
        );

    }



    if(words.empty())
        return 0;



    int count=0;




    for(int pos:
        global_index[words[0]][filename])
    {


        bool match=true;



        int current=pos;



        for(int i=1;i<words.size();i++)
        {


            auto &next =
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









bool SearchEngine::binarySearch(
    vector<int>& positions,
    int target
)
{


    int l=0;

    int r=positions.size()-1;



    while(l<=r)
    {


        int mid=(l+r)/2;



        if(positions[mid]==target)
            return true;



        else if(positions[mid]<target)
            l=mid+1;


        else
            r=mid-1;


    }


    return false;

}









void SearchEngine::autocomplete(string prefix)
{

    trie->autocomplete(prefix);

}









unordered_map<
string,
unordered_map<string,vector<int>>
>&

SearchEngine::getIndex()
{

    return global_index;

}








vector<string>
SearchEngine::getDocuments()
{

    vector<string> docs;



    for(auto &word:global_index)
    {

        for(auto &doc:word.second)
        {

            if(find(
                docs.begin(),
                docs.end(),
                doc.first
            )
            ==
            docs.end())
            {
                docs.push_back(doc.first);
            }

        }

    }


    return docs;

}