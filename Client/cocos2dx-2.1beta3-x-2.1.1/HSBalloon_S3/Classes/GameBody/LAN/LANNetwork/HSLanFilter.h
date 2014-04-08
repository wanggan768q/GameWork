//
//  HSLanFilter.h
//  HSBalloon_S3
//
//  Created by Ambition on 13-12-12.
//
//

#ifndef __HSBalloon_S3__HSLanFilter__
#define __HSBalloon_S3__HSLanFilter__

#include <iostream>
#include "HSFilter.h"

class HSLanFilter : public HSFilter
{
public:
    HSLanFilter(void);
	~HSLanFilter(void);
    
protected:
    map<string,int> m_lanProtocol;
    
private:
    
    void RegistermLanProtocol();
    
    ::google::protobuf::Message* CreaterLanMessage(int ID);
    
    
public:
    static HSLanFilter* SharedLanFilter();
    
    virtual bool CreaterMessage(google::protobuf::Message* msg);
    
	virtual void CreaterMessage(char* data,int lenth);
    
    
    
};

#endif /* defined(__HSBalloon_S3__HSLanFilter__) */
