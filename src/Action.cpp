#include"../include/json.hpp"
#include"../include/Session.h"
#include "../include/Action.h"
#include "../include/User.h"
#include<fstream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;


BaseAction::BaseAction() : errorMsg(""), status(PENDING) {};

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status = COMPLETED;
}

void BaseAction::error(const std::string &errorMsg) {
    status = ERROR;
    cout << errorMsg << endl;
}

std::string BaseAction::getErrorMsg() const {
    return "";
}

//Create user class------------------------------------------------------------------
void CreateUser::act(Session &sess) {
    if (!sess.insertNewUser()) {
        BaseAction::error("There was a problem- please try to rewrite");
    }
    sess.addActionLog(this);
    complete();
}

std::string CreateUser::toString() const {
    std::string output = "tried to create a new user and the status is" + getStatus();
    return output;
}

//Change Active user--------------------------------------------------------------
void ChangeActiveUser::act(Session &sess) {
    if (!sess.changeActiveUser(sess.getMsg()[1])) {
        BaseAction::error("There was a problem- please try to rewrite");
    }
    sess.addActionLog(this);
    complete();
}

std::string ChangeActiveUser::toString() const {
    string output = "tried to change the active user and the status is:" + getStatus();
    return output;
}

//Delete user----------------------------------------------------------------------
void DeleteUser::act(Session &sess) {
    if (!sess.deleteUser(sess.getMsg()[1])) {
        BaseAction::error("There was a problem- please try to rewrite");
    }
    sess.addActionLog(this);
    complete();
}
std::string DeleteUser::toString() const {
    string output = "tried to delete the given user name and the status is" + getStatus();
    return output;
}


