#/***************************************************
# File Name:	moduls.cpp
# Abstract:
# Author:	zhangzhelucky
# Update History:
#
# 2014-04-11	begining
#
#
#****************************************************/

#include "moduls.h"
#include <iostream>
using namespace std;

CModul::CModul( vector<int>* data)
{
    mRawData = data;
}

virtual bool CModul::Decode()
{
    tempData = mRawData->at( 0 );
    
}

virtual unsigned short CModul::checkMark()
{
    return ( (tempData & DataMarkMask ) >> DataMarkR );
}


virtual bool CModul::getHeader()
{
    mChlNum = (tempData & ChlNumMask ) >> ChlNumR;

    if( 1 != ((tempData & CrateMask ) >> CrateR) )
    {
	return false;
    }

    return true;
}


virtual bool CModul::getData()
{
    if( 0 != ( temp & isUnderThrsMask )  )
    {
	return false;
    }
    else if( 0 != ( temp & isOverflewMask )  )
    {
	return false;
    }
    else
    {
	
    }    
    



}








  

