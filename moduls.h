
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
  
#ifndef _MODULS_H_
#define _MODULS_H_
  

#include <vector>

  using namespace std;

#define	DataMarkMask		0x07000000
#define DataMarkR		24
#define DataMarKData		0x0
#define DataMarkHeader		0x2
#define DataMarkEnd		0x4
#define DataMarkNotValid	0x6

#define ChlNumMask		0x00003f00
#define ChlNumR			8

#define CrateMask		0x00ff0000
#define CrateR			16

#define GeoMask			0xf8000000
#define GeoR			27

#define ChlMask16		0x001e0000
#define ChlR16			17

#define ChlMask32		0x001f0000
#define ChlR32			16

#define DataMask		0x00000fff

#define isUnderThrsMask		0x00001000
#define isOverflewMask		0x00002000
#define isDataValidMask		0x00004000		


class CModul
{
 public:
    CModul( int* , vector<int>::iterator* );
    virtual ~CModul();

 public:
    //    vector<int>* mRawData;
    //    CEvent* event;

    int tempData;
    unsigned short mChlNum;
    unsigned short mGeo;

    (vector<int>::iterator)* pRawData;
    int* pData;

    //    unsigned short mCrate;
    //    const unsigned short mMaxChlNum;

 private:
    virtual bool getData();

    virtual bool Decode();
    virtual bool getHeader();

    //    virtual bool checkGeo();
    //    virtual bool checkCrate();
    //    virtual unsigned short checkMark(); 
    //    virtual unsigned short getChl();
    //    virtual bool getEnd();


};


class CMv830ac : public CModul
{
 public:
    CMv830ac( int* , vector<int>::iterator* );
    virtual ~CMv830ac();

    virtual bool getData();

};


class CMv792 : public CModul
{
 public:
    CMv792( int* , vector<int>::iterator* );
    virtual ~CMv792();

    virtual bool getData();

};


class CMv785 : public CModul
{
 public:
    CMv785( int* , vector<int>::iterator* );
    virtual ~CMv785();

    virtual bool getData();

};


class CMv785N : public CModul
{
 public:
    CMv785N( int* , vector<int>::iterator* );
    virtual ~CMv785N();

    virtual bool getData();

};


class CMv775N : public CModul
{
 public:
    CMv775N( int* , vector<int>::iterator* );
    virtual ~CMv775N();

    virtual bool getData();

};
  
  
#endif /* _MODULS_H_ */


