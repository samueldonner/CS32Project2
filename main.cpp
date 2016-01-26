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
    Map map1;
    Map map2;
    
    map1.insert("Fred", 123);
    map1.insert("Ethel", 456);
    map1.insert("Lucy", 789);
    
    map2.insert("Lucy", 654);
    map2.insert("Ricky", 321);
    cout<<endl;
    map1.dump();
    cout<<endl;
    map2.dump();
    cout<<endl;
    cout<<combine(map1, map2, map2);
    map2.dump();
    cout<<endl;
    
    //combine(map1, map2, map3);
    /*Map map;
    Map map2;
    
    
    if(map.empty())
        cout << "Map is empty" << endl;
    else
        cout << "Map is filled" << endl;
    
    map.insert("Steve", 123);
    map.insert("Joe", 456);
    map.insert("Sam", 1246);
    
    map2.insert("Jerm", 12163);
    map2.insert("Sal", 454536);
    map2.insert("Rick", 56423);
    
    map.dump();
    cout << endl;
    map2.dump();
    cout << endl;
    map.swap(map2);
    map.dump();
    cout << endl;
    map2.dump();
    cout << endl;
    
    Map map3(map2);
    cout << "map 3: " << endl;
    map3.dump();
     */
    
    /*cout << "Map has " << map.size() << " elements." << endl;
    
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
        cout << "Map does not contain element." << endl;*/
    
    
}
