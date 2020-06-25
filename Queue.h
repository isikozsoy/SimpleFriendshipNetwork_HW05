/*
* Title: Graphs
* Author: Isik Ozsoy
* ID: 21703160
* Section: 1
* Assignment: 5
* Description: header file of Queue
*/

class Queue{
public:
    Queue(int);  // default constructor
    ~Queue();  // default constructor
   // Queue operations:
   bool isEmpty() const;
   bool enqueue(int newItem);
   bool dequeue(int& queueFront);

private:
   int* items;
   int  front;
   int  back;
   int  count;
   int  size;
};
