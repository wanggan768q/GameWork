#ifndef __IO_CONFIGFILE__H__
#define __IO_CONFIGFILE__H__

#include "IO_InputTextStream.h"
#include "IO_OutputTextStream.h"

class IO_ConfigFile
{
public:
	IO_ConfigFile();
	virtual ~IO_ConfigFile();

public:
	bool Load(const wstring& name, const wstring& separator = _T("="));
	bool Load(IO_InputStream* stream, const wstring& separator = _T("="));
	bool Save(const wstring& name);
	bool Save(IO_OutputStream* stream);
	void Close();
	
public:
	int ReadInt(const wstring& keyName, int defaultValue);
	float ReadFloat(const wstring& keyName, float defaultValue);
	wstring ReadString(const wstring& keyName, const wstring& defaultValue);
	
public:
	bool WriteInt(const wstring& keyName, int setValue);
	bool WriteFloat(const wstring& keyName, float setValue);
	bool WriteString(const wstring& keyName, const wstring& setValue);
	
public:
	bool DeleteKey(const wstring& keyName);
	bool KeyIsExist(const wstring& keyName);
	bool ClearAll();

private:
	
};

#endif /*__IO_CONFIGFILE__H__*/
