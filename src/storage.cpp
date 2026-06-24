#include "storage.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

void Storage::saveIndex(
    unordered_map<
        string,
        unordered_map<string, vector<int>>
    >& index,

    string filename
)
{

    ofstream file(filename);


    if(!file)
    {
        cout<<"Unable to open storage file\n";
        return;
    }



    for(auto &wordEntry : index)
    {

        string word = wordEntry.first;


        file << word << "\n";



        for(auto &docEntry : wordEntry.second)
        {

            file << docEntry.first << " ";


            file << docEntry.second.size() << " ";


            for(int pos : docEntry.second)
            {

                file << pos << " ";

            }


            file << "\n";

        }


        file << "#\n";

    }



    file.close();


}









unordered_map<
string,
unordered_map<string, vector<int>>
>
Storage::loadIndex(
    string filename
)
{


    unordered_map<
        string,
        unordered_map<string, vector<int>>
    >
    index;



    ifstream file(filename);



    if(!file)
    {
        cout<<"No saved index found\n";
        return index;
    }



    string word;



    while(getline(file,word))
    {


        if(word=="")
            continue;



        if(word=="#")
            continue;



        string line;



        while(getline(file,line))
        {


            if(line=="#")
                break;



            stringstream ss(line);



            string document;


            int count;



            ss >> document >> count;



            vector<int> positions;



            for(int i=0;i<count;i++)
            {

                int pos;

                ss >> pos;


                positions.push_back(pos);

            }



            index[word][document] =
                positions;


        }


    }



    file.close();



    return index;

}