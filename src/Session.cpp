#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include "../include/Session.h"
#include "../include/json.hpp"
#include "../include/Watchable.h"
#include "../include/User.h"
#include <fstream>

using namespace std;

Session::~Session() {}

Session::Session(const std::string &configFilePath) {
    inputMsg;
    actionsLog;
    activeUser = 0;
    unordered_map<std::string, User *> userMap;
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
    for (auto &x : movies.items()) {
        json movie = x.value();
        string currMovieName = movie["name"];
        int currMovieLength = movie["length"];

        //making tags in to string vector tags
        vector<string> currMovietags;
        for (auto &y : movie["tags"]) {
            string currTag = y;
            currMovietags.push_back(currTag);
        }
        Watchable *currMovie = new Movie(movie_Id, currMovieName, currMovieLength, currMovietags);
        content.push_back(currMovie);
        movie_Id++;
    }

    //inserting Episodes into content
    long episode_Id = 1;
    json series = j["tv_series"];
    for (auto &x : series.items()) {
        json tv_Show = x.value();
        string currtvShowName = tv_Show["name"];
        int currtvShowLength = tv_Show["episode_length"];
        //making tags in to string vector tags
        vector<string> currtvShowtags;
        for (auto &y : tv_Show["tags"]) {
            string currTag = y;
            currtvShowtags.push_back(currTag);
        }
        int seasonCounter = 1;
        for (auto &season : tv_Show["seasons"]) {
            for (int i = 1; i <= season; i++) {
                Watchable *currEpisode = new Episode(episode_Id, currtvShowName, currtvShowLength, seasonCounter, i,
                                                     currtvShowtags);
                content.push_back(currEpisode);
                episode_Id++;
            }
            seasonCounter++;
        }
    }
}

void Session::start() {
    std::cout << "SPLflix is now on!" << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    string input;
    cin >> input;
    inputMsg = interpreter(input);
    while (inputMsg[0] != "exit") {
        if (inputMsg[0] == "createuser" && inputMsg.size() == 3) {
            CreateUser *actCreate = new CreateUser();
            actCreate->act(*this);
        }
        if (inputMsg[0] == "changeuser" && inputMsg.size() == 2) {
            ChangeActiveUser *changeUser = new ChangeActiveUser();
            changeUser->act(*this);
        }
        if (inputMsg[0] == "deleteuser" && inputMsg.size() == 2) {
            DeleteUser *deleteUser = new DeleteUser();
            deleteUser->act(*this);
        }
//        if (inputMsg[0] == "dupuser" && inputMsg.size() == 3) {
//            DuplicateUser *dupUser = new DuplicateUser();
//            dupUser->act(*this);
//        }
//        if (inputMsg[0] == "content" && inputMsg.size() == 1) {
//            PrintContentList *contentList = new PrintContentList();
//            contentList->act(*this);
//        }
//        if (inputMsg[0] == "watchhist" && inputMsg.size() == 1) {
//            PrintWatchHistory *watchList = new PrintWatchHistory();
//            watchList->act(*this);
//        }
//        if (inputMsg[0] == "watch" && inputMsg.size() == 2) {
//            Watch *watch = new Watch();
//            watch->act(*this);
//        }
//        if (inputMsg[0] == "log" && inputMsg.size() == 1) {
//            PrintActionsLog *actionLog = new PrintActionsLog();
//            actionLog->act(*this);
//        } else { cout << "the syntax isn't right- please type again" << endl;
        }


    }



//analyzing the user's input
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

const vector<string> Session::getMsg() const {
    return inputMsg;
}

void Session::insertUser(User *newUser) {
    userMap.insert({newUser->getName(), newUser});
}

//check if the pointer not points on garbadge

void Session::setActiveUser(const User *actUser) {
    activeUser = const_cast<User *>(actUser);
}

void Session::addActionLog(BaseAction *newAction) {
    actionsLog.push_back((BaseAction *const) newAction);
}

bool Session::insertNewUser() {
    if (userMap.find(inputMsg[1]) == userMap.end()) {
        if (inputMsg[2] == "len") {
            LengthRecommenderUser* inputUser = new LengthRecommenderUser(inputMsg[1]);
            Session::setActiveUser(inputUser);
            Session::insertUser(inputUser);
        } else if (inputMsg[2] == "rer") {
            RerunRecommenderUser* inputUser = new RerunRecommenderUser(inputMsg[1]);
            Session::setActiveUser(inputUser);
            Session::insertUser(inputUser);
        } else if (inputMsg[2] == "gen") {
            GenreRecommenderUser* inputUser = new GenreRecommenderUser(inputMsg[1]);
            Session::setActiveUser(inputUser);
            Session::insertUser(inputUser);
        } else {
            return false;
        }
        return true;
    }
    return false;
}

bool Session::changeActiveUser(string userName) {
    unordered_map<std::string,User*>::iterator iter;
    iter= userMap.find(userName);
    if (iter == userMap.end())
        return false;
    else{
        if(activeUser->getName()==userName)
            return true;
        activeUser=iter->second;
    }
    return true;
}

bool Session::deleteUser(string userName) {
    unordered_map<std::string,User*>::iterator iter;
    iter= userMap.find(userName);
    if (iter == userMap.end())
        return false;
    else{
        if(iter->first==activeUser->getName())
        {
            //needs to update a default user which will replace the active user
        }
        else{
            //decide how to delete- first delete the user and than in the map or just release the map memory
        }
    }
    return true;
}
