#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "../include/User.h"
#include "../include/Session.h"
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
    //finding user average length
    int lengthaAcumulator = 0;
    int counter = 0;
//    vector<Watchable*> CurrHistory = s.get_activeUser()->;
//    for (auto x : ){
//        lengthaAcumulator =
//    }

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
