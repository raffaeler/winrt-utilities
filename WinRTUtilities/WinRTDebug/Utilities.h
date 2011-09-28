#pragma once
#include "stdafx.h"
// Copyright 2011, Raffaele Rialdi http://www.iamraf.net
// 
// Command line, copyright, usage, IsUserAdmin (not used at the moment)

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#define szTokens (L"-/")

typedef enum COMMANDLINECHOICE_Type
{
	None	= 0x00,
	List	= 0x01,
	Debug	= 0x02,
	Undebug	= 0x03,
	Suspend = 0x04,
	Resume	= 0x05,
	Terminate = 0x06,
	SessionId = 0x07
} COMMANDLINECHOICE;

struct ActionRequested
{
	COMMANDLINECHOICE Choice;
	std::vector<std::wstring> Parameters;
	std::wstring ToString()
	{
		using namespace std;

		wstringstream ss;
		switch(Choice)
		{
		case List:
			ss << L"List packages";
			break;
		case Debug:
			ss << L"Enable debugging";
			break;
		case Undebug:
			ss << L"Disable debugging";
			break;
		case Suspend:
			ss << L"Suspend processes for the package";
			break;
		case Resume:
			ss << L"Resume processes for the package";
			break;
		case Terminate:
			ss << L"Terminate processes for the package";
			break;
		case SessionId:
			ss << L"Set Session Id";
			break;
		}
		ss << L" " << endl;
		for_each(begin(Parameters), end(Parameters), [&] (const wstring& par) {
			ss << L"\t" << par.c_str() <<  endl;
		});

		return ss.str();
	}
};


class Utilities
{
private:
	// a very very old code for searching the token
	static wchar_t * Utilities::FindOneOf(wchar_t *p1, wchar_t *p2)
	{
		while (*p1 != NULL)
		{
			LPCTSTR p = p2;
			while (*p != NULL)
			{
				if (*p1 == *p++)
					return p1+1;
			}
			p1++;
		}
		return NULL;
	}

public:

	static void Utilities::PrintCopyright()
	{
		using namespace std;

		wstringstream ss;
		ss << L"WinRTDebug v1.0 by Raffaele Rialdi, 2011 - http://www.iamraf.net" << endl;
		ss << L"Project repository: http://WinRT.codeplex.com" << endl;
		ss << L"This utility enable debugging the activation of WinRT Metro applications" << endl;
		//ss << L"Windows 8 or greater required" << endl;
		ss << L"" << endl;
		wcout << ss.str();
	}

	static void Utilities::PrintUsage()
	{
		using namespace std;

		wstringstream ss;
		ss << L"-v ";
		ss << L"   list full names of all the packages" << endl;

		ss << L"-d package debugger";
		ss << L"   enable debugging the package with specified debugger" << endl;

		ss << L"-u package";
		ss << L"   stop debugging the package" << endl;

		ss << L"-s package";
		ss << L"   suspend all the processes running the package" << endl;

		ss << L"-r package";
		ss << L"   resume all the processes running the package" << endl;

		ss << L"-t package";
		ss << L"   terminate all the processes running the package" << endl;

		ss << L"-i tid    ";
		ss << L"   Set the target session id" << endl;

		ss << L"package name must be full (see -v)" << endl;
		ss << L"debugger path must be the full qualified path name" << endl;
		wcout << ss.str();
	}

	static ActionRequested Utilities::GetCommandLineChoice()
	{
		ActionRequested res;
		res.Choice = None;
		int argc;
		wchar_t **argvW = CommandLineToArgvW(GetCommandLine(), &argc);
		if(argc == 1)
			return res;

		int i=1;	// start from the second (excluding exe)
		argvW++;	// first is exe
		wchar_t *pToken = FindOneOf(*argvW, szTokens);
		if(pToken == NULL)
			return res;

		if(_wcsicmp(pToken, L"v") == 0)
			res.Choice = List;
		else if(_wcsicmp(pToken, L"d") == 0)
			res.Choice = Debug;
		else if(_wcsicmp(pToken, L"u") == 0)
			res.Choice = Undebug;
		else if(_wcsicmp(pToken, L"s") == 0)
			res.Choice = Suspend;
		else if(_wcsicmp(pToken, L"r") == 0)
			res.Choice = Resume;
		else if(_wcsicmp(pToken, L"t") == 0)
			res.Choice = Terminate;
		else if(_wcsicmp(pToken, L"i") == 0)
			res.Choice = SessionId;
		else return res;

		while(i < argc - 1)
		{
			res.Parameters.push_back(argvW[i++]);
		}
		return res;
	}


	// ======================================================================================================================
	// This routine returns TRUE if the caller's process is a member of the Administrators local group.
	// Caller is NOT expected to be impersonating anyone and is expected to be able to open its own 
	// process and process token. 
	static BOOL Utilities::IsUserAdmin()
	{
		BOOL bRes;
		SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
		PSID AdministratorsGroup; 
		bRes = AllocateAndInitializeSid(
			&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
			0, 0, 0, 0, 0, 0, &AdministratorsGroup); 
		if(bRes) 
		{
			if (!CheckTokenMembership(NULL, AdministratorsGroup, &bRes))
				bRes = FALSE;
			FreeSid(AdministratorsGroup); 
		}
		return bRes;
	}

};