#include "../include/Member.h"

#include <utility>

using namespace std;

Member::Member(string name, string email) : name(move(name)), email(move(email)) {}
const string &Member::getName() const { return name; }
const string &Member::getEmail() const { return email; }
string Member::serialize() const { return name + "<" + email + ">"; }


