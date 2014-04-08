#include "HSBase.h"


CCSize HSBase::m_MaxImageSize = CCSizeMake(0,0);

HSBase::HSBase(void)
{
}

HSBase::~HSBase(void)
{
}

void HSBase::HSMessageBox_(string strMsg,const char* strTitle/* = " HSDebug "*/)
{
#if WIN32
	CCMessageBox(strMsg.c_str(),strTitle);
#else
	//CCMessageBox(HS_GBK_TO_UTF8(strMsg),strTitle);
	CCMessageBox(strMsg.c_str(),strTitle);
#endif
	
}

CCPoint HSBase::GetLocationPoint( CCTouch *pTouch ,CCNode* node)
{
	return node->convertTouchToNodeSpaceAR(pTouch);
}

std::string HSBase::GetStringWithWstring( const wstring& ws )
{
// 	string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";
// 	setlocale(LC_ALL, "chs"); 
// 	const wchar_t* _Source = ws.c_str();
// 	size_t _Dsize = 2 * ws.size() + 1;
// 	char *_Dest = new char[_Dsize];
// 	memset(_Dest,0,_Dsize);
// 	wcstombs(_Dest,_Source,_Dsize);
// 	string result = _Dest;
// 	delete []_Dest;
// 	setlocale(LC_ALL, curLocale.c_str());
	
	string result;

	result.resize(ws.size());

	for(size_t i = 0; i < ws.size(); ++i)
	{
		result[i] = (string::value_type)ws[i];
	}
	return result;
}

wstring HSBase::GetWstringWithString( const std::string& s )
{
	// 	std::string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";
	// 	setlocale(LC_ALL, "chs"); 
	// 	const char* _Source = s.c_str();
	// 	size_t _Dsize = s.size() + 1;
	// 	wchar_t *_Dest = new wchar_t[_Dsize];
	// 	wmemset(_Dest, 0, _Dsize);
	// 	mbstowcs(_Dest,_Source,_Dsize);
	// 	std::wstring result = _Dest;
	// 	delete []_Dest;
	// 	setlocale(LC_ALL, curLocale.c_str());
	wstring ret;

	ret.resize(s.size());

	for(size_t i = 0; i < s.size(); ++i)
	{
		ret[i] = (wstring::value_type)s[i];
	}

	return ret;
}



int HSBase::Strlen_utf8( string str )
{
	char* buf = (char*)str.c_str();
	int i = 0, j = 0;
	while (buf[i]) 
	{
		if ((0xc0 & buf[i]) != 0x80) j++;
		i++;
	}
	return j;
}

CCSize HSBase::GetScreenSize()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//CCLog("ScreenWidth: %.2f , %.2f",size.width,size.height);
	return size;
}

CCPoint HSBase::GetScreenOrigin()
{
	//cocos2dx_1.0	ccp(0.f,0.f)
	//cocos2dx_2.0	openGLES get
	return ccp(0,0);
}

float HSBase::GetScreenWidth()
{
	CCSize size = HSBase::GetScreenSize();
	return size.width;
}

float HSBase::GetScreenHeight()
{
	CCSize size = HSBase::GetScreenSize();
	return size.height;
}

CCPoint HSBase::GetScreenCentre()
{
	return ccp(HSBase::GetScreenWidth() / 2.f,HSBase::GetScreenHeight() / 2.f);
}

const char* HSBase::GBKToUTF8( string& gbkStr,const char* toCode,const char* fromCode )
{

#if WIN32
	iconv_t iconvH;
	iconvH = iconv_open(fromCode,toCode);
	if(iconvH == 0)
		return "GBKToUTF8 Error";
	const char* strChar = gbkStr.c_str();
	const char** pin = &strChar;
	size_t strLenth = gbkStr.length();
	//char *outbuf = (char *)malloc(strLenth *4);
	char *outbuf = new char[strLenth *4];

	char* pBuff = outbuf;

	memset(outbuf,0,strLenth*4);
	size_t outLength = strLenth*4;

	if( -1 == iconv(iconvH,pin,&strLenth,&outbuf,&outLength))
	{
		iconv_close(iconvH);
		outbuf = NULL;
		outbuf = NULL;
		pBuff = NULL;
		return "GBKToUTF8 Error";
	}
	gbkStr = string(pBuff);
	iconv_close(iconvH);
	outbuf = NULL;
	pBuff = NULL;
#endif
	return gbkStr.c_str();

}

void HSBase::GetAllLineInfo( unsigned char* buf,unsigned long bufSize,vector<string>* out )
{
	HSAssert(out,"out == NULL");
	string line = "";

	for (unsigned long i=0;i<bufSize;++i)
	{
		unsigned char cByte = buf[i];
		if(cByte == '\n' || cByte == '\r') //'\n'
		{
			int begin = line.find('#');
			if (begin != std::string::npos)
			{
				line = line.substr(0,begin);
			}
			out->push_back(line);
			line = "";
		}else{
			if (cByte != ' ')
				line += cByte;
		}
	}
	int begin = line.find('#');
	if (begin != std::string::npos)
	{
		line = line.substr(0,begin);
	}
	if(line != "")
	{
		out->push_back(line);
	}
}

void HSBase::GetDictionary_Key_V( vector<string>* pAllLineInfo,map<string,string>* out )
{
	HSAssert(pAllLineInfo,"pAllLineInfo == NULL");
	HSAssert(out,"out == NULL");

	for (int i=0;i<(int)pAllLineInfo->size();++i)
	{
		string line = pAllLineInfo->at(i);
		int cutIndex = line.find('=');
		if (cutIndex != -1)
		{
			string key = line.substr(0,cutIndex);
			string v = line.substr(cutIndex + 1,line.length() - 1);
			out->insert(pair<string,string>(key,v));
		}		
	}
}

void HSBase::GetDictionary_Key_V__WithFile( const char* fileName,map<string,string>* out )
{
	string fullFilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
	HSFileData data(fullFilePath.c_str(),"rb");
	if(data.GetSize() <= 0)
		return;
	unsigned char* buf = data.GetBuffer();

	vector<string> lineInfoList;

	HSBase::GetAllLineInfo(buf,data.GetSize(),&lineInfoList);

	HSBase::GetDictionary_Key_V(&lineInfoList,out);
}

void HSBase::SetMaxImageSize( CCSize size )
{
	m_MaxImageSize = size;
}

float HSBase::GetMaxImageW()
{
	return m_MaxImageSize.width;
}

float HSBase::GetMaxImageH()
{
	return m_MaxImageSize.height;
}

cocos2d::CCPoint HSBase::GetTemplateScreenCentre()
{
	return ccp(HSBase::GetMaxImageW() / 2.f,HSBase::GetMaxImageH() / 2.f);
}

float HSBase::GetTemplateScreenW()
{
	return HSBase::GetMaxImageW();
}

float HSBase::GetTemplateScreenH()
{
	return HSBase::GetMaxImageH();
}

cocos2d::CCSize HSBase::GetTemplateScreenSize()
{
	return CCSizeMake(HSBase::GetTemplateScreenW(),HSBase::GetTemplateScreenH());
}

