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
	 	printf("WebSeedAdder-Console <webseeds/--use_wsa_config> [--include_existing] <Torrent\nFile> [Torrent File [...]] \n\n");
	 	printf("<webseeds> must contain at least one http:// address or the webseeds will be\nremoved from the file unless the --use_wsa_config paramater is passed.\n\n");
	 	printf("If you do not include the <webseeds> paramater, the file will most likely NOT\nbe edited.\n\n");
	 	printf("The <webseeds> paramater is a list of http:// addresses separated by \";\"\n");
	 	printf("Any number of webseeds may be added. Existing webseeds in the torrent will be\nremoved unless the --include_existing paramater is passed.\n");
	 	printf("The --use_wsa_config paramater uses the wsa.configure file from EAD's\nVB.Net Webseed adder application.\n" );
    }
    else
    {
        CAtom *pWSAConfig;
#ifdef WIN32
        pWSAConfig = DecodeFile( ".\\wsa.configure" );
#else
        pWSAConfig = DecodeFile( "./wsa.configure" );
#endif
        CAtomList *pWSAConfigList = new CAtomList();
        if( pWSAConfig->isDicti() )
        {
            CAtom *pCheck;
            pCheck = ((CAtomDicti *)pWSAConfig)->getItem( "seeds" , NULL);
            if( pCheck && pCheck->isList() )
                pWSAConfigList = (CAtomList *)pCheck;
        }
        bool include_existing;
        for( int t=2; t<argc; t++ )
        {
             if( t == 2 && string( argv[t] ) == string( "--include_existing" ) )
             {
                 continue;
             }
             else
             {
                 CAtom *pTorrent;
	 	         pTorrent = DecodeFile( argv[t] );
	 	         if( pTorrent->isDicti() )
	 	         {
		 	         if( string( argv[1] ).find( "http://" ) == string ::npos && string(argv[1]) != string("--use_wsa_config") )
		 	         {
			 	         printf( "Removing Seed\n" );
			 	         ((CAtomDicti *)pTorrent)->delItem("httpseeds" );
		             }
                 else
			     {
			 	     printf( "Adding Seed" );
                     CAtomList *pWebSeedList = new CAtomList();
			 	     if( string( argv[2] ) == string( "--include_existing" ) )
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
                             ((CAtomDicti *)pTorrent)->setItem( "httpseeds", pWebSeedList );
                         }
                     }
                     else
                     {
                         printf( ", Removing existing seeds" );
   			 	         ((CAtomDicti *)pTorrent)->delItem( "httpseeds" );
                         pWebSeedList = new CAtomList();
                         ((CAtomDicti *)pTorrent)->setItem( "httpseeds", pWebSeedList );
                     }
                     printf("\nAdding new seed");
                     string sWebSeedParamater;
		 	 	     sWebSeedParamater = string( argv[1] );
			 	     if( sWebSeedParamater.find_first_of( ";") == string :: npos && string(argv[1]) != string("--use_wsa_config") )
			 	     {
                         printf( " to torrent\n" );
			 		     pWebSeedList->addItem( new CAtomString( sWebSeedParamater ) );
			 	     }
			 	     else if (string(argv[1]) == string("--use_wsa_config") )
			 	     {
                          printf( "(s) from wsa.config to torrent\n");
                          vector<CAtom *> v_aWebSeeds;
                          v_aWebSeeds = pWSAConfigList->getValue();
                          for( vector<CAtom *> :: iterator i = v_aWebSeeds.begin(); i != v_aWebSeeds.end(); i++ )
                          {
                               printf( ".");
                               pWebSeedList->addItem( (*i) );
                          }
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
		         }
		         printf( "\n");
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
