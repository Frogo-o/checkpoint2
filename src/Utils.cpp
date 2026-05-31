#include "../include/Utils.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

string todayDate()
{
    time_t now = time(nullptr);
    tm local{};
#ifdef _WIN32
    localtime_s(&local, &now);
#else
    localtime_r(&now, &local);
#endif
    ostringstream out;
    out << put_time(&local, "%Y-%m-%d");
    return out.str();
}

string readLine(const string &prompt)
{
    cout << prompt;
    string value;
    getline(cin, value);
    return value;
}

int readInt(const string &prompt)
{
    cout << prompt;
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}


