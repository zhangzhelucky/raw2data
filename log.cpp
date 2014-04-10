#/***************************************************
# File Name:	log.cpp
# Abstract:
# Author:	zhangzhelucky
# Update History:
#
# 2014-04-10	Start this file
#
#
#****************************************************/

#include <iostream>
#include <fstream>
#include <time.h>
#include <assert.h>

using namespace std;

#include "log.h"


CLog::CLog( string str , bool isdis = true )
{
    logStr = str;
    fp.open( fileStr.c_str() , ios::app );
    assert( fp );

    isDisplay = isdis;
}


string CLog::getTimeStr()
{
    time_t lt = time(NULL);
    tm* current = localtime( &lt );
    char str[100];
    strftime( str , 100 , "%F %X%t", current);

    return std::string(str);
}

CLog::~CLog()
{
    string timeStr = getTimeStr();

    fp << timeStr ;
    fp << logStr <<endl;
    fp.close();

    if( isDisplay)
    {
	cout << timeStr << logStr << endl;
    }
}




