
#include <event.h>
#include <iostream>

using namespace std;

inline int geti32(fstream *f);

CEvent::CEvent( fstream* pf )
{
    pDataFile = pf;
    
}


fstream* CEvent::loadEvent()
{
    int temp = 0;

    while ( _EVENT_SEPARATOR != temp ) 
    {
	temp = geti32( pDataFile );
	RawData.push_back( temp );
    }

    return pDataFile;

}








inline int geti32(fstream *f)
{
    int temp[4]; 
    
    for (int i=0; i < 4; i++)
    {
	temp[i] = f->get();
    }

    int n = (temp[3]<<24) + 
	    (temp[2]<<16) + 
	    (temp[1]<<8) + 
	    (temp[0]) ; 

    return n;
}



