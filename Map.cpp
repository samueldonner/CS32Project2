
#include <iostream>
#include "Map.h"

using namespace std;

void Map::dump() const
{
    Node *p = head;
    while(p != nullptr)
    {
        cerr << "Name: " << p->key << "|   Value: " << p->value << endl;
        p = p->next;
    }
} //print Map






bool combine(const Map& m1, const Map& m2, Map& result)
{
    KeyType keyM1;
    ValueType valueM1;
    KeyType keyM2;
    ValueType valueM2;
    bool passOrFail = true;
    Map resultTemp; // create temp result variable
    
    if( m2.size() == 0 )
    {
        result = m1;
        return true;
    }
    else if( m1.size() == 0 )
    {
        result = m2;
        return true;
    }
    
    for(int i = 0; i < m1.size(); i++)
    {
        for( int j = 0; j < m2.size(); j++ )
        {
            m1.get(i, keyM1, valueM1);
            m2.get(j, keyM2, valueM2);
            resultTemp.insert(keyM1, valueM1);
            resultTemp.insert(keyM2, valueM2);
        } //insert all keys from m1 and m2 (duplicates will not be inserted)
    }
    
    for(int i = 0; i < m1.size(); i++)
    {
        for( int j = 0; j < m2.size(); j++ )
        {
            m1.get(i, keyM1, valueM1);
            m2.get(j, keyM2, valueM2);
            if (keyM1==keyM2 && valueM1!=valueM2)
            {
                resultTemp.erase(keyM1);
                passOrFail = false;
            } // if m1 and m2 keys equal each other and the values dont equal each other
              // remove the that key from the resultTemp Map and set passOrFail = to false
        }
    }
    
    result = resultTemp;
    
    return passOrFail;
}


void subtract(const Map& m1, const Map& m2, Map& result)
{
    KeyType keyM1;
    ValueType valueM1;
    KeyType keyM2;
    ValueType valueM2;
    Map resultTemp;
    for( int j = 0; j < m1.size(); j++ )
    {
        m1.get(j, keyM1, valueM1);
        resultTemp.insert(keyM1, valueM1);
    } // insert all m1 keys into resultTemp
    
    for(int j = 0; j < m2.size(); j++)
    {
        for( int i = 0; i < resultTemp.size(); i++ )
        {
            resultTemp.get(i, keyM1, valueM1);
            m2.get(j, keyM2, valueM2);
            if (keyM1==keyM2)
            {
                resultTemp.erase(keyM1);
            } // if keym1 and keym2 are equal erase keym1 from result map
        } // go through m2 and result temp and compaure each function
    }
    
    result = resultTemp;
}


Map::Map()
{
    head = nullptr;
} // construct map and set head = to nullptr


Map::Map(const Map& other)
{
    head = nullptr;
    Node *pOther = other.head;
    while( pOther!=nullptr )
    {
        if(pOther->next==nullptr)
            break;
        pOther = pOther->next;
    } // go to end of the other Map
    
    while( pOther!=nullptr)
    {
        insert(pOther->key, pOther->value);
        pOther = pOther->previous;
    } // go backwards through other Map and insert
      // keys in right order
}

Map& Map::operator=(const Map& otherSide)
{
    Node *pOtherSide = otherSide.head;
    Node *p=head;
    while( p!=nullptr )
    {
        erase(p->key);
        p = p->next;
    } // erase this Map
    while( pOtherSide!=nullptr )
    {
        if(pOtherSide->next==nullptr)
             break;
        pOtherSide = pOtherSide->next;
    } // go to end of otherSide map

    while( pOtherSide!=nullptr)
    {
        insert(pOtherSide->key, pOtherSide->value);
        pOtherSide = pOtherSide->previous;
    } // go backwards through other Map and insert
    // keys in right order
    return (*this);
}

Map::~Map()
{
    if(head == nullptr)
    {
        return;
    } // check if Map is empty
    Node *p = head;
    while(p!=nullptr)
    {
        head = p->next;
        Node* killer = p;
        p = p->next;
        delete killer;
    } //delete all Nodes in Map
}

bool Map::empty() const
{
    if( head == nullptr)
        return true;
    else
        return false;
} // check if Map is empty

int Map::size() const
{
    Node *p = head;
    int sizeCounter = 0;
    while( p!=nullptr )
    {
        sizeCounter++;
        p = p->next;
    } // increase size Counter while cycling through Map
    
    return sizeCounter;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
    if( contains(key) )
        return false; // dont insert if key is contained
    Node *p = new Node;
    p->value = value;
    p->key = key;
    p->next = head;
    p->previous = nullptr; //linke up items
    if(head != nullptr)
    {
        head->previous = p;
    } // make sure Map is not empty
    head = p;
    
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
    Node *p = head;
    while( p!=nullptr )
    {
        if( p->key == key )
        {
            p->value = value;
            return true;
        } // if Map key is key then Map value equals
        p = p->next;
    } // go through Map
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    if(contains(key))
    {
        update(key, value);
    } // if map contains update it
    else
    {
        insert(key, value);
    } // otherwise insert the key
    return true;
}

bool Map::erase(const KeyType& key)
{
    Node *p = head;
    while( p!=nullptr )
    {
        if(p->key == key)
        { // if Map key equals key
            Node *killer = p;
            Node *temp = killer->next;
            if( p->previous == nullptr )
            {
                if(temp!=nullptr)
                {
                    temp->previous = nullptr;
                } // if only node in a list
                head = temp;
                delete killer;
                return true;
            } // if first node in a list
            
            p = killer->previous;
            p->next = temp;
            if(temp!=nullptr)
            {
                temp->previous = p;
            } // if temp is empty
            delete killer;
            return true;
        }
        p = p->next;
    } // go through Map
    
    return false;
}

bool Map::contains(const KeyType& key) const
{
    Node *p = head;
    while( p!=nullptr )
    { // go thorugh Map
        if( p->key == key )
        { // if key is in Map return true
            return true;
        }
        p = p->next;
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    Node *p = head;
    while( p!=nullptr )
    { // go through map
        if( p->key == key )
        { // Map key == key
            value = p->value; // set value = to Map value
            return true; //return true if key is in Map
        }
        p = p->next;
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    Node *p = head;
    int getIndex = 0;
    while( p!=nullptr )
    { // go through Map
        if( getIndex == i )
        { // if the index equals I then set key and value to the Map's
            key = p->key;
            value =p->value;
            return true;
        }
        p = p->next;
        getIndex++;
    }
    return false;
}

void Map::swap(Map& other)
{
    Map tempMap; //create tempoarty map
    tempMap = other;
    other = *this;
    *this = tempMap;
} //swamp maps

