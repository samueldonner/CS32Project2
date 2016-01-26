
#include <iostream>
#include "Map.h"

using namespace std;

bool combine(const Map& m1, const Map& m2, Map& result)
{
    KeyType keyM1;
    ValueType valueM1;
    KeyType keyM2;
    ValueType valueM2;
    bool passOrFail = true;
    Map resultTemp;
    for(int i = 0; i < m1.size(); i++)
    {
        for( int j = 0; j < m2.size(); j++ )
        {
            m1.get(i, keyM1, valueM1);
            m2.get(j, keyM2, valueM2);
            resultTemp.insert(keyM1, valueM1);
            resultTemp.insert(keyM2, valueM2);
        }
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
            }
        }
    }
    
    result = resultTemp;
    
    return passOrFail;
}

void subtract(const Map& m1, const Map& m2, Map& result)
{
    
}


Map::Map()
{
    head = nullptr;
}


Map::Map(const Map& other)
{
    Node *pOther = other.head;
    while( pOther!=nullptr)
    {
        insert(pOther->key, pOther->value);
        pOther = pOther->next;
    }
}

Map& Map::operator=(const Map& otherSide)
{
    Node *p = head;
    Node *pOtherSide = otherSide.head;
    while( p!=nullptr )
    {
        erase(p->key);
        p = p->next;
    }
    while( pOtherSide!=nullptr)
    {
        insert(pOtherSide->key, pOtherSide->value);
        pOtherSide = pOtherSide->next;
    }
    return (*this);
}

Map::~Map()
{
    if(head == nullptr)
    {
        return;
    }
    Node *p = head;
    while(p!=nullptr)
    {
        head = p->next;
        Node* killer = p;
        p = p->next;
        delete killer;
    }
}

bool Map::empty() const
{
    if( head == nullptr)
        return true;
    else
        return false;
}

int Map::size() const
{
    Node *p = head;
    int sizeCounter = 0;
    while( p!=nullptr )
    {
        sizeCounter++;
        p = p->next;
    }
    
    return sizeCounter;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
    if( contains(key) )
        return false;
    Node *p = new Node;
    p->value = value;
    p->key = key;
    p->next = head;
    p->previous = nullptr;
    if(head != nullptr)
    {
        head->previous = p;
    }
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
        }
        p = p->next;
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    if(contains(key))
    {
        update(key, value);
    }
    else
    {
        insert(key, value);
    }
    return true;
}

bool Map::erase(const KeyType& key)
{
    Node *p = head;
    while( p!=nullptr )
    {
        if(p->key == key)
        {
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
            }
            delete killer;
            return true;
        }
        p = p->next;
    }
    
    return false;
}

bool Map::contains(const KeyType& key) const
{
    Node *p = head;
    while( p!=nullptr )
    {
        if( p->key == key )
        {
            
            return true;
        }
        p = p->next;
    }
    return false;
}

void Map::dump()
{
    Node *p = head;
    while(p != nullptr)
    {
        cout << "Name: " << p->key << "|   Value: " << p->value << endl;
        p = p->next;
    }
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    Node *p = head;
    while( p!=nullptr )
    {
        if( p->key == key )
        {
            value = p->value;
            return true;
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
    {
        if( getIndex == i )
        {
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
    Map tempMap;
    tempMap = other;
    other = *this;
    *this = tempMap;
}

