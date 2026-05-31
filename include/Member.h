#ifndef MEMBER_H
#define MEMBER_H

#include <string>

using namespace std;

class Member {
    string name;
    string email;

public:
    Member(string name = "Unassigned", string email = "");
    const string &getName() const;
    const string &getEmail() const;
    string serialize() const;
};

#endif


