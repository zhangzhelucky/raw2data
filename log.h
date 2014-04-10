#/***************************************************
# File Name:	log.h
# Abstract:
# Author:	zhangzhelucky
# Update History:
#
# 2014-04-10	Start this file
#
#
#****************************************************/


#ifndef _LOG_H_
#define _LOG_H_
#include <fstream>




class CLog
{
 public:
    CLog( string , bool );

    virtual ~CLog();
 private:
    string getTimeStr();
    bool isDisplay;

 private:
    ofstream fp;
    string logStr;

 public:
    static string fileStr;
    
};
  
string CLog::fileStr;
  
#endif /* _LOG_H_ */





