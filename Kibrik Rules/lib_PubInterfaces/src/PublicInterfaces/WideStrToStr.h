#ifndef WideStrToStr_h
#define WideStrToStr_h

#include <string>
#include <string.h>
#include <Windows.h>


//using namespace std;
namespace utils {

	std::string IntToStr(long tmp);
	std::string RealToStr(float tmp);

	std::wstring IntToWideStr(long tmp);
	std::wstring RealToWideStr(float tmp);

	BSTR StringToBSTR(const char* pSrc);
	
	std::string const WideStrToStr( std::wstring const & in, unsigned charSet = CP_ACP );
	std::wstring const StrToWideStr( std::string const & in, unsigned charSet = CP_ACP );

	std::string const WideStrToStr_( const wchar_t* in, unsigned charSet = CP_ACP );
	std::wstring const StrToWideStr_( const char* in, unsigned charSet = CP_ACP );


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

}

#endif
