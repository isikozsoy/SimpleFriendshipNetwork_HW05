/*
* Title: Graphs
* Author: Isik Ozsoy
* ID: 21703160
* Section: 1
* Assignment: 3
* Description: cpp file of FriendNet
*/

#include "FriendNet.h"
#include "Person.h"
#include "Queue.h"
#include <string>
#include <iostream>
#include <fstream>
#include<bits/stdc++.h>
using namespace std;

// Constructor
FriendNet :: FriendNet( const string fileName)
{
    string str;		                          // str contains lines in file
    ifstream file;
    file.open( fileName);	                  // we open file
    getline( file, str);
    numPeople = stoi( str);
    people = new Person [numPeople];
    int cur = -1;
    int count = 0;
    while( getline( file, str))
    {
        cur = str.find( " ");                        // we find the first index containing space
        int id = stoi( str.substr( 0, cur));         // we save the content up to space as id
        str.erase( 0, cur + 1);

        cur = str.find( " ");                        // we find the first index containing space
        string name = str.substr( 0, cur);           // we save the content up to space as name
        str.erase( 0, cur + 1);

        cur = str.find( " ");                        // we find the first index containing space
        int degree = stoi( str.substr( 0, cur));     // we save the content up to space as degree
        str.erase( 0, cur + 1);

        Person* temp = new Person(id, name, degree);  // we create our person
        int* friends = new int[degree];
        cur = str.find( " ");                         // we find the first index containing space
        int indexFriends = 0;
        while( cur != string :: npos)
        {
            friends[indexFriends] = stoi( str.substr( 0, cur));
            indexFriends++;
            str.erase( 0, cur + 1);
            cur = str.find( " ");                                // we find the first index containing space
        }
        friends[indexFriends] = stoi( str);
        temp->setFriends( friends);                              // we set the friends of the person
        people[count].createPerson(temp);
        count++;
        delete [] friends;                                       // we delete friends pointer array
        delete temp;                                             // we delete temp
    }
}

// Copy Constructor
FriendNet :: FriendNet(const FriendNet& aNet) {
    numPeople = aNet.numPeople;
    people = new Person[numPeople];
    for( int i = 0; i < numPeople; i++) {
        Person* temp = new Person(aNet.people[i]);
        people[i].createPerson(temp);
        delete temp;
    }
}

// Destructor
FriendNet :: ~FriendNet()
{
    if (people)
        delete [] people;
}

// method that takes person name (string) and hop no (int)
// and prints people which are hop no away from entered person
void FriendNet :: listFriends( const string personName, const int hopNo)
{
    int personID = findPersonId( personName);                             // Find the id from the person name
    if( personID == -1)                                                    // If personID is -1, there is no such person
        cout << personName << " does not exist in the network.";
    else if( hopNo < 0)
        cout << "People accessible from " << personName << " within " << hopNo << " hops: NOBODY";
    else
    {
        cout << "People accessible from " << personName << " within " << hopNo << " hops: ";
        int countFriend = 0;
        bool* visited = new bool[numPeople];                              // Boolean array, true if the person is visited, otherwise false
        for(int i = 0; i < numPeople; i++)                                // Initially no person is visited
            visited[i] = false;
        visited[personID] = true;
        listFriendsRec(personID, hopNo, visited, countFriend);            // Call recursive function to find friends
        if( countFriend == 0)
            cout << "NOBODY";
        delete [] visited;                                                // Delete pointer array
    }
    cout << endl;
}

// Recursive method to find people which are hop no away from the given person
void FriendNet :: listFriendsRec( int personID, int hopNo, bool*& visited, int& countFriend)
{
    if( hopNo != 0)
    {
        int degree = people[personID].getDegree();
        for( int i = 0; i < degree; i++)
        {
            int friendID = people[personID].getFriendId(i);
            if( !visited[friendID])
            {
                cout << people[friendID].getName() << " ";
                countFriend++;
                visited[friendID] = true;
            }
            listFriendsRec(friendID, hopNo - 1, visited, countFriend);     // Function is recursively called
        }
    }
}

// Method that returns the id of the person with the given name
int FriendNet :: findPersonId( string personName)
{
    for( int i = 0; i < numPeople; i++)
    {
        if( people[i].getName() == personName)
            return i;
    }
    return -1;
}

// Displays average degree of each connected component
void FriendNet :: displayAverageDegrees()
{
    int conComp = 0;
    int countDeg = 0;
    int countPeople = 0;
    bool* visited = new bool[numPeople];                              // Boolean array, true if the person is visited, otherwise false
    for(int i = 0; i < numPeople; i++)                                // Initially no person is visited)
        visited[i] = false;
    double* averages = new double[numPeople];                         // Array that holds the average of degrees of the each connected component
    for( int i = 0; i < numPeople; i++)
        averages[i] = -1;
    int index = 0;
    for( int i = 0; i < numPeople; i++)
    {
        if( !visited[i])
        {
            countDeg = 0;
            countPeople = 0;
            countDeg += people[i].getDegree();
            countPeople++;
            displayAvDegRec(i, countDeg, countPeople, visited);       // Recursive method is called
            conComp++;                                                // Increase the number of connected component
            averages[index] = double(countDeg) / double(countPeople); // Average is calculated
            index++;
        }
    }
    cout << "There are " << conComp << " connected components. The average degrees are:" << endl;
    for( int i = 0; i < index; i++)
        cout << "For component " << i << ": " << setprecision(3) << averages[i] << endl;
    delete [] visited;
    delete [] averages;
}

// Recursive method for displayAverageDegree method
void FriendNet :: displayAvDegRec( int personId, int &countDeg, int &countPeople, bool* &visited)
{
    if( !visited[personId])                                                       // If the person is not visited execute
    {
        visited[personId] = true;
        for( int i = 0; i < people[personId].getDegree(); i++)
        {
            int friendIndex = people[personId].getFriendId(i);
            if( !visited[friendIndex])
            {
                countPeople++;
                countDeg += people[friendIndex].getDegree();
                displayAvDegRec( friendIndex, countDeg, countPeople, visited);    // Function is recursively called
            }
        }
    }
}

// Method that displays the longest of the shortest paths for each connected component
void FriendNet :: displayDiameters()
{
    int* diameters = new int[numPeople];                // Holds the length of the longest path for each v-connected component
    for( int i = 0; i < numPeople; i++)
        diameters[i] = -1;
    int numComponent = 0;
    int* dist = new int[numPeople];                     // Holds the shortest path for each person
    for( int i = 0; i < numPeople; i++)
        dist[i] = -1;
    int start = 0;
    Queue* q = new Queue( numPeople);                   // Created a queue for breadth first traversal
    while(start != numPeople)
    {
        bool* compVisited = new bool[numPeople];        // People belong to connected component that we currently work on
        for( int i = 0; i < numPeople; i++)
            compVisited[i] = false;
        dist[start] = 0;
        compVisited[start] = true;
        q->enqueue(start);
        while (!q->isEmpty())
        {
            int w;
            q->dequeue(w);
            for (int i = 0; i < people[w].getDegree(); i++)   // Execute for each unvisited people u adjacent to w
            {
                int u = people[w].getFriendId(i);
                if(dist[u] == -1)                             // If it is -1, it is unvisited
                {
                    q->enqueue(u);
                    dist[u] = dist[w] + 1;
                    compVisited[u] = true;
                }
            }
        }
        int maxDistID = start;
        for(int i = maxDistID + 1; i < numPeople; i++)
        {
            if( compVisited[i] && dist[maxDistID] < dist[i])
                maxDistID = i;
        }
        for( int i = 0; i < numPeople; i++) {
            if( compVisited[i])
                dist[i] = -1;
        }

        dist[maxDistID] = 0;                                // We use bfs one more time for the person with longest distance to find the longest of the shortest path
        q->enqueue(maxDistID);
        while (!q->isEmpty())
        {
            int w;
            q->dequeue(w);
            for (int i = 0; i < people[w].getDegree(); i++)
            {
                int u = people[w].getFriendId(i);
                if(dist[u] == -1)
                {
                    q->enqueue(u);
                    dist[u] = dist[w] + 1;
                }
            }
        }

        for(int i = start + 1; i < numPeople; i++) {
            if(compVisited[i] && dist[start] < dist[i])
                start = i;                                   // Start holds index of the largest shortest path
        }
        diameters[numComponent] = dist[start];               // After second bfs the largest value will set as diameter for this connected component
        numComponent++;
        for(start = 0; start < numPeople; start++)
        {
            if(dist[start] == -1)
                break;
        }
        delete [] compVisited;                                // compVisited pointer array is deleted
    }
    cout << "There are " << numComponent << " connected components. The diameters are:" << endl;
    for(int i = 0; i < numComponent; i++)
        cout << "For component " << i << ": " << diameters[i] << endl;
    delete [] dist;                                            // dist pointer array is deleted
    delete [] diameters;                                       // diameters pointer array is deleted
    delete q;                                                  // q is deleted
 }
