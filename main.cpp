//
//  main.cpp
//  Project2
//
//  Created by Samuel Donner on 1/24/16.
//  Copyright © 2016 Samuel Donner. All rights reserved.
//
#include <iostream>
#include "Map.h"
using namespace std;

int main()
{
    Map map;
    
    if(map.empty())
        cout << "Map is empty" << endl;
    else
        cout << "Map is filled" << endl;
    
    map.insert("Steve", 123);
    map.insert("Joe", 456);
    map.insert("Sam", 456);
    
    map.dump();
    
    
    cout << "Map has " << map.size() << " elements." << endl;
    
    //map.erase("Sam");
    //map.erase("Joe");
    map.erase("Steve");
    
    if(map.empty())
        cout << "Map is empty" << endl;
    else
        cout << "Map is filled" << endl;
    
    map.dump();
    cout << "Map has " << map.size() << " elements." << endl;
    
    
    
    if(map.contains("George"))
        cout << "Map contains element." << endl;
    else
        cout << "Map does not contain element." << endl;
    
    
}
