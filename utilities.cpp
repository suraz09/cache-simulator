/*************************************************************************
/
/   filename: utitlies.cpp
/
/   description: Implements the utilities method
/
/   authors: Acharya, Suraj
/
/   class:  CSE 331
/   instructor: Zheng
/   assignment: Lab Project #1
/
/   assigned: Oct 17, 2016
/   due:    Oct 31, 2016
/
/************************************************************************/

#include "header.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>


using namespace std;



int bin2Dec(string str){
    
    int n = 0;
    int size = str.size() -1 ;
    int count = 0;
    for(int i = 0; i <= size; i++) {
    if ( str[i] == '1' ) 
        n = n + pow(2, size - count );
        count++; 
    }
    return n;
}

int hextoDec(string str){
	unsigned int result;
    int i;
    int size =  4 * (str.size() -2);
    i = 0;
    result = 0;
    
    if(str[i] == '0' && str[i+1] == 'x')
    {
        i = i + 2;
    }

    while(str[i] != '\0')
    {
        result = result * 16;
        if(str[i] >= '0' && str[i] <= '9')
        {
            result = result + (str[i] - '0');
        }
        else if(tolower(str[i]) >= 'a' && tolower(str[i]) <= 'f')
        {
            result = result + (tolower(str[i]) - 'a') + 10;
        }
        i++;
    }
    return result;
}



string hextoBinary(string str){
    str = str.substr(2,str.size() - 3);
    int size =  4* (str.size());
    int num = hextoDec(str);
    
    string bstring;    
    
    for(int i = size -1; i >= 0; i-- )
    {
        bstring  += (num == ((1 << i) | num)) ? '1' : '0';
    }

    return bstring;
   
}
