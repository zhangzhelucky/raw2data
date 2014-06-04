
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

CModul::CModul( int* pdata , vector<int>::iterator* piter )
{
    pData = pdata;
    pRawData = piter;

    Decode();
}


// CModul::~CModul()
// {

// }


CMv830ac::CMv830ac( int* pdata , vector<int>::iterator* piter )
    : CModul( pdata , piter )
{
}


CMv792::CMv792( int* pdata , vector<int>::iterator* piter )
    : CModul( pdata , piter )
{
}


CMv785::CMv785( int* pdata , vector<int>::iterator* piter )
    : CModul( pdata , piter )
{
}


CMv785N::CMv785N( int* pdata , vector<int>::iterator* piter )
    : CModul( pdata , piter )
{
}


CMv775N::CMv775N( int* pdata , vector<int>::iterator* piter )
    : CModul( pdata , piter )
{
}


bool CModul::getHeader()
{
    // tempData = mRawData->at( 0 );
    // mRawData->erase( mRawData->begin() );

    tempData = *( (*piter)++ );

    mChlNum = (tempData & ChlNumMask ) >> ChlNumR; // Get Channel Num
    mGeo = (tempData & GeoMask ) >> GeoR;	   // Get Geo

    // On crate No.1
    if( 0x01 != ((tempData & CrateMask ) >> CrateR) )
    {
	// Crate number error
	return false;
    }

    return true;
}


// get data from 792 785N 785 and 775N ----------
bool CModul::getData()
{
    short chl;
    int data;
    short mark;

    while ( 1 ) 
    {
	tempData = *( (*piter)++ );

	mark = ( tempData & DataMarkMask ) >> DataMarkR ;
	chl =  ( tempData & ChlMask32 ) >> ChlR32 ;
	data = ( tempData & DataMask ) ;

	if( DataMarkEnd == mark )
	{
	    break;
	}
	else
	{
	    *( pData + chl ) = data;
	}
	
    }

    return true;
}


// get data from 839AC ----------
bool CMv830ac::getData()
{
    // Function out of service
    return false;
}


bool CModul::Decode()
{
    // May there be enough clouds in your life to make a beautiful sunset.

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



  
// unsigned short CModul::checkMark()
// {
//     return ( (tempData & DataMarkMask ) >> DataMarkR );

// }



