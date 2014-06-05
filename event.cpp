
#/***************************************************
# File Name:	event.cpp
# Abstract:
# Author:	zhangzhelucky
# Update History:
#
#
#
#****************************************************/

#include <event.h>
#include <iostream>

using namespace std;

#include "moduls.h"


inline int geti32(fstream *pf);

CEvent::CEvent( fstream* pf )
{
    pDataFile = pf;

}


bool CEvent::loadEvent()
{
    int temp = 0;

    while ( _EVENT_SEPARATOR != temp )  
    {
	temp = geti32( pDataFile );
	RawData.push_back( temp );

	if(  ( EOF == pDataFile->peek() ) )
	{
	    return true;	// To indicate the end of current file
	}

    }

    return false;

}


bool CEvent::getEventHeader()
{
    iter = RawData.begin();

    // Check Event Separator ----------
    if( _EVENT_SEPARATOR != (*iter) )
    {
	// Separator missing error
    }
    else
    {
	iter++;
    }
 
    // Check Events Counter ----------
    if( (EC+1) != (*iter) )
    {
	// Event counter error
    }
    else if( 0x10000000 < (*iter) )
    {
	// Event counter overflow error
    }
    else
    {
	EC = *iter;
	iter++;
    }
    
    // Jump over the Header ----------
    iter += 8;

    return true;
}

bool CEvent::Decode()
{
    CModul* modul;

    while( RawData.end() != iter )
    {
	int mark = ( (*iter) & 0x07000000 ) >> 24;
	int geo =  ( (*iter) & 0xf8000000 ) >> 27;

	// Check the Modul Header Mark
	if( 0x2 != mark )
	{
	    iter ++;
	    continue;
	} 
	else
	{
	    // Branch to each modul based on defferent GEO
	    switch( geo )
	    {
	      case 4 :
		modul = new CMv785N( &(DataReg.v785n_4) , & iter );
		break;

	      case 5 : 
		modul = new CMv785N( &(DataReg.v775n_5) , & iter );
		break;

	      case 7 : 
		modul = new CMv785N( &(DataReg.v775n_7) , & iter );
		break;

	      case 8 : 
		modul = new CMv785N( &(DataReg.v775n_8) , & iter );
		break;

	      case 10 : 
		modul = new CMv785N( &(DataReg.v785_10) , & iter );
		break;

	      case 12 : 
		modul = new CMv785N( &(DataReg.v792_12) , & iter );
		break;

	      case 13 : 
		modul = new CMv785N( &(DataReg.v792_13) , & iter );
		break;

	      case 15 : 
		modul = new CMv785N( &(DataReg.v792_15) , & iter );
		break;

	      case 16 : 
		modul = new CMv785N( &(DataReg.v792_16) , & iter );
		break;

	    }
	}

	delete( modul );

    }
}


inline int geti32( fstream *pf )
{
    int temp[4]; 
    
    for (int i=0; i < 4; i++)
    {
	temp[i] = pf->get();
    }

    int n = ( temp[3]<<24 ) + 
	    ( temp[2]<<16 ) + 
	    ( temp[1]<<8 ) + 
	    ( temp[0] ) ; 

    return n;
}



