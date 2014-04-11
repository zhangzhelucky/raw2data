
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{
    ofstream fp;
    string str[100];
    char ch[3];

    for (int i = 0; i < 100; i++) 
    {
	sprintf( ch , "%02d" , i );
	str[i] = ch;
    }

    for (int i = 0; i < 100; i++) 
    {
	str[i] = "20140405." + str[i];

	fp.open( str[i].c_str() , ios::app );
	fp.close();
	cout << str[i] << endl;
    }

    return 0;
}
