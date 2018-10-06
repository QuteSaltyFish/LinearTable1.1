//
//  LongIntList.cpp
//  LinearTable1.1
//
//  Created by Mingke Wang on 2018/10/4.
//  Copyright © 2018 Mingke Wang. All rights reserved.
//

#include "LongIntList.hpp"
#include <iostream>
using namespace std;
//返回第i个节点的地址
LongIntList::node* LongIntList::move(int i) const
{
    node *p = head;
    while (i-->=0) p = p->next;
    return p;
}

//构造函数的实现
LongIntList::LongIntList()
{
    head = new node;
    currentLength = 0;
}

//清空所有的数据点
void LongIntList::clear()
{
    node *p = head->next, *q;
    head->next = NULL;
    while (p!=NULL)
    {
        q = p->next;
        delete p;
        p = q;
    }
    currentLength = 0;
}

void LongIntList::add(int i)
{
    node *p=move(currentLength-1);
    p->next = new node(i);
    ++currentLength;
    
}

//插入节点
void LongIntList::insert(int i, const int &x)
{
    node *p=move(i-1);
    p->next = new node(x,p->next);
    ++currentLength;
}

//删除某个节点
void LongIntList::remove(int i)
{
    node *p, *del;
    p = move(i-1);
    del = p->next;
    p->next = del->next;
    delete del;
    --currentLength;
}

//查找某一个元素
int LongIntList::search(const int &x) const
{
    node* p = head->next;
    int index=0;
    while (p!= NULL && p->data != x)
    {
        p=p->next;
        index ++;
    }
    if (p == NULL)   return -1;
    else return index;
}

//看某一个节点
int LongIntList::visit(int i)const
{
    node *p=move(i);
    return p->data;
}

//遍历输出所有元素的值
void LongIntList::traverse()const
{
    cout<<endl;
    node *p = head;
    if (p->data==1)
        cout<<'-';
    p = p->next;
    while (p != NULL)
    {
        cout<<p->data<<"  ";
        p = p->next;
    }
    cout<<endl;
}

//消除值在[x,y]之间的所有元素点
void LongIntList::erase(int x, int y)
{
    node *p=head->next;
    int index = 0;
    while (p!=NULL)
    {
        if (p->data>=x && p->data<=y)
            remove(index);
        else index++;
    }
}

//反转所有数据点
void LongIntList::reverse()
{
    int *storage = new int[currentLength];
    for (int i=0; i<currentLength; ++i)
        storage[i] = visit(i);
    for (int i=0; i<currentLength; ++i)
        move(i)->data = storage[currentLength-1-i];
}


//赋值符号重载寒暑
LongIntList& LongIntList::operator=(const LongIntList &obj)
{
    if (this==&obj) return *this;   //防止自己复制自己
    this->clear();
    this->head->data = obj.head->data;
    for (int i = 0; i<obj.currentLength; ++i)
        this->insert(i, obj.visit(i));
    return *this;
}

//拷贝复制函数
LongIntList::LongIntList(const LongIntList &obj)
{
    head = new node;
    currentLength = 0;
    head->data = obj.head->data;
    for (int i = 0; i<obj.currentLength; ++i)
        this->insert(i, obj.visit(i));
}

//两个相加
LongIntList operator+(const LongIntList &x, const LongIntList &y)
{
    int sum = 0,minLen, AorB=0, maxLen;     //AorB是A与B的位数比较。
    if (x.currentLength<y.currentLength)
    {
        minLen = x.currentLength;
        maxLen = y.currentLength;
        AorB=1;
    }
    else if(x.currentLength>y.currentLength)
    {
        minLen = y.currentLength;
        maxLen = x.currentLength;
        AorB = -1;
    }
    else
    {
        minLen = y.currentLength;
        maxLen = x.currentLength;
        AorB = 0;
    }
    
    int carry = 0;
    int i=0;
    LongIntList A(x), B(y), C;
    if (x.head->data == y.head->data)   //判断是否符号相同
    {
        C.head->data = x.head->data;    //赋符号
        for ( i=0; i<minLen; ++i)
        {
            sum = A.visit(i) + B.visit(i) + carry;
            C.insert(i,sum%10000);
            carry = sum/10000;
        }
        if (AorB==1)
        {
            while (carry==1)
            {
                sum = B.visit(i) + carry;
                C.insert(i,sum%10000);
                carry = sum/10000;
                i++;
            }
            for (; i<maxLen;++i)
            {
                C.insert(i, B.visit(i));
            }
        }
        else if (AorB==-1)
        {
            while (carry==1)
            {
                sum = A.visit(i) + carry;
                C.insert(i,sum%10000);
                carry = sum/10000;
                i++;
            }
            for (; i<maxLen;++i)
            {
                C.insert(i, A.visit(i));
            }
        }
        else
        {
            C.insert(i,1);
        }
        return C;
    }
    
    else
    {
        bool change = false;
        //判断两个数字的绝对值的大小
        //确保A一定比B大
        if (y.currentLength > x.currentLength)
            change = true;
        else if (y.currentLength == x.currentLength)
        {
            for (i=0; i<minLen; ++i)
            {
                if (y.visit(minLen-1-i)>x.visit(minLen-1-i))
                {
                    change = true;
                    break;
                }
        
            }
        }
        if (change)
        {
            A = y;
            B = x;
        }
        
        for ( i=0; i<minLen; ++i)
        {
            sum = A.visit(i) - B.visit(i) - carry;
            if (sum>=0) carry=0;
            else
            {
                carry=1;
                sum+=10000;
            }
            C.insert(i,sum);
            
        }
        if (A.currentLength!=B.currentLength)
        {
            while (carry==1)
            {
                sum=A.visit(i)-carry;
                if (sum>=0) carry=0;
                else
                {
                    carry=1;
                    sum+=10000;
                }
                C.insert(i, sum);
                
                i++;
            }
            for (; i<maxLen;++i)
            {
                C.insert(i, A.visit(i));
            }
        }
        
        
        
        for ( i=C.currentLength-1; i>=0; --i)  //除掉最前面的0
        {
            if (C.visit(i)==0)
                C.remove(i);
            else break;
        }
        
        if (change)
            C.head->data = !x.head->data;
        else
            C.head->data = x.head->data;
        return C;
    }
}
