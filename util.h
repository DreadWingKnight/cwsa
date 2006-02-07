#ifndef UTIL_H
 #define UTIL_H
#include <stdio.h>
#include <time.h>
#include <map>
#include <string>
#include <vector>
#include <utility>

using namespace std;

 typedef __int64 int64;
 typedef unsigned __int64 uint64;

void UTIL_MakeFile( const char *szFile, string strContents );
string UTIL_StringToHash( const string &strString );

#endif
