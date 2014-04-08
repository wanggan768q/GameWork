#include "HSJni.h"

HSJni::HSJni(void)
{
	
}


HSJni::~HSJni(void)
{
}

bool HSJni::LoadStaticClass(const char* javaClass,const char* C_ReturnType,const char* functionName,const char* parameter,const std::string& buffer)
{
	std::string param = FormatParameter(parameter);
	std::string returnType = FormatReturnType(C_ReturnType);

	param += returnType;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	//CCLog("JavaClassName : %s",javaClass);
	//CCLog("FunctionName : %s",functionName);
	//CCLog("Param : %s",param.c_str());
	bool isOk = JniHelper::getStaticMethodInfo(m_minfo,javaClass,functionName,param.c_str());

	if (!isOk)
	{
		CCLog(param.c_str());
		HSMessageBox("LoadStatic Fail");
		return false;
	}
	if (buffer == "")
	{
		jbyteArray str1 = StringToJByteArray(m_minfo.env,buffer.c_str());
		m_minfo.env->CallStaticObjectMethod(m_minfo.classID,m_minfo.methodID,str1);
	}else{
		jbyteArray str1 = StringToJByteArray(m_minfo.env,buffer.c_str());
		m_minfo.env->CallStaticObjectMethod(m_minfo.classID,m_minfo.methodID,str1);
	}
	
#endif

	return true;
}

const char* HSJni::FormatType( const char* C_type )
{
	if (0 == strcmp(C_type,"void"))
	{
		return "V";
	}else if (0 == strcmp(C_type,"int")){
		return "I";
	}else if(0 == strcmp(C_type,"string")){
		return "Ljava/lang/String;";
	}else if(0 == strcmp(C_type,"bool")){
		return "Z";
	}else if(0 == strcmp(C_type,"byteArray")){
		return "[B";
	}
	HSMessageBox("Illegal type");
	return "";
}

std::string HSJni::FormatReturnType( const char* C_type )
{
	std::string javaType = FormatType(C_type);

	return javaType;
}

std::string HSJni::FormatParameter( const char* C_parameter )
{
	if (!C_parameter)
	{
		return "";
	}
	std::vector<std::string> result = this->Split(C_parameter,"#");
	std::string newParam = "(";
	for (int i=0;i<(int)result.size();++i)
	{
		newParam += FormatType(result[i].c_str());
	}
	newParam += ")";
	return newParam;
}

std::vector<std::string> HSJni::Split( const char* str,const char* format )
{
	std::string temp = str;
	std::string pattern = format;
	std:: string::size_type pos;
	std::vector<std::string> result;
	temp += pattern; 
	int size = (int)temp.size();

	for( int i= 0; i<size; i++)
	{ 
		pos = temp.find(pattern,i);
		if((int)pos < size) 
		{ 
			std:: string s=temp.substr(i,pos-i);
			result.push_back(s);
			i = pos+pattern.size() - 1;
		}
	}
	return result;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
jstring HSJni::StrToJstring( JNIEnv* env, const char* pStr )
{
	jclass strClass = env->FindClass("Ljava/lang/String;");
	jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
	jbyteArray bytes = env->NewByteArray(strlen(pStr));
	env->SetByteArrayRegion(bytes, 0, strlen(pStr), (jbyte*)pStr);
	jstring encoding = env->NewStringUTF("utf-8");
	return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
}

jbyteArray HSJni::StringToJByteArray( JNIEnv* env,const char* buffer )
{
	HSAssert(env,"");
	HSAssert(buffer,"");
	const jbyte* jBuffer = (const jbyte*)buffer;
	jsize bufferSize = (jsize)strlen(buffer);
	jbyteArray jarray = env->NewByteArray(strlen(buffer));
	env->SetByteArrayRegion(jarray, 0, bufferSize, jBuffer);
	return jarray;
}

const char* HSJni::JByteArrayToCharArray( JNIEnv* env,jbyteArray buffer )
{
	HSAssert(env,"");
	HSAssert(buffer,"");
	jbyte* pJavaData = env->GetByteArrayElements(buffer,0);
	jsize  pJavaDataSize = env->GetArrayLength(buffer);
	CCLog("%s -- %d",__FUNCTION__,pJavaDataSize);
	char* pData = (char*)pJavaData;
	return pData;
}

#endif

