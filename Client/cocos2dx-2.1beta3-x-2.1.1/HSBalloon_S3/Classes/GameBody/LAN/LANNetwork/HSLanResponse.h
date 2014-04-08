//
//  HSLanResponse.h
//  HSBalloon_S3
//
//  Created by Ambition on 13-12-12.
//
//

#ifndef __HSBalloon_S3__HSLanResponse__
#define __HSBalloon_S3__HSLanResponse__
#include "HSResponse.h"

class HSLanResponse : public HSResponse
{
public:
    HSLanResponse(){}
    ~HSLanResponse(){}
    
public:
	static HSLanResponse* ShareLanResponse();
    
	virtual void HandleFactory(int commandId,google::protobuf::Message* responseMsg);
    
};

#endif /* defined(__HSBalloon_S3__HSLanResponse__) */
