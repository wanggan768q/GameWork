//
//  HSSocketSendData.h
//  HSBalloon_S3
//
//  Created by Ambition on 13-10-30.
//
//

#ifndef __HSBalloon_S3__HSSocketSendData__
#define __HSBalloon_S3__HSSocketSendData__

#include "HSBase.h"



class HSSocketSendData
{
public:
    HSSocketSendData();
    ~HSSocketSendData();
    
private:
    std::string m_data;
    int m_id;
    std::string m_describe;
public:
    static HSSocketSendData* New(const std::string& data,int id,const std::string& describe);
    
    bool init(const std::string& data,int id,const std::string& describe);
    
    const std::string& GetData();
    
    const int& GetID();
    
    const char* GetDescribe();
    
};

#endif /* defined(__HSBalloon_S3__HSSocketSendData__) */
