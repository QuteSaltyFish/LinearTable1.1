//
//  LongIntList.hpp
//  LinearTable1.1
//
//  Created by Mingke Wang on 2018/10/4.
//  Copyright © 2018 Mingke Wang. All rights reserved.
//

#ifndef LongIntList_hpp
#define LongIntList_hpp

#include <iostream>
using namespace std;
class LongIntList
{
    friend ostream& operator<<(ostream& out, const LongIntList& obj);
    friend LongIntList operator+(const LongIntList &x, const LongIntList &y);
private:
    struct node
    {
        int data;
        node *next;
        
        node(const int referencedata, node *n=NULL)
        {
            data = referencedata;
            next = n;
        }
        node():next(NULL),data(0){}
        ~node(){};
    };
    
    node *head; //头指针
    
    
    node *move(int i) const;//返回第i个节点的地址
    
public:
    int currentLength;  //表长
    
    LongIntList& operator=(const LongIntList &obj);
    LongIntList();
    LongIntList(const LongIntList& obj);
    ~LongIntList()
    {
        clear();
        delete head;
    }
    
    void clear();
    int length() const {return currentLength;}
    void insert(int i, const int &x);
    void remove(int i);
    int search(const int &x) const;
    int visit(int i) const;
    void traverse() const;
    void erase(int x, int y);
    void reverse();
    void isMinus(){head->data=1;}
    void add(int i);
};


#endif /* LongIntList_hpp */
