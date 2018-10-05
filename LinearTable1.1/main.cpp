//
//  main.cpp
//  LinearTable1.1
//
//  Created by Mingke Wang on 2018/10/4.
//  Copyright © 2018 Mingke Wang. All rights reserved.
//

#include <iostream>
#include "LongIntList.hpp"
#include <string>
#include <cstring>
#include <cmath>

int main(int argc, const char * argv[]) {
    // insert code here...
    string data;
    LongIntList AList, BList, CList;
    int isAminus=0, isBminus=0;
    int A=0,B=0;
    
    cout<<"PLS input data:";
    cin>>data;
    int index=(int)data.find_first_of(';');
    if (data[0] == '-')
    {
        isAminus = true;
        AList.isMinus();
    }
    if (data[index+1] == '-')
    {
        isBminus = true;
        BList.isMinus();
    }
    for (int i = 0; i < index-isAminus; ++i)
    {
        
        
        if (i%4==0 && i!=0)
        {
            AList.add(A);
            A=0;
        }
        A+= (data[index-1-i]-'0') * pow(10, i%4);
    }
    if (A!=0)
    {
        AList.add(A);
        A=0;
    }
    
    for (int i = 0; i < data.length()-1-index-isBminus-1; ++i)
    {
        if (i%4==0 && i!=0)
        {
            BList.add(B);
            B=0;
        }
        B+= (data[data.length()-1-1-i]-'0') * pow(10, i%4);
    }
    if (B!=0)
    {
        BList.add(B);
        B=0;
    }
    CList = AList + BList;
    AList.traverse();
    BList.traverse();
    CList.traverse();
    return 0;
}
