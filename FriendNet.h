/*
* Title: Graphs
* Author: Isik Ozsoy
* ID: 21703160
* Section: 1
* Assignment: 5
* Description: header file of FriendNet
*/

#ifndef FriendNet_h
#define FriendNet_h

#include "Person.h"
#include <string>
#include <iostream>
using namespace std;

class FriendNet
{
private:
    int numPeople;
    Person* people;
public:
    FriendNet(const string); // constructor
    FriendNet(const FriendNet&); // copy constructor
    ~FriendNet(); // destructor
    void listFriends(const string, const int);
    void listFriendsRec(int, int, bool*&, int&);
    void displayAverageDegrees();
    void displayAvDegRec(int, int&, int&, bool*&);
    void displayDiameters();
    int bfs( int id);
    int findPersonId( string);
};
#endif
