#pragma once

#include "constParameter.h"

//Command
enum eCommand
{
	eCommUp = 0
	, eCommLeft
	, eCommDown
	, eCommRight
	, eCommUnknow
};

static wstring s2ws(const string & str)
{
	int size_needed = MultiByteToWideChar(CP_ACP, 0, &str[0], (int)str.size(), NULL, 0);
	wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_ACP, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
	
}

static string ws2s(const wstring& wstr)
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, 0);
	string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, 0);
	return strTo;
}

class command
{
public:
	command()
		:_eType(eCommUnknow)
		,_from("")
	{}
	command(eCommand cmd, string from)
		:_eType(cmd)
		, _from(from)
	{}
public:
	eCommand _eType;
	string _from;
};