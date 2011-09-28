#pragma once
// Copyright 2011, Raffaele Rialdi http://www.iamraf.net
// 
// Get the full names for all the installed packages from the registry

#include "stdafx.h"

#include <string>
#include <vector>
#include <algorithm>


class PackageDiscovery
{
private:
public:
	static std::vector<std::wstring> PackageDiscovery::GetPackages()
	{
		using namespace std;

		vector<wstring> list;
		LPCTSTR regKey = L"Software\\Classes\\ActivatableClasses\\Package";
		ATL::CRegKey reg;
		if(reg.Open(HKEY_CURRENT_USER, regKey) != ERROR_SUCCESS)
			return list;
		int i = 0;
		wchar_t buffer[MAX_PATH * 2];
		DWORD len;
		LONG ret;
		do
		{
			len = _countof(buffer);
			ret = reg.EnumKey(i++, buffer, &len);
			if(ret != ERROR_SUCCESS && ret != ERROR_NO_MORE_ITEMS)
				return list;

			list.push_back(wstring(buffer, len));
		} while (ret != ERROR_NO_MORE_ITEMS);

		sort(begin(list), end(list));
		return list;
	}

};