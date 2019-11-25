#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include "../include/Session.h"
#include "../include/json.hpp"
#include "../include/Watchable.h"
#include <fstream>
using namespace std;

 Session::~Session() {}

 Session::Session(const std::string &configFilePath) {
     using json = nlohmann::json;
    json j;
    //Line below is just for test
    //std::ifstream ifs("../include/config1.json");
    std::ifstream ifs(configFilePath);
    ifs >> j;
    ifs.close();
    //making <Watchable*> content


    //inserting movies into content
    long movie_Id = 1;
    json movies = j["movies"];
    for(auto &x : movies.items()){
        json movie = x.value();
        string currMovieName = movie["name"];
        int currMovieLength = movie["length"];

        //making tags in to string vector tags
        vector<string> currMovietags;
        for(auto &y : movie["tags"]){
            string currTag = y;
            currMovietags.push_back(currTag);
        }
        auto* currMovie = new Movie(movie_Id, currMovieName, currMovieLength, currMovietags);
        content.push_back(currMovie);
        movie_Id++;
    }

    //inserting Episodes into content
    long episode_Id = 1;
    json series = j["tv_series"];
     for(auto &x : series.items()) {
         json tv_Show = x.value();
         string currtvShowName = tv_Show["name"];
         int currtvShowLength = tv_Show["episode_length"];
         //making tags in to string vector tags
         vector<string> currtvShowtags;
         for(auto &y : tv_Show["tags"]){
             string currTag = y;
             currtvShowtags.push_back(currTag);
         }

         int seasonCounter = 1;
         bool episodeCarry = false;
         Episode* currEpisode;
         for(auto &season : tv_Show["seasons"]){
             for(int i=1; i <= season; i++){
                 currEpisode = new Episode(episode_Id,currtvShowName,currtvShowLength,seasonCounter,i,currtvShowtags);
                 content.push_back(currEpisode);
                 episode_Id++;
                 //set next episode to id+1
                 currEpisode->set_nextEpisodeId(long(episode_Id));
             }
             seasonCounter++;
         }
         //setting next episode_id to null
         currEpisode->set_nextEpisodeId(long(0));
     }
 }

void Session::start() {
    cout<<"SPLflix is now on!"<<endl;
    cout<<"What would you like to do?"<<endl;
    string input;
    cin >> input;
    //vector<string> strV=interpeter(input);
    //inputMsg = strV;
//    while(strV[0]!="exit")
//    {
//        if(strV[0]=="createuser" && strV.size()==3)
//        {
//            CreateUser *actCreate= new CreateUser();
//            actCreate->act(*this);
//        }
//        if(strV[0]=="changeuser" && strV.size()==2)
//        {
//            ChangeActiveUser *changeUser= new ChangeActiveUser();
//            changeUser->act(*this);
//        }
//        if(strV[0]=="deleteuser" && strV.size()==2)
//        {
//            DeleteUser *deleteUser= new DeleteUser();
//            deleteUser->act(*this);
//        }
//        if(strV[0]=="dupuser" && strV.size()==3)
//        {
//            DuplicateUser *dupUser= new DuplicateUser();
//            dupUser->act(*this);
//        }
//        if(strV[0]=="content" && strV.size()==1)
//        {
//            PrintContentList *contentList= new PrintContentList();
//            contentList->act(*this);
//        }
//        if(strV[0]=="watchhist" && strV.size()==1)
//        {
//            PrintWatchHistory *watchList= new PrintWatchHistory();
//            watchList->act(*this);
//        }
//        if(strV[0]=="watch" && strV.size()==2)
//        {
//            Watch *watch= new Watch();
//            watch->act(*this);
//        }
//        if(strV[0]=="log" && strV.size()==1)
//        {
//            PrintActionsLog *actionLog= new PrintActionsLog();
//            actionLog->act(*this);
//        }
//
//        else {cout<<"the syntax isn't right- please type again"<<endl;}
//

   // }

}



////analyzing the user's input
    vector<string> Session::interpreter(string input) {
        vector<string> strV;
        string word = "";
        for (auto x : input) {
            if (x == ' ') {
                strV.push_back(word);//push to the vector
                word = "";
            } else {
                word = word + x;
            }
        }
        return strV;
    }

/// get_activeUser Method
User& Session::get_activeUser() const {
     return *activeUser;
 }

 /// get content vector method
 vector<Watchable*> Session::get_content() const {
     return content;
 }





