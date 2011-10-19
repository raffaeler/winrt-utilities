#pragma once
// Copyright 2011, Raffaele Rialdi http://www.iamraf.net
// 
// Call the methods for enable/disable/suspend/resume/...

#include "stdafx.h"
#include <ShObjIdl.h>
//IPackageDebugSettings
//CLSID_PackageDebugSettings
//IID_IPackageDebugSettings

#include <string>

#define EXIT_IF_INVALID		{ if(!ValidatePackageName()) return; }

class ShellPackage
{
private:
	std::wstring _packageFullName;
	HRESULT _lastHRESULT;

	ATL::CComQIPtr<IPackageDebugSettings> CreatePackageDebugSettings()
	{
		ATL::CComQIPtr<IPackageDebugSettings> sp;
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
		_lastHRESULT = S_OK;
	}

	ShellPackage(const std::wstring& packageFullName)
	{
		_packageFullName = packageFullName;
		_lastHRESULT = S_OK;
	}

	HRESULT GetLastHRESULT()
	{
		return _lastHRESULT;
	}

	void EnableDebugging(const std::wstring& debuggerFullName, PZZWSTR pEnvironment = NULL)
	{
		EXIT_IF_INVALID
		_lastHRESULT = S_OK;
		ATL::CComQIPtr<IPackageDebugSettings> sp = CreatePackageDebugSettings();
		if(sp == NULL) return;
		_lastHRESULT = sp->EnableDebugging(_packageFullName.c_str(), debuggerFullName.c_str(), pEnvironment);
	}

	void DisableDebugging()
	{
		EXIT_IF_INVALID
		_lastHRESULT = S_OK;
		ATL::CComQIPtr<IPackageDebugSettings> sp = CreatePackageDebugSettings();
		if(sp == NULL) return;
		_lastHRESULT = sp->DisableDebugging(_packageFullName.c_str());
	}

	void Suspend()
	{
		EXIT_IF_INVALID
		ATL::CComQIPtr<IPackageDebugSettings> sp = CreatePackageDebugSettings();
		_lastHRESULT = S_OK;
		if(sp == NULL) return;
		_lastHRESULT = sp->Suspend(_packageFullName.c_str());
	}

	void Resume()
	{
		EXIT_IF_INVALID
		_lastHRESULT = S_OK;
		ATL::CComQIPtr<IPackageDebugSettings> sp = CreatePackageDebugSettings();
		if(sp == NULL) return;
		_lastHRESULT = sp->Resume(_packageFullName.c_str());
	}

	void TerminateAllProcesses()
	{
		EXIT_IF_INVALID
		_lastHRESULT = S_OK;
		ATL::CComQIPtr<IPackageDebugSettings> sp = CreatePackageDebugSettings();
		if(sp == NULL) return;
		_lastHRESULT = sp->TerminateAllProcesses(_packageFullName.c_str());
	}

	void SetTargetSessionId(ULONG id)
	{
		ATL::CComQIPtr<IPackageDebugSettings> sp = CreatePackageDebugSettings();
		_lastHRESULT = S_OK;
		if(sp == NULL) return;
		_lastHRESULT = sp->SetTargetSessionId(id);
	}

};