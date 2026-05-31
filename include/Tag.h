#ifndef TAG_H
#define TAG_H

#include <string>

using namespace std;

class Tag {
    string name;

public:
    Tag(string name = "");
    const string &getName() const;
};

#endif


