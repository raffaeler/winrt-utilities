// WinRTDebug.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "OSVersion.h"
#include "PackageDiscovery.h"
#include "ShellPackage.h"
#include "Utilities.h"

#include <iostream>
using namespace std;

struct _init
{
	_init() {CoInitialize(NULL);}
	~_init() {CoUninitialize();}
} init;


void ListPackages()
{
	auto packages = PackageDiscovery::GetPackages();
	for_each(begin(packages), end(packages), [] (const wstring& package) {
		wcout << package << endl;
	});
}

HRESULT ProcessShellPackage(ActionRequested action)
{
	wstringstream ss;

	HRESULT res = E_FAIL;
	if(action.Choice == SessionId)
	{
		if(action.Parameters.size() < 1)
			return res;

		int id = 0;
		ss = wstringstream(action.Parameters[0]);
		ss >> id;
		if(ss.fail())
			return res;

		ShellPackage pck;
		pck.SetTargetSessionId(id);
		return pck.GetLastHRESULT();
	}

	// for the rest of the parameters, at least the package full name is required
	if(action.Parameters.size() < 1)
		return res;

	ShellPackage pck(action.Parameters[0]);

	switch(action.Choice)
	{
	case Debug:
		// debug requires the debugger full path name too
		if(action.Parameters.size() <2)
			return res;
		pck.EnableDebugging(action.Parameters[1]);
		return pck.GetLastHRESULT();

	case Undebug:
		pck.DisableDebugging();
		return pck.GetLastHRESULT();

	case Suspend:
		pck.Suspend();
		return pck.GetLastHRESULT();

	case Resume:
		pck.Resume();
		return pck.GetLastHRESULT();

	case Terminate:
		pck.TerminateAllProcesses();
		return pck.GetLastHRESULT();
	}

	return res;
}

int wmain(int argc, wchar_t* argv[])
{
	Utilities::PrintCopyright();
	if(!OSVersion::IsWindows8())
	{
		wcout << L"Windows 8 or greater is required" << endl;
		return -1;
	}

	auto action = Utilities::GetCommandLineChoice();
	wcout << action.ToString();

	int res = 0;
	switch(action.Choice)
	{
	case List:
		ListPackages();
		return 0;


	case Debug:
	case Undebug:
	case Suspend:
	case Resume:
	case Terminate:
	case SessionId:
		res = ProcessShellPackage(action);
		if(res == 0) return res;
	}

	Utilities::PrintUsage();
	return res;
}

