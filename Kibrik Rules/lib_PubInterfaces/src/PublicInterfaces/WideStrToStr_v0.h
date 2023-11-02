#ifndef WideStrToStr_h
#define WideStrToStr_h

#include <string>
#include <string.h>
#include <Windows.h>

using std::string;
using std::wstring;
//using namespace std;
class utils {
public:
	static string PlusString( char*, char* );
	static string PlusString( const char*, const char* ) ;
	static string PlusString( const char*, char* ) ;
	static string PlusString( char*, const char* ) ;

	static string IntToStr(long tmp);
	static string RealToStr(float tmp);

	static wstring IntToWideStr(long tmp);
	static wstring RealToWideStr(float tmp);

	static BSTR StringToBSTR(const char* pSrc);
	
	static string const WideStrToStr( std::wstring const & in, unsigned charSet = CP_ACP );
	static wstring const StrToWideStr( std::string const & in, unsigned charSet = CP_ACP );
	static wchar_t* const StrToWideStrBig( std::string const & in, unsigned charSet = CP_ACP );

	static string const WideStrToStr_( const wchar_t* in, unsigned charSet = CP_ACP );
	static wstring const StrToWideStr_( const char* in, unsigned charSet = CP_ACP );


	struct String_less
	{
		bool operator() (const char* x, const char* y) const
		{
			return strcmp(x,y)<0 ? true:false ;
		}
	};

	struct WString_less
	{
		bool operator() (const wchar_t* x, const wchar_t* y) const
		{
			return wcscmp(x,y)<0 ? true:false ;
		}
	};

};

#endif
