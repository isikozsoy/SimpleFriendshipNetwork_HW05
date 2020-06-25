/*
* Title: Graphs
* Author: Isik Ozsoy
* ID: 21703160
* Section: 1
* Assignment: 3
* Description: cpp file of Queue
*/

#include "Queue.h"

// Constructor
Queue :: Queue(int size) {
    front = 0;
    back = size - 1;
    count = 0;
    items = new int[size];
    this->size = size;
}

// Destructor
Queue :: ~Queue() {
    if(items)
        delete [] items;
}

// Returns true if the queue is empty, otherwise false
bool Queue :: isEmpty() const {
    return (count == 0);
}

// Add new item to the queue, if the queue is full returns false otherwise true
bool Queue :: enqueue(int newItem) {
    if (count == size)                // Checks whether the queue is full
        return false;

    else{                             // If queue is not full; insert item
        back = (back+1) % size;
        items[back] = newItem;
        ++count;
        return true;
    }
}

// Removes the item from the queue and returns it
bool Queue::dequeue(int& queueFront) {
    if (isEmpty())
        return false;
    else {                            // If queue is not empty; retrieve and remove front
        queueFront = items[front];
        front = (front+1) % size;
        --count;
        return true;
   }
}
