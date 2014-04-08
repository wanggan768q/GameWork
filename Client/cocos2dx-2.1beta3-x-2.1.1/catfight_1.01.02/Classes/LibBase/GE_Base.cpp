#include "GE_Base.h"

void wsplitpath(const wchar* path, wchar* drv, wchar* dir, wchar* name, wchar* ext)
{
	const wchar* end; /* end of processed string */
	const wchar* p;	  /* search pointer */
	const wchar* s;	  /* copy pointer */

	/* extract drive name */
	if (path[0] && path[1]==':') {
		if (drv) {
			*drv++ = *path++;
			*drv++ = *path++;
			*drv = L'\0';
		}
	} else if (drv)
		*drv = L'\0';

	/* search for end of string or stream separator */
	for(end=path; *end && *end!=L':'; )
		end++;

	/* search for begin of file extension */
	for(p=end; p>path && *--p!=L'\\' && *p!=L'/'; )
		if (*p == L'.') {
			end = p;
			break;
		}

		if (ext)
			for(s=end; *ext=*s++; )
				ext++;

		/* search for end of directory name */
		for(p=end; p>path; )
			if (*--p=='\\' || *p=='/') {
				p++;
				break;
			}

			if (name) {
				for(s=p; s<end; )
					*name++ = *s++;

				*name = L'\0';
			}

			if (dir) {
				for(s=path; s<p; )
					*dir++ = *s++;

				*dir = L'\0';
			}
}

wstring GE_GetAbsolutePath(const wstring& name, const wstring& relative)
{
	wstring path = relative.substr(0, relative.length() - 1) + name.substr(1);

	return path;
}

wstring GE_GetFilePath(const wstring& name)
{
	wchar drive[_MAX_DRIVE];
	wchar dir[_MAX_DIR];
	wchar path[_MAX_PATH];

	wsplitpath(name.c_str(), drive, dir, NULL, NULL);
	wcscpy(path, drive);
	wcscat(path, dir);

	return path;
}

bool GE_IsRelativePath(const wstring& name)
{
	if(name.empty())
	{
		return false;
	}

	if(name[0] == L'.')
	{
		return true;
	}

	return false;
}

bool GE_GetResourcePath(const wstring& name, wstring& path)
{
	string patha = GE_U2A(name);

	std::string strFullpath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(patha.c_str());
	const char* fullpath = strFullpath.c_str();
	
	if(fullpath == NULL)
	{
		return false;
	}

	wstring fullpathw = GE_A2U(fullpath);

	path = fullpathw;

	return true;
}

string GE_U2A(const wstring& str)
{
	string ret;

	ret.resize(str.size());

	for(size_t i = 0; i < str.size(); ++i)
	{
		ret[i] = (string::value_type)str[i];
	}

	return ret;
}

wstring GE_A2U(const string& str)
{
	wstring ret;

	ret.resize(str.size());

	for(size_t i = 0; i < str.size(); ++i)
	{
		ret[i] = (wstring::value_type)str[i];
	}

	return ret;
}

utime GE_GetTime()
{
	struct timeval now; 
	gettimeofday(&now, NULL); 
	return (now.tv_sec * 1000 + now.tv_usec / 1000); 
}

