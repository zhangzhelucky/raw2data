
#include <event.h>
#include <iostream>

using namespace std;

inline int geti32(fstream *f);

CEvent::CEvent( fstream* pf )
{
    pDataFile = pf;
    iter = RawData.begin();

}


fstream* CEvent::loadEvent()
{
    int temp = 0;

    while ( _EVENT_SEPARATOR != temp ) 
    {
	temp = geti32( pDataFile );
	RawData.push_back( temp );
	temp = 0;
    }

    return pDataFile;

}


bool CEvent::getEventHeader()
{
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
    while( RawData.end() != iter )
    {
	int mark = ( (*iter) & 0x07000000 ) >> 24;
	int geo =  ( (*iter) & 0xf8000000 ) >> 27;

	if( 0x2 != mark )
	{
	    continue;
	}
	else
	{
	    // =========================================================
	    // =========================================================
	    // =========================================================
	    // =========================================================
	    // =========================================================
	    // =========================================================
	    // =========================================================
	    // =========================================================
	    // =========================================================
	    // =========================================================
	    // =========================================================
	    // =========================================================
	    // =========================================================
	    // =========================================================
	}
	

    }


}


inline int geti32( fstream *f )
{
    int temp[4]; 
    
    for (int i=0; i < 4; i++)
    {
	temp[i] = f->get();
    }

    int n = ( temp[3]<<24 ) + 
	    ( temp[2]<<16 ) + 
	    ( temp[1]<<8 ) + 
	    ( temp[0] ) ; 

    return n;
}



