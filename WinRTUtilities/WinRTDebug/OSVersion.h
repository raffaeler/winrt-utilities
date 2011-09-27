#pragma once
// Copyright 2011, Raffaele Rialdi http://www.iamraf.net
// 
// Check the OS Version


#include "stdafx.h"
using namespace ATL;

#include <string>
using namespace std;

class OSVersion
{
private:
	static void OSVersion::GetMajorMinorOSVersion(DWORD* major, DWORD* minor)
	{
		*major = 0;
		*minor = 0;
		OSVERSIONINFO version;
		version.dwOSVersionInfoSize = sizeof(version);
		if(!::GetVersionEx(&version))
			return;
		*major = version.dwMajorVersion;
		*minor = version.dwMinorVersion;
	}
public:
	static bool OSVersion::IsWindows8()
	{
		DWORD major, minor;
		GetMajorMinorOSVersion(&major, &minor);
		if(major == 6)
		{
			if(minor >= 2)
				return true;
			else
				return false;
		}
		if(major > 6)
			return true;
		return false;
	}
	
};