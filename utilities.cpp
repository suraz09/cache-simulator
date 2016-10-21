#include "header.h"
#include <string>
#include <iostream>

using namespace std;

void printAddress(string str){
	
    cout << str+"\t|";
    // cout << "-------------------------------------------------------------|"<<endl;
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
   

	string bstring = "";
    int num = result;
    
    /* Calculate the Binary String */
    
    
    bstring[size] = '\0';
    
    for( i = size -1; i >= 0; i-- )
    {
        bstring  += (num == ((1 << i) | num)) ? '1' : '0';
    }
    
    
    return bstring;
   
}
