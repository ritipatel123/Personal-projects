//
//  Set.cpp
//  project 2
//
//  Created by Riti Patel on 4/20/24.
//
#include <iostream>
#include <string>
#include "Set.h"



Set::Set() {
    head = tail = nullptr;
    m_size = 0;
}


Set::~Set() {
    if (m_size == 0)
        return;
    if (m_size == 1) {
        delete head;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
         delete temp->prev;
    }
    delete tail;
}


Set::Set(const Set& other) {
    int i = 0;
    Node* temphead = head;
    for (Node* temp = other.head; temp != nullptr; temp = temp->next)
    {

        if (i == 0)
        {
            head = new Node;
            head->value = other.head->value;
            head->prev = nullptr;
            head->next = nullptr;
            i++;
            temphead = head;
            if (other.m_size == 1)
                tail = temphead;
            m_size++;
        }
        else
        {
            Node* newNode = new Node;
            newNode->value = temp->value;
            temphead->next = newNode;
            newNode->prev = temphead;
            temphead = temphead->next;
            i++;
            m_size++;
        }
    }
    if (i == other.m_size)
    {
        temphead->next = nullptr;
        tail = temphead;
    }
    if (other.size() == 0)
    {
        head = tail = nullptr;
        m_size = 0;
    }
}

Set& Set::operator=(const Set& rhs)
{
    if(this != &rhs)
    {
        Set temp(rhs);
        swap(temp);
    }
    
    return *this;
}

bool Set::empty() const {
    return m_size == 0;
}

int Set::size() const {
    return m_size;
}

bool Set::insert(const ItemType& value) {
    if (contains(value)) {
        return false;
    }

    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;

    if (m_size == 0) {
        head = tail = newNode;
        newNode->prev = nullptr;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    m_size++;
    return true;
}

bool Set::erase(const ItemType& value) {
    for (Node* p = head; p != nullptr; p = p->next) {
        if (p->value == value) {
            if (p == head) {
                head = p->next;
                if (head) {
                    head->prev = nullptr;
                } else {
                    tail = nullptr;
                }
            } else {
                p->prev->next = p->next;
            }
            if (p == tail) {
                tail = p->prev;
                if (tail) {
                    tail->next = nullptr;
                } else {
                    head = nullptr;
                }
            } else {
                p->next->prev = p->prev;
            }

            delete p;
            m_size--;
            return true;
        }
    }
    return false;
}


bool Set::contains(const ItemType& value) const {
    for (Node* p = head; p != nullptr; p = p->next)
    {
        if (p->value == value)
            return true;
    }
    return false;
}

bool Set::get(int pos, ItemType& value) const {
    if (head == nullptr || pos < 0 || pos >= m_size) {
        return false;
    }

    Node* out = head;
    while (out != nullptr) {
        int lessThanCount = 0;
        Node* in = head;
        while (in != nullptr) {
            if (out != in && out->value < in->value) {
                lessThanCount++;
            }
            in = in->next;
        }

        if (lessThanCount == pos) {
            value = out->value;
            return true;
        }

        out = out->next;
    }
    return false;
}

void Set::swap(Set& other) {
    int temp = other.m_size;
    other.m_size = m_size;
    m_size = temp;
    
    Node *tempHead = head;
    head = other.head;
    other.head = tempHead;
    
    Node* t_tail = tail;
    tail = other.tail;
    other.tail = t_tail;
}



void unite(const Set& s1, const Set& s2, Set& result)
{
    ItemType temp;
    
    if (&result == &s1)
    {
        for (int i = 0; i < s2.size(); i++)
        {
            s2.get(i, temp);
            result.insert(temp);
        }

    }
    else if(&result == &s2)
    {
        for (int i = 0; i < s1.size(); i++)
        {
            s1.get(i, temp);
            result.insert(temp);
        }
        
    }
    
    else
    {
    for (int i = 0; result.size() != 0;)
    {
        result.get(i, temp);
        result.erase(temp);
    }
    
    for (int i = 0; i < s1.size(); i++)
    {
        s1.get(i, temp);
        result.insert(temp);
    }
    
    for (int i = 0; i < s2.size(); i++)
    {
        s2.get(i, temp);
        result.insert(temp);
    }
    }
}
void inOnlyOne(const Set& s1, const Set& s2, Set& result){
    Set s = result;
    for (int i = 0; i < s1.size(); i++) {
        ItemType item;
        s1.get(i,item);
        if(!s2.contains(item)) {
            s.insert(item);
        }
    }
    for (int i = 0; i < s2.size(); i++) {
        ItemType item;
        s2.get(i,item);
        if(!s1.contains(item)) {
            s.insert(item);
        }
    }
    result = s;
    
    
}
