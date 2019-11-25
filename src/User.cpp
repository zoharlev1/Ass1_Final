#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "../include/User.h"
#include "../include/Session.h"
#include "../include/Watchable.h"
#include <cstdlib>
#include  <cmath>
using namespace std;

////User Constructor
User::User(const std::string &name):name(name){}

////User getName method
string User::getName() const {
    return name;
}

////User get_history method
vector<Watchable*> User::get_history() const {
    return history;
}
////class LengthRecommenderUser--------------------------------------------
/// LengthRecommenderUser constructor
LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name) {}

/// LengthRecommenderUser getRecommendation virtual method
///  --  It will recommend the content whose length is closest to the
///       average length of the content in the user's watch history, and which isn't in the user's watch history

/// get history user history vector, iterate on it and find the average length, now iterate on content vector while saving content
/// with minimum difference between average and current content length. check if current content is in history vector
Watchable* LengthRecommenderUser::getRecommendation(Session& s) {
    Watchable* output = nullptr;
    User& currUser = s.get_activeUser();
    vector<Watchable*> currHistory = currUser.get_history();
    //if the user has just finished watching an episode we need to recommend the next episode if there is one
    if(currHistory[currHistory.size()-1]-> ){

    }


    //finding user average length
    int lengthaAcumulator = 0;
    int counter = 0;
    for (Watchable* x : currHistory){
        int currLength = x->get_length();
        lengthaAcumulator = lengthaAcumulator + currLength;
        counter++;
    }
    int averageLength = lengthaAcumulator/counter;

    vector<Watchable*> currContent = s.get_content();
    int minLengthDifference = INT_MAX;
    bool watched = false;
    for(Watchable* nextWatchCanidate : currContent){
        int currLength = nextWatchCanidate->get_length();
        if(abs(averageLength-currLength) < minLengthDifference){
            for(int i=0 ; i<currHistory.size() && !watched; i++){
                  if(currHistory[i]->get_id() == nextWatchCanidate->get_id()){
                      watched = true;
                  }
            }
            if(!watched){
                minLengthDifference = abs(averageLength-currLength);
                output = nextWatchCanidate;
            }
            watched = false;
        }
    }

    return output;
}

///-----------------------------------------------------------------------

///class RerunRecommenderUser----------------------------------------------
///RerunRecommenderUser constructor
RerunRecommenderUser::RerunRecommenderUser(const std::string &name) :User(name){}

///RerunRecommenderUser getRecommendation virtual method
Watchable* RerunRecommenderUser::getRecommendation(Session &s) {

}
///-------------------------------------------------------------------------------
///class GenreRecommenderUser-----------------------------------------------------
/// GenreRecommenderUser constructor
GenreRecommenderUser::GenreRecommenderUser(const std::string &name):User(name) {}

///GenreRecommenderUser getRecommendation virtual method
Watchable* GenreRecommenderUser::getRecommendation(Session &s) {

}
