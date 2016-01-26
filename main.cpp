//
//  main.cpp
//  Project2
//
//  Created by Samuel Donner on 1/24/16.
//  Copyright © 2016 Samuel Donner. All rights reserved.
//
#include <iostream>
#include <cassert>
#include "Map.h"

using namespace std;

int main()
{
    KeyType k;
    ValueType v;
    
    Map hi; //initiate new map without parameters
    assert(hi.size()==0); // check that hi is empty
    assert(hi.empty()); // check hi has no nodes and is empty
    assert(hi.erase("Jake")==false); // nothing to erase
    assert(hi.erase("Jake")==false); // Map contains no values
    
    assert(hi.insert("Jake", 199));
    assert(!hi.empty()); // check if hi is empty
    assert(hi.size()==1); //check if size has increased
    assert(hi.contains("Jake")); // if the nodes that are inserted are contained
    assert(!hi.insert("Jake",1)); //duplicate nodes can not beinserted
    assert(hi.size()==1); //check if size has not changed
    
    hi.get("Jake", v);
    assert(v == 199); // chekc that node Jake is holding value 199
    
    assert(!hi.erase("Nobody")); // check that a node that does not
                                // exist cant be deleted
    assert(hi.update("Jake", 10)); // node with key jake is updated
    hi.get("Jake", v);
    assert(v == 10); // check that node Jake is holding value 10
    assert(hi.insert("John", 255)); // check that a second node can be added
    hi.get("John",v);
    assert(v==255); // check if value is replaced
    
    hi.insertOrUpdate("Jerry", 23123); // inserts into function
    hi.insertOrUpdate("John", 4894); // updates John
    
    assert(hi.size()==3); // checks for right number of nodes
    hi.dump(); // prints out all keys and values
    // (Jake, 10) (John, 4894) (Jerry, 23123)
    
    assert(hi.contains("Jerry") && hi.contains("John") && hi.contains("Jake"));
    // poper nodes are contained
    
    
    Map hiCopy(hi); //test copy constructor
    
    assert(hiCopy.size()==3); //check that hiCopy has the same size as hi
    hiCopy.dump(); // should print out same values as hi
    
    Map hiCopy2 = hi; //check that hicopy2 is an copy of hi
    assert(hiCopy.size()==3);
    hiCopy2.dump();
    
    while(!hiCopy2.empty())
    {
        hiCopy2.get(0,k,v);
        hiCopy2.erase(k);
        cerr << k << " : " << v << " removed" << endl;
    }
    
    Map blank;
    hiCopy = blank;
    assert(hiCopy.empty());
    
    Map anotherBlank(blank);
    assert(anotherBlank.empty());
    
    Map oneNode;
    oneNode.insert("blah",1);
    Map copyOneNode(oneNode); // test the copy constructor with only one node
    assert(copyOneNode.size()==1); //check that size is correct
    assert(copyOneNode.contains("blah"));
    
    Map goodbye;
    hi.swap(goodbye);
    assert(hi.empty());
    assert(goodbye.size()==3);
    
    goodbye.swap(hi);
    assert(goodbye.empty());
    assert(hi.size()==3);
    
    assert(hi.erase("John")); //check that middle node is deleted and updated
    assert(hi.size()==2);
    
    assert(hi.erase("Jake")); //check that tail node is deleted and updated
    assert(hi.size()==1);
    
    assert(hi.erase("Jerry")); //check that head node is deleted and updated
    assert(hi.empty());
    
    assert(hi.insert("next head", 5));
    assert(hi.insert("next tail", 5));
    assert(hi.erase("next head")); // check that the head node can be removed when its not the last node
    assert(hi.size()==1);
    
    
    
    
    
    
    
    //=====================
    
    
    
    Map firstMap;
    firstMap.insert("one",1);
    firstMap.insert("two",2);
    firstMap.insert("three",3);
    firstMap.insert("four", 4); // should not be included in combine because values differ
    
    Map secondMap;
    
    secondMap.insert("three",3);
    secondMap.insert("four",10);
    secondMap.insert("five",5);
    
    Map answer;
    assert(combine(firstMap, secondMap, answer)==false);
    
    assert(answer.size()==4); //check that size is the same

    assert(combine(firstMap, secondMap, secondMap)==false);
    assert(answer.size()==4); // check if combine works when aliasing
    
    Map simpleOne;
    simpleOne.insert("blah",1);
    
    Map simpleTwo;
    simpleTwo.insert("bleh", 2);
    Map simpleThree;
    
    assert(combine(simpleOne, simpleTwo, simpleThree)); //check that combine returns true
    assert(simpleThree.size()==2);
    assert(simpleThree.contains("blah") && simpleThree.contains("bleh")); // check for correct pairs
    
    Map random;
    random.insert("eek" ,0);
    random.insert("aah",1);
    assert(random.size()==2);
    Map blankMap;
    Map blankResult;
    
    combine(random, blankMap, blankResult); //test combine with empty Map as m2
    assert(blankResult.size()==2 && blankResult.contains("eek") && blankResult.contains("aah"));
    
    combine(blankMap,random, blankResult); //test combine with empty map as m1
    assert(blankResult.size()==2 && blankResult.contains("eek") && blankResult.contains("aah"));
    
    Map firstMapCopy;
    firstMapCopy.insert("one",1);
    firstMapCopy.insert("two",2);
    firstMapCopy.insert("three",3);
    firstMapCopy.insert("four",4); // should not be included in subtract because first and second maps differ
    
    Map secondMapCopy;
    secondMapCopy.insert("three",3);
    secondMapCopy.insert("four",10);
    secondMapCopy.insert("five",5);
    
    Map anotherResult;
    
    subtract(firstMapCopy, secondMapCopy, anotherResult);
    assert(anotherResult.size()==2);
    assert(anotherResult.contains("one") && anotherResult.contains("two"));
    
    subtract(firstMapCopy, secondMapCopy, firstMapCopy); //check aliasing
    assert(firstMapCopy.size()==2);
    assert(firstMapCopy.contains("one") && firstMapCopy.contains("two")); // check for pairs
    
    Map random2;
    assert(random2.insert("eek", 0) && random2.insert("aah",1));
    assert(random2.size()==2);
    Map blankMap2;
    Map blankResult2;
    
    subtract(random2, blankMap2, blankResult2); //test subtract with empty map as m2
    assert(blankResult2.size()==2 && blankResult2.contains("eek") && blankResult2.contains("aah"));
    
    subtract(blankMap2, random2, blankResult2); //test subtract with empty map as m1
    assert(blankResult2.empty());
    
    
    
    cerr << "passed all tests"<< endl;
}
