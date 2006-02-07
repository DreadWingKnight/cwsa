#include "util.h"

void UTIL_MakeFile( const char *szFile, string strContents )
{
	FILE *pFile = NULL;

	if( ( pFile = fopen( szFile, "wb" ) ) == NULL )
	{
		printf( "warning - unable to open %s for writing\n", szFile );

		return;
	}

	fwrite( (void *)strContents.c_str( ), sizeof( char ), strContents.size( ), pFile );
	fclose( pFile );
}

string UTIL_StringToHash( const string &strString )
{
	// convert a readable string hash to a 20 character hash

	string strHash;

	if( strString.size( ) != 40 && strString.size() != 41 )
		return string( );

    if( strString.size() == 40 )
	for( unsigned long i = 0; i < strString.size( ); i += 2 )
	{
		char pBuf[2];

		memset( pBuf, 0, sizeof( char ) * 2 );

		pBuf[0] = strString[i];
		pBuf[1] = strString[i + 1];

		unsigned int c;

		sscanf( pBuf, "%02x", &c );

		strHash += c;
	}
	else if( strString.size() == 41)
	for( unsigned long i = 1; i < strString.size( ); i += 2 )
	{
		char pBuf[2];

		memset( pBuf, 0, sizeof( char ) * 2 );

		pBuf[0] = strString[i];
		pBuf[1] = strString[i + 1];

		unsigned int c;

		sscanf( pBuf, "%02x", &c );

		strHash += c;
	}

	return strHash;
}
