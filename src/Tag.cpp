#include "../include/Tag.h"

#include <utility>

using namespace std;

Tag::Tag(string name) : name(move(name)) {}
const string &Tag::getName() const { return name; }


