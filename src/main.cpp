#include <bits/stdc++.h>

#include "search_engine.h"
#include "ranker.h"
#include "storage.h"


using namespace std;



int main(){


    SearchEngine engine;



    cout<<"Loading documents...\n";


    engine.loadDocuments(
        "./documents"
    );


    cout<<"Documents loaded!\n";



    /*
        Prepare document data
        for TF-IDF ranking
    */


    unordered_map<string,vector<string>> documents;



    auto &index =
        engine.getIndex();



    for(auto &wordEntry:index)
    {

        string word =
            wordEntry.first;



        for(auto &docEntry:
            wordEntry.second)
        {


            string filename =
                docEntry.first;



            int frequency =
                docEntry.second.size();



            for(int i=0;i<frequency;i++)
            {

                documents[filename]
                .push_back(word);

            }

        }

    }



    Ranker ranker(documents);


    Storage storage;




    while(true)
    {


        cout<<"\n====================\n";

        cout<<"1. Search Word\n";
        cout<<"2. Search Phrase\n";
        cout<<"3. Autocomplete\n";
        cout<<"4. TF-IDF Ranked Search\n";
        cout<<"5. Save Index\n";
        cout<<"6. Exit\n";


        cout<<"Choice: ";



        int choice;

        cin>>choice;

        cin.ignore();



        if(choice==6)
            break;




        // -------------------------
        // WORD SEARCH
        // -------------------------

        if(choice==1)
        {


            string word;


            cout<<"Enter word: ";

            getline(cin,word);



            auto result =
            engine.searchWord(word);



            if(result.empty())
            {

                cout<<"No matches found\n";

            }

            else
            {

                cout<<"\nResults:\n";


                for(auto &r:result)
                {

                    cout
                    <<r.first
                    <<" -> "
                    <<r.second
                    <<" occurrences\n";

                }

            }

        }




        // -------------------------
        // PHRASE SEARCH
        // -------------------------

        else if(choice==2)
        {


            string phrase;


            cout<<"Enter phrase: ";

            getline(cin,phrase);



            auto result =
            engine.searchPhrase(
                phrase
            );



            if(result.empty())
            {

                cout<<"No matches found\n";

            }

            else
            {

                cout<<"\nPhrase Results:\n";


                for(auto &r:result)
                {

                    cout
                    <<r.first
                    <<" -> "
                    <<r.second
                    <<" times\n";

                }

            }

        }




        // -------------------------
        // AUTOCOMPLETE
        // -------------------------

        else if(choice==3)
        {


            string word;


            cout<<"Enter prefix: ";

            cin>>word;



            engine.autocomplete(
                word
            );

        }




        // -------------------------
        // TF-IDF SEARCH
        // -------------------------

        else if(choice==4)
        {


            string query;


            cout<<"Enter query: ";

            getline(cin,query);



            auto result =
            ranker.rankDocuments(
                query
            );



            if(result.empty())
            {

                cout<<"No relevant documents\n";

            }

            else
            {

                cout<<"\nRanked Results:\n";


                for(auto &r:result)
                {

                    cout
                    <<r.first
                    <<" Score: "
                    <<r.second
                    <<endl;

                }

            }

        }




        // -------------------------
        // SAVE INDEX
        // -------------------------

        else if(choice==5)
        {


            storage.saveIndex(
                engine.getIndex()
            );


            cout
            <<"Index saved successfully!\n";

        }



        else
        {

            cout<<"Invalid choice\n";

        }



    }



    return 0;

}