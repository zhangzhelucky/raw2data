
#/***************************************************
# File Name:	moduls.h
# Abstract:
# Author:	zhangzhelucky
# Update History:
#
# 2014-04-11	
#
#
#****************************************************/

#ifndef _EVENT_H_
#define _EVENT_H_

#include <vector>
using namespace std;


#define _EVENT_SEPARATOR 0xffffffff


struct sEventDataRegister
{
    short v830ac_3[32];
    short v785n_4[16];
    short v775n_5[16];
    /*  */
    short v775n_7[16];
    short v775n_8[16];
    /*  */
    short v785_10[32];
    /*  */
    short v792_12[32];
    short v792_13[32];
    /*  */
    short v792_15[32];
    short v792_16[32];

};

typedef	sEventDataRegister sEData


class CEvent
{
 public:
    CEvent( fstream* );
    virtual ~CEvent();

 public:
    static unsigned int EC;	// Enent Counter (EC)
    sEData data;	// for event data output

    vector<int> RawData;
    vector<int>::iterator iter;
    
 private:
    fstream* pDataFile;

 private:
    fstream* loadEvent();
    bool getEventHeader();

 public:
    bool Decode();


};

  
  
#endif /* _EVENT_H_ */


