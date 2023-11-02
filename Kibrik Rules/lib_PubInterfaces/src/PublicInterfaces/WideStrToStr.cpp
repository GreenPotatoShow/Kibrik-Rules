#include <sstream>

//#include <string.h>
#include "WideStrToStr.h"

using std::stringstream;
using std::string;
using std::wstring;

string PlusString( char* s1, char* s2 )
{
	stringstream out;
	out << s1 << s2;
	return out.str();
}

string PlusString( const char* s1, const char* s2 )
{
	stringstream out;
	out << s1 << s2;
//	return out.str().c_str();
	return out.str();
}

string PlusString( const char* s1, char* s2 )
{
	stringstream out;
	out << s1 << s2;
	return out.str();
}

string PlusString( char* s1, const char* s2 )
{
	stringstream out;
	out << s1 << s2;
	return out.str();
}

string utils::IntToStr(long tmp) {
	stringstream out;
	out << tmp;
	return out.str();
}

string utils::RealToStr(float tmp) {
	stringstream out;
	out << tmp;
	return out.str();
}

wstring utils::IntToWideStr(long tmp) {
	std::wostringstream out;
	out << tmp;
	return out.str();
}

wstring utils::RealToWideStr(float tmp) {
	std::wostringstream out;
	out << tmp;
	return out.str();
}

string const utils::WideStrToStr( std::wstring const & in, unsigned charSet )
{
    if( in.empty() ) return "";
    int const bigEnough = 256;
    char dest[ bigEnough ];
    int len = ::WideCharToMultiByte( charSet, 0, in.c_str(), -1, dest, bigEnough, 0, 0 );
    if( len ){ // success
        dest[ len ] = 0;
		return std::string(dest);
    }

    // rare case
    string outStr;
    if( ::GetLastError() == ERROR_INSUFFICIENT_BUFFER )
    {
        len = ::WideCharToMultiByte( charSet, 0, in.c_str(), -1, dest, 0, 0, 0 );
        char * out = new char[ len + 1 ];
        len = ::WideCharToMultiByte( charSet, 0, in.c_str(), -1, out, len, 0, 0 );
        if( len ){ // success
            out[ len ] = 0;
            outStr = out;
        }
        delete [] out;
    }
    return outStr;
}

/*BSTR __stdcall ConvertStringToBSTR(const char* pSrc) throw (_com_error) 
{
  int size = ::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pSrc, -1, 0, 0);
  LPWSTR dst = ::SysAllocStringLen(0, size);
  size = ::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pSrc, -1, dst, size);
  if (size <= 0) _com_issue_error(E_OUTOFMEMORY);
  return dst;
}//*/

//-------------------------------------------------------------------------
wstring const utils::StrToWideStr( std::string const & in, unsigned charSet )
{
	if( in.empty() ) return std::wstring();
    int const bigEnough = 256;
    wchar_t dest[ bigEnough ];
    int len = ::MultiByteToWideChar( charSet, 0, in.c_str(), static_cast<int>(in.length()), dest, bigEnough );
    if( len ){ // success
        dest[ len ] = 0;
        return std::wstring(dest);
    }
    // rare case
    std::wstring outStr;
    if( ::GetLastError() == ERROR_INSUFFICIENT_BUFFER )
    {
        len = ::MultiByteToWideChar( charSet, 0, in.c_str(), static_cast<int>(in.length()), dest, 0 );
        wchar_t * out = new wchar_t[ len + 1 ];
        len = ::MultiByteToWideChar( charSet, 0, in.c_str(), static_cast<int>(in.length()), out, len );
        if( len ){ // success
            out[ len ] = 0;
            outStr = out;
        }
        delete [] out;
    }
    return outStr;
}
/*/-------------------------------------------------------------------------
wchar_t * const utils::StrToWideStrBig( std::string const & in, unsigned charSet )
{
	if( in.empty() ) return 0;
	// rare case
	int len = ::MultiByteToWideChar( charSet, 0, in.c_str(), static_cast<int>(in.length()), 0, 0 );
	wchar_t * out = new wchar_t[ len + 1 ];
	len = ::MultiByteToWideChar( charSet, 0, in.c_str(), static_cast<int>(in.length()), out, len );
	if( !len ) { delete [] out; return 0; }
	// success
	out[ len ] = 0;
	return out;
} //*/
//-------------------------------------------------------------------------
BSTR utils::StringToBSTR(const char* pSrc) //throw (_com_error)
{
  int size = ::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pSrc, -1, 0, 0);
  LPWSTR dst = ::SysAllocStringLen(0, size);
  size = ::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pSrc, -1, dst, size);
  //if (size <= 0) _com_issue_error(E_OUTOFMEMORY);
  return dst;
}

std::string const utils::WideStrToStr_( const wchar_t* in, unsigned charSet )
{
    if( !in || !in[0] ) return "";
    int const bigEnough = 256;
    char dest[ bigEnough ];
    int len = ::WideCharToMultiByte( charSet, 0, in, -1, dest, bigEnough, 0, 0 );
    if( len ){ // success
        dest[ len ] = 0;
		return string(dest);
    }

    // rare case
    string outStr;
    if( ::GetLastError() == ERROR_INSUFFICIENT_BUFFER )
    {
        len = ::WideCharToMultiByte( charSet, 0, in, -1, dest, 0, 0, 0 );
        char * out = new char[ len + 1 ];
        len = ::WideCharToMultiByte( charSet, 0, in, -1, out, len, 0, 0 );
        if( len ){ // success
            out[ len ] = 0;
            outStr = out;
        }
        delete [] out;
    }
    return outStr;
}
//-------------------------------------------------------------------------
wstring const utils::StrToWideStr_( const char* in, unsigned charSet )
{
	if( !in || !in[0] ) return std::wstring();
    int const bigEnough = 256;
    wchar_t dest[ bigEnough ];
    int in_len = static_cast<int>(strlen(in)+1);
    int len = ::MultiByteToWideChar( charSet, 0, in, in_len, dest, bigEnough );
    if( len ){ // success
        dest[ len ] = 0;
		return wstring(dest);
    }
    // rare case
    wstring outStr;
    if( ::GetLastError() == ERROR_INSUFFICIENT_BUFFER )
    {
        len = ::MultiByteToWideChar( charSet, 0, in, in_len, dest, 0 );
        wchar_t * out = new wchar_t[ len + 1 ];
        len = ::MultiByteToWideChar( charSet, 0, in, in_len, out, len );
        if( len ){ // success
            out[ len ] = 0;
            outStr = out;
        }
        delete [] out;
    }
    return outStr;
}

/*
#include <stdlib.h>

	size_t len = mbstowcs(NULL, in, 0)+1;
	wchar_t *out = new wchar_t[len];
	mbstowcs(out, in, len);
    return out;
//*/

