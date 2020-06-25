/*
* Title: Graphs
* Author: Isik Ozsoy
* ID: 21703160
* Section: 1
* Assignment: 3
* Description: cpp file of Person
*/

#include <string>
#include <iostream>
#include "Person.h"
using namespace std;

// Constructor
Person :: Person( int id, string name, int degree) {
    this -> id = id;
    this -> name = name;
    this -> degree = degree;
    friends = new int[degree];
}

// Default constructor
Person :: Person() {

}

Person :: Person( const Person& aPerson) {
    id = aPerson.id;
    name = aPerson.name;
    degree = aPerson.degree;
    friends = new int[degree];
    for(int i = 0; i < degree; i++)
        friends[i] = (aPerson.friends)[i];
}

// Destructor
Person :: ~Person() {
    if(friends)
        delete [] friends;
}

// Copies the given person
void Person :: createPerson(Person* personToCopy)
{
    id = personToCopy->id;
    name = personToCopy->name;
    degree = personToCopy->degree;
    friends = new int[degree];
    for( int i = 0; i < degree; i++)
        friends[i] = personToCopy->friends[i];
}

// Method that set the friends
void Person :: setFriends( int* friends) {
    for( int i = 0; i < degree; i++)
        this->friends[i] = friends[i];
}

// Returns the name of the person
string Person :: getName() {
    return name;
}

// Returns the degree of the person
int Person:: getDegree() {
    return degree;
}

int Person::getId() {
    return id;
}

// Returns the id of the friend in the given index
int Person :: getFriendId(int i) {
    return friends[i];
}
