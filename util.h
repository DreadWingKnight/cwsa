#ifndef UTIL_H
 #define UTIL_H
#include <stdio.h>
#include <time.h>
#include <map>
#include <string>
#include <vector>
#include <utility>

using namespace std;

#ifdef WIN32
 typedef __int64 int64;
 typedef unsigned __int64 uint64;
#else
 typedef long long int64;
 typedef unsigned long long uint64;
#endif


void UTIL_MakeFile( const char *szFile, string strContents );
string UTIL_StringToHash( const string &strString );

#endif
