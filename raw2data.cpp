#/***************************************************
# File Name:	raw2data.cpp
# Abstract:
# Author:	zhangzhelucky
# Update History:
#
# 2014-04-08	Start this file
# 2014-04-10	Added File scaning and sorting modul
#
#****************************************************/

#include <string.h>
#include "stdio.h"
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <string>
#include <iostream>
#include "algorithm"

  using namespace std;

#include "log.h"
#include "global.h"
//#include "raw2data.h"

int scanDir( vector<string>* );		// Scan current directory for data files


int main(int argc, char *argv[])
{
    cout << "zhangzhelucky" << endl;
    CLog();

    CEvent::EC = -1;

    // Scan current directory ----------

    vector<string> file_names;

    int fileNum = scanDir( & file_names );

    if( _MAX_FILE_NUM <= fileNum )
    {
	CLog("Too Much Files Found.", true);
	return 0;
    }

    char ch[8];
    sprintf( ch , "%d" , fileNum );
    string fileNumStr = ch ;
    fileNumStr = fileNumStr + " files found. Confirm ?";
    CLog( fileNumStr , true );

    do
    {
	cout << "[Y/N] " ;
	char c;
	cin >> c;

	if( ( 'Y' == c ) || ( 'y' == c ) )	break;
	if( ( 'N' == c ) || ( 'n' == c ) )	return 0;

    } while (1);


    // Print all files found ----------

    /*
      for (int i = 0; i < file_names.size() ; i++) 
      {
      cout << file_names[i] << '\t';
      }
    */


    // Open file for Decoding ----------

    for (int i = 0; i < file_names.size() ; i++) 
    {
    	cout << endl 
	     << "----Preparing for decoding file: " << file_names[i] << endl;


	fstream datafile( file_names[i] , ios::in | ios::binary );


	// Get file header and the comments ---
	char comment[1024];
	datafile.get(name,1024);
	cout << "---File Comments: " << comment  << endl;

	datafile.seekg(1024 + 4,ios::beg);	// Skip the header and the first
						// event separator(4 byte)


	bool isFileEnd = false;

	while( true != isFileEnd )
	{
	    CEvent event( &datafile );
	    isFileEnd = event.loadEvent();

	}

    }


    CLog();
    return 0;
}


int scanDir(vector<string>* file_names)
{
    int file_counter = 0;
    DIR *dp;
    struct dirent *dirp;
    char dirname[] = _DATA_DIRE ;
        
    if( ( dp=opendir(dirname) ) == NULL )
    {
	CLog("Wrong Directory ! Check data directory setting in global.h . ",
	     true);
	return 0;
    }

    while( (dirp=readdir(dp) ) != NULL )
    {
	string tempStr = dirp->d_name;
	if( ("." == tempStr) || (".." == tempStr) )	continue;

	file_names->push_back( dirp->d_name );	    
	file_counter ++;
    }

    sort( file_names->begin() , file_names->end() );

    return file_counter;
}



