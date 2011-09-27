#pragma once
// Copyright 2011, Raffaele Rialdi http://www.iamraf.net
// 
// Call the methods for enable/disable/suspend/resume/...

#include "stdafx.h"
#include <ShObjIdl.h>
//IPackageDebugSettings
//CLSID_PackageDebugSettings
//IID_IPackageDebugSettings

using namespace ATL;

#include <string>
using namespace std;

#define EXIT_IF_INVALID		{ if(!ValidatePackageName()) return; }

class ShellPackage
{
private:
	wstring _packageFullName;
	HRESULT _lastHRESULT;

	CComQIPtr<IPackageDebugSettings> CreatePackageDebugSettings()
	{
		CComQIPtr<IPackageDebugSettings> sp;
		_lastHRESULT = sp.CoCreateInstance(CLSID_PackageDebugSettings, NULL, CLSCTX_ALL);
		return sp;
	}

	BOOL ValidatePackageName()
	{
		if(_packageFullName.size() == 0)
		{
			_lastHRESULT = E_FAIL;
			return FALSE;
		}
		return TRUE;
	}

public:
	ShellPackage()
	{
	}

	ShellPackage(const wstring& packageFullName)
	{
		_packageFullName = packageFullName;
	}

	HRESULT GetLastHRESULT()
	{
		return _lastHRESULT;
	}

	void EnableDebugging(const wstring& debuggerFullName, PZZWSTR pEnvironment = NULL)
	{
		EXIT_IF_INVALID
		CComQIPtr<IPackageDebugSettings> sp = CreatePackageDebugSettings();
		if(sp == NULL) return;
		_lastHRESULT = sp->EnableDebugging(_packageFullName.c_str(), debuggerFullName.c_str(), pEnvironment);
	}

	void DisableDebugging()
	{
		EXIT_IF_INVALID
		CComQIPtr<IPackageDebugSettings> sp = CreatePackageDebugSettings();
		if(sp == NULL) return;
		_lastHRESULT = sp->DisableDebugging(_packageFullName.c_str());
	}

	void Suspend()
	{
		EXIT_IF_INVALID
		CComQIPtr<IPackageDebugSettings> sp = CreatePackageDebugSettings();
		if(sp == NULL) return;
		_lastHRESULT = sp->Suspend(_packageFullName.c_str());
	}

	void Resume()
	{
		EXIT_IF_INVALID
		CComQIPtr<IPackageDebugSettings> sp = CreatePackageDebugSettings();
		if(sp == NULL) return;
		_lastHRESULT = sp->Resume(_packageFullName.c_str());
	}

	void TerminateAllProcesses()
	{
		EXIT_IF_INVALID
		CComQIPtr<IPackageDebugSettings> sp = CreatePackageDebugSettings();
		if(sp == NULL) return;
		_lastHRESULT = sp->TerminateAllProcesses(_packageFullName.c_str());
	}

	void SetTargetSessionId(ULONG id)
	{
		CComQIPtr<IPackageDebugSettings> sp = CreatePackageDebugSettings();
		if(sp == NULL) return;
		_lastHRESULT = sp->SetTargetSessionId(id);
	}

};