#include "../include/BoardItem.h"

#include <utility>

using namespace std;

BoardItem::BoardItem(int id, string title, string description, string createdAt)
    : id(id), title(move(title)), description(move(description)), createdAt(move(createdAt)) {}

int BoardItem::getId() const { return id; }
const string &BoardItem::getTitle() const { return title; }
const string &BoardItem::getDescription() const { return description; }
const string &BoardItem::getCreatedAt() const { return createdAt; }
void BoardItem::setTitle(const string &value) { title = value; }
void BoardItem::setDescription(const string &value) { description = value; }


