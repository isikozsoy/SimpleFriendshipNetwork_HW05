/*
* Title: Graphs
* Author: Isik Ozsoy
* ID: 21703160
* Section: 1
* Assignment: 5
* Description: header file of Person
*/

#ifndef Person_h
#define Person_h

#include <string>
using namespace std;

class Person {
public:
    Person();
    Person( int, string, int);
    Person( const Person& aPerson);
    ~Person();
    void createPerson(Person*);
    string getName();
    int getDegree();
    int getId();
    int getFriendId(int);
    void setFriends(int*);
private:
    int id;
    string name;
    int degree;
    int* friends;
};
#endif
