#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

#include "cocos2d.h"
#include "cocoa/CCObject.h"
#include "HSThread.h"
#include "MobClickCpp.h"
/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class  AppDelegate : private cocos2d::CCApplication,private cocos2d::CCObject,public HSThread
{

public:
	AppDelegate();
	virtual ~AppDelegate();

	/**
	@brief    Implement CCDirector and CCScene init code here.
	@return true    Initialize success, app continue.
	@return false   Initialize failed, app terminate.
	*/
	virtual bool applicationDidFinishLaunching();

	/**
	@brief  The function be called when the application enter background
	@param  the pointer of the application
	*/
	virtual void applicationDidEnterBackground();

	/**
	@brief  The function be called when the application enter foreground
	@param  the pointer of the application
	*/
	virtual void applicationWillEnterForeground();

	void AddSocket();

	void Updata(float dt);
    
    void Lister_LoadPngFinish(float dt);
    
    virtual void Run();
    
    //void Activate(float dt);

private:
    bool m_isLoadPngFinish;
    std::map<std::string, CCImage*> m_ImageMap;
};

#endif  // __APP_DELEGATE_H__
