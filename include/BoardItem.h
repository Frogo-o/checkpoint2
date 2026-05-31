#ifndef BOARD_ITEM_H
#define BOARD_ITEM_H

#include <string>

using namespace std;

class BoardItem {
protected:
    int id;
    string title;
    string description;
    string createdAt;

public:
    BoardItem(int id, string title, string description, string createdAt);
    virtual ~BoardItem() = default;
    int getId() const;
    const string &getTitle() const;
    const string &getDescription() const;
    const string &getCreatedAt() const;
    void setTitle(const string &value);
    void setDescription(const string &value);
    virtual void displayInfo() const = 0;
};

#endif


