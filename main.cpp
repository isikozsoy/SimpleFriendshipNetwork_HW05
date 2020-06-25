#include "Person.h"
#include "FriendNet.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
    FriendNet yes("deneme.txt");
    yes.displayAverageDegrees();
    yes.displayDiameters();

    return 0;
}
