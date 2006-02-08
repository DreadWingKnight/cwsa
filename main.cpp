#include "atom.h"
#include "bencode.h"
#include "util.h"
#include "stringsplit.h"
#include "WebSeedAdder_CPP_private.h"

#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    if( !argv[1] || !argv[2] )
    {
	 	printf( "%s %s\n", FILE_DESCRIPTION, VER_STRING);
	 	printf("You failed to include one or more required command line arguments.\n\n");
	 	printf("WebSeedAdder-Console <webseeds> <Torrent File> \n");
	 	printf("<webseeds> must contain at least one http:// address\nor the webseeds will be removed from the file.\n");
	 	printf("If you do not include the <webseeds> paramater,\nthe file will most likely NOT be edited.\n");
    }
    else
    {
        for( int t=2; t<argc; t++ )
        {
	 	CAtom *pTorrent;
	 	pTorrent = DecodeFile( argv[t] );
	 	if( pTorrent->isDicti() )
	 	{
		 	if( string( argv[1] ).find( "http://" ) == string ::npos )
		 	{
			 	printf( "Removing Seed\n" );
			 	((CAtomDicti *)pTorrent)->delItem("httpseeds" );
			}
			else
			{
			 	printf( "Adding Seed" );
 	 		 	CAtomList *pWebSeedList;
		 	 	pWebSeedList = new CAtomList();
  		     	string sWebSeedParamater;
		 	 	sWebSeedParamater = string( argv[1] );
			 	if( sWebSeedParamater.find_first_of( ";") == string :: npos )
			 	{
                    printf( "\n" );
			 		pWebSeedList->addItem( new CAtomString( sWebSeedParamater ) );
			 	}
			 	else
			 	{
                    printf( "s\n");
			 		vector<string> v_sWebSeeds;
			 		StringUtils::SplitString( sWebSeedParamater, ";", v_sWebSeeds, false);
  			    	for( vector<string> :: iterator i = v_sWebSeeds.begin(); i != v_sWebSeeds.end( ); i++ )
  			    	{
					 	 if( (*i).find("http://") != string::npos )
				 		 pWebSeedList->addItem( new CAtomString( (*i) ) );
					}
 			 	}
			 	((CAtomDicti *)pTorrent)->setItem( "httpseeds", pWebSeedList );
			}
			UTIL_MakeFile( argv[t] , Encode( pTorrent ) );
		 }
		 delete pTorrent;
       }
	}
#ifdef WIN32
	system("PAUSE");
#endif
    return EXIT_SUCCESS;
}
