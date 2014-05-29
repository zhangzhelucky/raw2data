
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
    Decode();

}


bool CModul::Decode()
{
    if( false == getHeader() )
    {
	// Get header error
	return false;
    }

    if( false == getData() )
    {
	// Get data error
	return false;
    }

    return true;
}


bool CModul::getHeader()
{
    tempData = mRawData->at( 0 );
    mRawData->erase( mRawData->begin() );

    mChlNum = (tempData & ChlNumMask ) >> ChlNumR; // Get Channel Num
    mGeo = (tempData & GeoMask ) >> GeoR;	   // Get Geo

    // On crate No.1
    if( 0x01 != ((tempData & CrateMask ) >> CrateR) )
    {
	return false;
    }

    return true;
}


bool CMv792::getData()
{
    short chl;
    for (int i = 0; i < mChlNum; i++) 
    {
	tempData = mRawData->at( 0 );
	mRawData->erase( mRawData->begin() );

	chl = ( tempData & ChlMask32 ) >> ChlR32 ;
	
	

    }





}


bool CModul::getData()
{

    // if( 0 != ( tempData & isUnderThrsMask )  )
    // {
    // 	return false;
    // }
    // else if( 0 != ( tempData & isOverflewMask )  )
    // {
    // 	return false;
    // }
    // else
    // {
	
    // }    


}

  
// unsigned short CModul::checkMark()
// {
//     return ( (tempData & DataMarkMask ) >> DataMarkR );

// }






