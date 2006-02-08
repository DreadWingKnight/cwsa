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
	 	printf("WebSeedAdder-Console <webseeds> [--include_existing] <Torrent File> [Torrent File [...]] \n\n");
	 	printf("<webseeds> must contain at least one http:// address\nor the webseeds will be removed from the file.\n\n");
	 	printf("If you do not include the <webseeds> paramater,\nthe file will most likely NOT be edited.\n\n");
	 	printf("The <webseeds> paramater is a list of http:// addresses separated by \";\"\n");
	 	printf("Any number of webseeds may be added. Existing webseeds in the torrent will be removed.\n");
    }
    else
    {
        bool include_existing;
        for( int t=2; t<argc; t++ )
        {
             if( t == 2 && string( argv[t] ) == string( "--include_existing" ) )
             {
                 include_existing = true;
             }
             else
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
                     CAtomList *pWebSeedList = new CAtomList();
			 	     if( include_existing == true )
			 	     {
                         printf("\nChecking for existing seeds");
                         CAtom *pExisting;
                         pExisting = ((CAtomDicti *)pTorrent)->getItem( "httpseeds" , NULL );
                         if ( pExisting && pExisting->isList( ) )
                         {
                              printf(", Existing list present");
                              pWebSeedList = (CAtomList *)pExisting;
                         }
                         else
                         {
                             printf(", Existing list not present");
                             pWebSeedList = new CAtomList();
                         }
                     }
                     else
                     {
                         pWebSeedList = new CAtomList();
                     }
                     printf("\nAdding new seed");
                     string sWebSeedParamater;
		 	 	     sWebSeedParamater = string( argv[1] );
			 	     if( sWebSeedParamater.find_first_of( ";") == string :: npos )
			 	     {
                         printf( " to torrent\n" );
			 		     pWebSeedList->addItem( new CAtomString( sWebSeedParamater ) );
			 	     }
			 	     else
			 	     {
                          printf( "s to torrent\n");
                          vector<string> v_sWebSeeds;
			 		      StringUtils::SplitString( sWebSeedParamater, ";", v_sWebSeeds, false);
  			    	      for( vector<string> :: iterator i = v_sWebSeeds.begin(); i != v_sWebSeeds.end( ); i++ )
  			    	      {
					 	       if( (*i).find("http://") != string::npos )
				 		       pWebSeedList->addItem( new CAtomString( (*i) ) );
					      }
 			 	     }
 			 	     if( include_existing == true && ((CAtomDicti *)pTorrent)->getItem( "httpseeds" , NULL ) == NULL )
			 	     ((CAtomDicti *)pTorrent)->setItem( "httpseeds", pWebSeedList );
		         }
			     UTIL_MakeFile( argv[t] , Encode( pTorrent ) );
	         }
		     delete pTorrent;
           }
       }
	}
#ifdef WIN32
	system("PAUSE");
#endif
    return EXIT_SUCCESS;
}
