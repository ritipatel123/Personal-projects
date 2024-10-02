//
//  Set.h
//  project 2
//
//  Created by Riti Patel on 4/20/24.
//

#ifndef Set_h
#define Set_h
#include <string>
#include <iostream>


using ItemType = std::string;

class Set
{
public:
    Set();
    ~Set();
    Set(const Set& other);
    Set& operator=(const Set& rhs);
    bool empty() const;
    int  size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
 

private:
    struct Node {
        ItemType value;
        Node*    next;
        Node*    prev;
    };

    
    Node* head;
    Node* tail;
    int   m_size;
};

void unite(const Set& s1, const Set& s2, Set& result);
void inOnlyOne(const Set& s1, const Set& s2, Set& result);

#endif /* Set_h */
