#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h"

class User;
class Watchable;
using namespace std;
class Session{
public:
    Session(const std::string &configFilePath);
    ~Session();
    void start();
    vector<string> interpreter(string input);
    User& get_activeUser() const;
    vector<Watchable*> get_content() const;
private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;
    //vector<string> inputMsg;

};
#endif