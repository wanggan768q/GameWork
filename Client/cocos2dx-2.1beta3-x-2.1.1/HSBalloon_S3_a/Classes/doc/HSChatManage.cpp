#include "HSChatManage.h"

HSChat::HSChat()
{
	
}

HSChat::~HSChat(void)
{
}

HSChat* HSChat::CreateChatManage(CCSize frameSize,const char* fontName,float fontSize,SelectorProtocol *target, SEL_MenuHandler selector)
{
	HSChat* chatMange = new HSChat;
	chatMange->autorelease();
	chatMange->frameSize = frameSize;
	chatMange->fontName = fontName;
	chatMange->fontSize = fontSize;
	chatMange->nameMenu = NULL;
	chatMange->target = target;
	chatMange->selector = selector;

	chatMange->AddInfo("当前","霸气回荡","asd主席12323asd@#$%^&*()换购让她地方地方而",CHAT_INVALID);
	return chatMange;
}

void HSChat::Init()
{

}

void HSChat::AddInfo( string channels, string name, string info,ChatType type )
{

	channels.insert(0,"[");
	channels.insert(channels.length(),"]");
	int unicodeWidth_channels = channels.length();
	channels = HS_GBK_TO_UTF8(channels);	
	CCLabelTTF* ttfChannels = CCLabelTTF::labelWithString(channels.c_str(),CCSizeMake(frameSize.width,
		this->fontSize),CCTextAlignmentLeft,this->fontName,this->fontSize);
	ttfChannels->setAnchorPoint(CCPointZero);
	ttfChannels->setPosition(CCPointZero);
	this->addChild(ttfChannels);
	float channelsWidth = this->GetStringWidth(channels);



	name.insert(0,"[");
	name.insert(name.length(),"]:");
	int unicodeWidth_name = channels.length();
	name = HS_GBK_TO_UTF8(name);
	CCTexture2D* nameTexture = new CCTexture2D();
	nameTexture->initWithString(name.c_str(),CCSizeMake(this->frameSize.width,this->fontSize),CCTextAlignmentLeft,
		this->fontName, this->fontSize);
	CCSprite* nameSprite_A = CCSprite::spriteWithTexture(nameTexture);
	nameSprite_A->setAnchorPoint(CCPointZero);
	nameSprite_A->setPosition(CCPointZero);
	nameSprite_A->setColor(ccc3(0,255,255));

	CCSprite* nameSprite_B = CCSprite::spriteWithTexture(nameTexture);
	nameSprite_B->setAnchorPoint(CCPointZero);
	nameSprite_B->setPosition(CCPointZero);
	nameSprite_B->setScaleY(1.2f);
	nameSprite_B->setColor(ccc3(0,255,0));

	CCMenuItemSprite* menuItemSprite = CCMenuItemSprite::itemFromNormalSprite(nameSprite_A,nameSprite_B,
		this->target,this->selector);
	menuItemSprite->setAnchorPoint(CCPointZero);
	menuItemSprite->setPosition(CCPointZero);
	this->nameMenu = CCMenu::menuWithItems(menuItemSprite, NULL);
	this->nameMenu->setPosition(ccp(channelsWidth,0));
	this->addChild(this->nameMenu);
	nameTexture->release();
	float nameWidth = this->GetStringWidth(name);


	for (int i=0;i<(int)(unicodeWidth_channels + unicodeWidth_name + 3);++i)
	{
		info.insert(0," ");
	}

// 	for (int i=0;i<(int)(channelsWidth + nameWidth + 3);++i)
// 	{
// 		info.insert(0," ");
// 	}
	info = HS_GBK_TO_UTF8(info);
	float infoWidth = this->GetStringWidth(info);
	float width = infoWidth;
	float line = width / frameSize.width;
	float diff = line - (float)((int)line);
	if (diff > 0.f)
	{
		line = (float)((int)line + 1);
	}else{
		line = (float)((int)line);
	}

	for (int i=1;i<(int)line;++i)
	{
		this->SetMoveUpOneLine(ttfChannels);
		this->SetMoveUpOneLine(menuItemSprite);
	}
	CCLabelTTF* ttfInfo = CCLabelTTF::labelWithString(info.c_str(),CCSizeMake(frameSize.width,
		this->fontSize * line),CCTextAlignmentLeft,this->fontName,this->fontSize);
	ttfInfo->setAnchorPoint(CCPointZero);
	ttfInfo->setPosition(CCPointZero);
	this->addChild(ttfInfo);
}

float HSChat::GetStringWidth(string utf8)
{
	float strWidth = 0.f;
	int utflen = utf8.length();
	wstring str;
	str.resize(utflen);
	vector<char> bytes;
	bytes.resize(utflen);
	for (int i=0;i<utflen;++i)
	{
		bytes[i] = utf8[i];
	}

	int ch1;
	int length = 0;
	int index = 0;

	while(length < utflen)
	{
		ch1 = (int) bytes[length] & 0xff;
		switch(ch1 >> 4)
		{
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
			/* 0xxxxxxx*/
			length++;
			strWidth += (this->fontSize / 2);		
			break;
		case 12: case 13:
			/* 110x xxxx   10xx xxxx*/
			length += 2;
			//strWidth += (this->fontSize / 2);
			return 0.f;
			break;
		case 14:
			/* 1110 xxxx  10xx xxxx  10xx xxxx */
			length += 3;
			strWidth += this->fontSize;
			break;
		default:
			/* 10xx xxxx,  1111 xxxx */
			return -1.f;
		}
	}
	return strWidth;
}

void HSChat::SetMoveUpOneLine( CCNode* node )
{
	CCPoint curPos = node->getPosition();
	node->setPosition(ccp(curPos.x,curPos.y + this->fontSize));
}

HSChatManage::HSChatManage(CCNode* node)
{
	this->node = node;
}

HSChatManage::~HSChatManage(void)
{
	list<HSChat*>::iterator alliInfolistIt = this->allInfoList.begin();
	for (;alliInfolistIt!=this->allInfoList.end();++alliInfolistIt)
	{
		this->node->removeChild(*alliInfolistIt,true);
	}
	this->allInfoList.clear();

}

HSChatManage* HSChatManage::CreateChatManage(CCNode* node)
{
	HSChatManage* hsChatManage = new HSChatManage(node);
	return hsChatManage;
}

void HSChatManage::AddChat( HSChat* chat )
{
	if (!this->node)
	{
		HSMessageBox("Please set Target for the chat manager @HSChatManage::AddChat");
		return;
	}
	if (chat)
	{
		this->allInfoList.push_front(chat);
		this->node->addChild(chat);
	}else{
		HSMessageBox("chat is NULL @HSChatManage::AddChat");
	}
}

