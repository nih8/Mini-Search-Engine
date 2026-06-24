#include "search_engine.h"

#include "storage.h"
#include <bits/stdc++.h>
#include <iostream>


using namespace std;



int main()
{


    SearchEngine engine;



    cout<<"Loading documents...\n";


    engine.loadDocuments(
        "documents"
    );



    cout<<"Index created successfully\n";



    Storage storage;


    storage.saveIndex(
        engine.getIndex()
    );





    while(true)
    {


        cout<<"\n===== MINI SEARCH ENGINE =====\n";


        cout<<"1. Search Word\n";

        cout<<"2. Search Phrase\n";

        cout<<"3. Autocomplete\n";

        cout<<"4. Exit\n";

        cout<<"Choice: ";



        int choice;

        cin>>choice;


        cin.ignore();





        if(choice==4)
            break;





        if(choice==1)
        {


            string query;


            cout<<"Enter word: ";

            getline(cin,query);




            auto result =
            engine.searchWord(query);




            for(auto &x:result)
            {

                cout
                <<x.first
                <<" score: "
                <<x.second
                <<endl;

            }



        }






        else if(choice==2)
        {


            string phrase;


            cout<<"Enter phrase: ";

            getline(cin,phrase);




            auto result =
            engine.searchPhrase(
                phrase
            );




            for(auto &x:result)
            {

                cout
                <<x.first
                <<" score: "
                <<x.second
                <<endl;


            }


        }







        else if(choice==3)
        {


            string prefix;


            cout<<"Prefix: ";

            cin>>prefix;



            engine.autocomplete(prefix);


        }


    }



    return 0;

}