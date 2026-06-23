#include "search_engine.h"

#include <filesystem>

using namespace std;



SearchEngine::SearchEngine(){


    stopWords = {

        "a","an","the",
        "and","or","but",
        "if","is","am","are",
        "was","were",
        "to","from","in",
        "on","at","for",
        "with","of",
        "this","that",
        "these","those",
        "it","they",
        "we","you"

    };

}



/*
    Text normalization

    Example:

    "Hello,"  -> hello
    "WORLD!"  -> world

*/

string SearchEngine::normalize(string word){


    string result;


    for(char c: word){

        if(isalpha(c))
            result += tolower(c);

    }


    return result;

}




bool SearchEngine::binarySearch(
        vector<int>& arr,
        int target
){


    int left = 0;

    int right = arr.size()-1;



    while(left<=right){


        int mid = left+(right-left)/2;


        if(arr[mid]==target)
            return true;


        else if(arr[mid]<target)
            left = mid+1;


        else
            right = mid-1;

    }


    return false;

}





void SearchEngine::loadDocuments(string path){


    for(auto &entry :
        filesystem::directory_iterator(path)){



        if(entry.path().extension()==".txt"){


            addDocument(entry.path().string());


        }

    }


}




void SearchEngine::addDocument(string filename){


    ifstream file(filename);



    if(!file){

        cout<<"Cannot open "
            <<filename<<endl;

        return;

    }



    string word;

    int position = 0;


    while(file >> word){


        word = normalize(word);



        if(word.empty())
            continue;



        if(stopWords.count(word))
            continue;



        index[word][filename]
            .push_back(position);



        position++;

    }



    documentWordCount[filename]=position;


}






vector<pair<string,int>>
SearchEngine::searchWord(string word){



    word = normalize(word);



    vector<pair<string,int>> result;



    if(index.find(word)==index.end())
        return result;



    for(auto &doc:index[word]){


        result.push_back({

            doc.first,

            (int)doc.second.size()

        });


    }



    sort(
        result.begin(),
        result.end(),
        [](auto&a,auto&b){

            return a.second>b.second;

        }
    );


    return result;

}








int SearchEngine::phraseFrequency(
        string phrase,
        string filename
){


    stringstream ss(phrase);


    vector<string> words;


    string temp;


    while(ss>>temp){

        temp = normalize(temp);

        if(!temp.empty())
            words.push_back(temp);

    }



    if(words.empty())
        return 0;




    int count=0;




    for(int pos:
        index[words[0]][filename]){


        bool match=true;


        int current=pos;



        for(int i=1;i<words.size();i++){


            current++;



            if(
                !binarySearch(
                    index[words[i]][filename],
                    current
                )
            ){

                match=false;

                break;

            }

        }



        if(match)
            count++;


    }


    return count;


}







vector<pair<string,int>>
SearchEngine::searchPhrase(string phrase){


    vector<pair<string,int>> result;



    for(auto &doc:documentWordCount){



        int freq =
        phraseFrequency(
            phrase,
            doc.first
        );



        if(freq>0){


            result.push_back({

                doc.first,

                freq

            });


        }

    }




    sort(
        result.begin(),
        result.end(),
        [](auto&a,auto&b){

            return a.second>b.second;

        }
    );



    return result;

}







unordered_map<string,
unordered_map<string, vector<int>>>&
SearchEngine::getIndex(){

    return index;

}







unordered_map<string,int>&
SearchEngine::getDocumentWordCount(){


    return documentWordCount;


}