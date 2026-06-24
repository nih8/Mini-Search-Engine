#include "storage.h"
#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <sstream>


void Storage::saveIndex(
    unordered_map<
        string,
        unordered_map<string,vector<int>>
    >& index,

    string filename
)
{


    ofstream file(filename);



    if(!file)
        return;




    for(auto &word:index)
    {


        file<<word.first<<"\n";



        for(auto &doc:word.second)
        {

            file<<doc.first<<" ";
            file<<doc.second.size()<<" ";


            for(int pos:doc.second)
            {
                file<<pos<<" ";
            }


            file<<"\n";

        }



        file<<"#\n";


    }


    file.close();

}










unordered_map<
string,
unordered_map<string,vector<int>>
>

Storage::loadIndex(string filename)
{


    unordered_map<
    string,
    unordered_map<string,vector<int>>
    >
    index;



    ifstream file(filename);



    if(!file)
        return index;




    string word;



    while(getline(file,word))
    {


        if(word=="#")
            continue;



        string line;



        while(getline(file,line))
        {


            if(line=="#")
                break;



            stringstream ss(line);



            string doc;
            int size;


            ss>>doc>>size;



            vector<int> positions;



            for(int i=0;i<size;i++)
            {

                int p;

                ss>>p;

                positions.push_back(p);

            }



            index[word][doc]=positions;

        }

    }



    return index;

}