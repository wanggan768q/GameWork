//////////////////////////////////////
//  FileName:    BJMFormatLabel.cpp
//	Author:	     zx
//  Date:        2012.5.4
//  Description: formatted label
//////////////////////////////////////

#include "BJMFormatLabel.h"
#include "BJMFace.h"
#include "XMLWrapperFormatLabel.h"
#include "XMLWrapperLabel.h"
#include "StringUtil.h"
#include "BJMImgFace.h"
#include "CCPointExtension.h"
#include "BJMRegexHelpler.h"
#include "BJMConfig.h"
#include "BJMXMLManager.h"
#include "CCImage.h"
#include "BJMBtn.h"
#include "BJMPanel.h"
#include "BJMLabelTTF.h"

string CBJMFormatLabel::s_strFaceCodeHead = "!";
string CBJMFormatLabel::s_strFaceCodeReg = "![0-3][0-9]";

CBJMFormatLabel::CBJMFormatLabel()
	:CCNode()
{
	Reset();
}

void CBJMFormatLabel::Reset()
{
	removeAllChildrenWithCleanup(true);
	m_fWidth = 0.0f;
	m_fLineHeight = BJMConfig::LINE_HEIGHT_DEFAULT;
	m_fLineSpace = BJMConfig::LINE_SPACE_DEFAULT;

	if (CCDirector::sharedDirector()->isRetinaDisplay())
	{
		m_fLineSpace *= 0.5;
		m_fLineHeight *= 0.5;
	}

	m_fCurRight = 0.0f;
	m_nCurLine = 0;
	m_ptStartPos = CCPointZero;
	m_ptEndPos = CCPointZero;

	m_ccColor = BJMConfig::FONTCOLOR_DEFAULT;
	m_fFontSize = BJMConfig::FONTSIZE_DEFAULT;
	m_strFontName = BJMConfig::FONT_DEFAULT;

	m_bIsMoveUpper = false;

	m_nLineCount = 0;
}

CBJMFormatLabel::~CBJMFormatLabel()
{

}

void CBJMFormatLabel::CreateFromConfig(CXMLWrapperFormatLabel * pFormatLabelConfig, const string & strStyleFileName, CBJMPanel * pLogicPanel /*= NULL*/)
{
	if (!pFormatLabelConfig) return;

	CXMLWrapperFormatLabel * pFormatLabelConfigNew = NULL;
	if (!pFormatLabelConfig->m_Style.empty())
	{
		pFormatLabelConfigNew = pFormatLabelConfig;
		pFormatLabelConfig = (CXMLWrapperFormatLabel *)CBJMXMLManager::Instance()->GetStyleConfigByName(pFormatLabelConfig->m_Style, strStyleFileName);
		if (!pFormatLabelConfig)
		{
			pFormatLabelConfig = pFormatLabelConfigNew;
		}
	}

	m_fWidth = pFormatLabelConfig->m_Width;
	if (pFormatLabelConfigNew && pFormatLabelConfigNew->m_flag_Width)
	{
		m_fWidth = pFormatLabelConfigNew->m_Width;
	}

	m_fLineSpace = pFormatLabelConfig->m_LineSpace;
	if (pFormatLabelConfigNew && pFormatLabelConfigNew->m_flag_LineSpace)
	{
		m_fLineSpace = pFormatLabelConfigNew->m_LineSpace;
	}

	m_fLineHeight = pFormatLabelConfig->m_LineHeight;
	if (pFormatLabelConfigNew && pFormatLabelConfigNew->m_flag_LineHeight)
	{
		m_fLineHeight = pFormatLabelConfigNew->m_LineHeight;
	}

	//if (CCDirector::sharedDirector()->isRetinaDisplay())
	//{
	//	m_fLineSpace *= 0.5;
	//	m_fLineHeight *= 0.5;
	//	m_fWidth *= 0.5;
	//}	

	if (pFormatLabelConfigNew && pFormatLabelConfigNew->m_flag_FontColor)
	{
		m_ccColor = pFormatLabelConfigNew->m_FontColor;
	}
	else
	{
		m_ccColor = pFormatLabelConfig->m_FontColor;
	}

	if (pFormatLabelConfigNew && pFormatLabelConfigNew->m_flag_FontSize)
	{
		m_fFontSize = pFormatLabelConfigNew->m_FontSize;
	}
	else
	{
		m_fFontSize = pFormatLabelConfig->m_FontSize;
	}
	
	if (pFormatLabelConfigNew && pFormatLabelConfigNew->m_flag_Font)
	{
		m_strFontName = pFormatLabelConfigNew->m_Font;
	}	
	else
	{
		m_strFontName = pFormatLabelConfig->m_Font;
	}

	if (m_fWidth <= 0 || m_fLineHeight <= 0) return;

	int nSegsCount = pFormatLabelConfig->m_Segs.size();
	for (int i = 0; i < nSegsCount; i++)
	{
		CXMLWrapperLabel * pLabelConfig = pFormatLabelConfig->m_Segs[i];
		if (!pLabelConfig) continue;

		if (!pLabelConfig->m_IsVisible)
		{
			continue;
		}
		
		if (pLabelConfig->m_flag_Img)
		{
			AddFace(pLabelConfig);
		}
		else
		{
			AddLabel(pLabelConfig, strStyleFileName, pLogicPanel);
		}
	}

	float fHeight = (m_nLineCount + 1) * (m_fLineHeight + m_fLineSpace);
	float fWidth = m_fWidth;
	if (m_nLineCount == 0)
	{
		fWidth = m_fCurRight;
	}
	setContentSize(CCSizeMake(fWidth, fHeight));
}

void CBJMFormatLabel::StartNewLine()
{
	m_nLineCount++;
	m_fCurRight = 0.0f;
	m_ptStartPos = CCPointZero;
	if (m_bIsMoveUpper)
	{
		MoveLine();
	}
	else
	{		
		m_ptStartPos.y = - ((m_nLineCount + 1) * (m_fLineHeight + m_fLineSpace));
	}
	m_ptEndPos = m_ptStartPos;
}

void CBJMFormatLabel::AddLabel(CXMLWrapperLabel * pLabelConfig, const string & strStyleFileName, CBJMPanel * pLogicPanel /*= NULL*/)
{
	if (!pLabelConfig) return;

	CXMLWrapperLabel * pLabelConfigNew = NULL;

	if (!pLabelConfig->m_Style.empty())
	{
		pLabelConfigNew = pLabelConfig;
		pLabelConfig = (CXMLWrapperLabel *)CBJMXMLManager::Instance()->GetStyleConfigByName(pLabelConfig->m_Style, strStyleFileName);
		if (!pLabelConfig)
		{
			pLabelConfig = pLabelConfigNew;
		}
	}
	
	string strLabel;
	if (pLabelConfigNew && pLabelConfigNew->m_flag_Text)
	{
		strLabel = pLabelConfigNew->m_Text;
	}
	else
	{
		strLabel = pLabelConfig->m_Text;
	}
	
	const wstring & wstrUnicodeLabel = StringUtil::Utf8StringToUnicodeString(strLabel);
	
	ccColor4B ccColor = m_ccColor;
	if (pLabelConfigNew && pLabelConfigNew->m_flag_FontColor)
	{
		ccColor = pLabelConfigNew->m_FontColor;
	}
	else
	{
		if (pLabelConfig->m_flag_FontColor)
		{
			ccColor = pLabelConfig->m_FontColor;
		}
	}
	float fFontSize = m_fFontSize;
	if (pLabelConfigNew && pLabelConfigNew->m_flag_FontSize)
	{
		fFontSize = pLabelConfigNew->m_FontSize;
	}
	else
	{
		if (pLabelConfig->m_flag_FontSize)
		{
			fFontSize = pLabelConfig->m_FontSize;
		}		
	}
	string strFontName = m_strFontName;
	if (pLabelConfigNew && pLabelConfigNew->m_flag_Font)
	{
		strFontName = pLabelConfigNew->m_Font;
	}
	else
	{
		if (pLabelConfig->m_flag_Font)
		{
			strFontName = pLabelConfig->m_Font;
		}
	}
	bool bNewLine = false;
	if (pLabelConfigNew && pLabelConfigNew->m_flag_NewLine)
	{
		bNewLine = pLabelConfigNew->m_NewLine;
	}
	else
	{
		if (pLabelConfig->m_flag_NewLine)
		{
			bNewLine = pLabelConfig->m_NewLine;
		}		
	}

	string strLink = "";
	if (pLabelConfigNew && pLabelConfigNew->m_flag_Link)
	{
		strLink = pLabelConfigNew->m_Link;
	}
	else
	{
		if (pLabelConfig->m_flag_Link)
		{
			strLink = pLabelConfig->m_Link;
		}
	}

	if (bNewLine)
	{
		StartNewLine();
	}

	CCImage::SetFont(strFontName, fFontSize);

	string strSeg;
	int nCharactersCount = wstrUnicodeLabel.length();
	int nStartIndex = 0;
	int nEndIndex = 0;
	for (int i = 0; i < nCharactersCount; i++)
	{
		wchar_t wCh = wstrUnicodeLabel.at(i);

		bool bNeedBreakByTag = false;
		if (wCh == L'\\')
		{
			// check if is \n
			if (i != nCharactersCount - 1)
			{
				wchar_t wChNext = wstrUnicodeLabel.at(i + 1);
				if (wChNext == L'n')
				{
					bNeedBreakByTag = true;
				}
			}			
		}
		
		string strCode;
		bool bNeedSetImg = false;
		if (wCh == L'!' && i + 2 < nCharactersCount)
		{
			// check if is a valid face name
			const wstring & wstrCode = wstrUnicodeLabel.substr(i, 3);
			strCode = StringUtil::UnicodeStringToUtf8String(wstrCode);
			bool bValid = CBJMImgFace::CheckFaceCode(strCode);
			if (bValid)
			{
				bNeedSetImg = true;
			}
		}

		FontType enmFontType = FT_EnSmall;
		CCSize sizeCharacters = CCSizeZero;
		int nEnd = 0;
		if (!bNeedBreakByTag & !bNeedSetImg)
		{
			nEnd = nEndIndex - nStartIndex + 1;
		}
		else if (bNeedSetImg)
		{
			nEnd = nEndIndex - nStartIndex;	
		}

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		sizeCharacters = CCImage::CalStringWidth(wstrUnicodeLabel.substr(nStartIndex, nEnd));
#else
		const wstring & wstrSubStr = wstrUnicodeLabel.substr(nStartIndex, nEnd);
		const string & strUtf8Str = StringUtil::UnicodeStringToUtf8String(wstrSubStr);
		sizeCharacters = CCImage::CalStringWidth(strUtf8Str);
#endif	

		bool bNeedChangeLine = CheckNeedChangeLine(sizeCharacters);

		if (bNeedBreakByTag || bNeedChangeLine && !bNeedSetImg)
		{
			// need change line
			if (bNeedBreakByTag)
			{
				m_ptEndPos = CCPointZero;
				m_fCurRight = 0.0f;
			}
			else
			{
				// set cur right as the right side of the first character of the second line
				CCSize sizeLastCharacter = CCSizeZero;
				const wstring & wstrSubStr = wstrUnicodeLabel.substr(nEndIndex, 1);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
				sizeLastCharacter = CCImage::CalStringWidth(wstrSubStr);
#else
				const string & strUtf8Str = StringUtil::UnicodeStringToUtf8String(wstrSubStr);
				sizeLastCharacter = CCImage::CalStringWidth(strUtf8Str);
#endif				
				m_ptEndPos.x = sizeLastCharacter.width;
			}
			
			CreateSubLabel(nStartIndex, nEndIndex - 1, wstrUnicodeLabel, strFontName, fFontSize, ccColor, strLink, pLogicPanel);
			if (m_bIsMoveUpper)
			{
				MoveLine();
			}		
			else
			{
				m_ptStartPos = CCPointZero;
			}
			nStartIndex = nEndIndex;
			m_ptStartPos = CCPointZero;
			m_nLineCount++;
		}
		else if (bNeedSetImg)
		{
			CreateSubLabel(nStartIndex, nEndIndex - 1, wstrUnicodeLabel, strFontName, fFontSize, ccColor, strLink, pLogicPanel);
			nStartIndex = nEndIndex;
		}

		if (bNeedBreakByTag)
		{
			nStartIndex += 2;
			nEndIndex = nStartIndex;
			i = nStartIndex - 1;
		}
		else if (bNeedSetImg)
		{
			nStartIndex += 3;
			nEndIndex = nStartIndex;
			i = nStartIndex - 1;
			m_ptStartPos = m_ptEndPos;
			AddFace(strCode);
		}
		else
		{
			nEndIndex ++;
		}
	}

	CreateSubLabel(nStartIndex, nEndIndex - 1, wstrUnicodeLabel, strFontName, fFontSize, ccColor, strLink, pLogicPanel);
	m_ptStartPos = m_ptEndPos;
}

void CBJMFormatLabel::CreateSubLabel(int & nStartIndex, int nEndIndex, const wstring & wstrUnicodeLabel, const string & strFontName, float fFontSize, const ccColor4B & ccColor, const string & strLink, CBJMPanel * pLogicPanel /*= NULL*/)
{
	if (nStartIndex > nEndIndex) return;
	// create label
	CBJMLabelTTF * pLastSeg = new CBJMLabelTTF;
	const wstring & strSubLabel = wstrUnicodeLabel.substr(nStartIndex, nEndIndex - nStartIndex + 1);
	string strLastSeg = StringUtil::UnicodeStringToUtf8String(strSubLabel);
	pLastSeg->initWithString(strLastSeg.c_str(), strFontName.c_str(), fFontSize);
	pLastSeg->setColor(ccc3(ccColor.r, ccColor.g, ccColor.b));
	pLastSeg->autorelease();

	pLastSeg->setAnchorPoint(CCPointZero);
	
	if (!m_bIsMoveUpper)
	{
		m_ptStartPos.y = - ((m_nLineCount + 1) * (m_fLineHeight + m_fLineSpace));
	}

	pLastSeg->setPosition(m_ptStartPos);

	CBJMBtn * pLinkBtn = NULL;
	if (!strLink.empty())
	{
		CBJMColorAndBorder * pColorAndBorder = pLastSeg->GetColorAndBorder();

		if (pColorAndBorder)
		{
			pColorAndBorder->SetColorBorder(ccc4(ccColor.r,ccColor.g,ccColor.b,255));
			//pColorAndBorder->SetColorBorder(ccc4(255,0,0,255));
			pColorAndBorder->SetBorderWidth(2);

			// set draw border
			pColorAndBorder->SetDrawBorder(0, 0, 1, 0);
		}

		// create link
		pLinkBtn = new CBJMBtn("", "", "", false);
		pLinkBtn->autorelease();
		pLinkBtn->SetRectFocus(CCRectMake(0, 0, pLastSeg->getContentSize().width, pLastSeg->getContentSize().height));
		pLinkBtn->setPosition(CCPointZero);
		pLinkBtn->SetName(BJMConfig::LINK_PRE + strLink);
		pLinkBtn->SetIsLink(true);
		pLinkBtn->SetLogicPanel(pLogicPanel);
	}

	m_ptStartPos = m_ptEndPos;
	m_vecSegs.push_back(pLastSeg);
	addChild(pLastSeg);

	if (pLinkBtn)
	{
		pLastSeg->addChild(pLinkBtn);
		if (pLogicPanel)
		{
			pLogicPanel->AddGroupAndBtns(BJMConfig::LINK_PRE, pLinkBtn);
		}
	}
}

void CBJMFormatLabel::MoveLine()
{
	int nSegsCount = m_vecSegs.size();
	for (int i = 0; i < nSegsCount; i++)
	{
		CCNode * pSeg = m_vecSegs[i];
		if (!pSeg) continue;
		CCPoint ptPos = pSeg->getPosition();
		ptPos.y += m_fLineHeight + m_fLineSpace;
		pSeg->setPosition(ptPos);
	}
}

bool CBJMFormatLabel::CheckNeedChangeLine(const CCSize & sizeCharacters)
{
	bool bNeedChangeLine = false;
	float fRightToBe = sizeCharacters.width + m_ptStartPos.x;
	float fY = 0;
	if (!m_bIsMoveUpper)
	{
		fY = -(m_nLineCount + 1) * (m_fLineHeight + m_fLineSpace);
	}
	if (fRightToBe > m_fWidth)
	{
		// need change line
		bNeedChangeLine = true;
		m_fCurRight = 0;
		m_ptEndPos = CCPointMake(m_fCurRight, fY);
	}
	else
	{
		// not need change line
		m_ptEndPos = CCPointMake(fRightToBe, fY);
		m_fCurRight = fRightToBe;
	}

	return bNeedChangeLine;
}

void CBJMFormatLabel::AddFace(const string & strFaceCode)
{
	CBJMImgFace * pImgFace = new CBJMImgFace(strFaceCode);
	pImgFace->autorelease();

	const CCSize & sizeImg = CBJMImgFace::GetSizeFace();
	bool bNeedChangeLine = CheckNeedChangeLine(sizeImg);
	if (bNeedChangeLine)
	{
		m_nLineCount++;
		if (m_bIsMoveUpper)
		{
			m_ptStartPos = CCPointZero;
			MoveLine();		
		}
		else
		{
			
			m_ptStartPos.x = 0;
		}
	}

	m_ptStartPos.y = -(m_nLineCount + 1) * (m_fLineHeight + m_fLineSpace);

	pImgFace->setPosition(m_ptStartPos);
	addChild(pImgFace);
	m_vecSegs.push_back(pImgFace);

	m_ptStartPos.x += sizeImg.width;
}

void CBJMFormatLabel::AddFace(CXMLWrapperLabel * pLabelConfig)
{
	if (!pLabelConfig) return;

	AddFace(pLabelConfig->m_Img);
}

void CBJMFormatLabel::CreateFromString(const string & strContent, const string & strFontName /*=*/, float fFontSize /*=*/, ccColor4B ccColor /*=*/)
{
	CBJMRegexHelpler::VEC_REGEX_RESULT vecRegexResults;
	CBJMRegexHelpler::MatchStringResults(strContent, s_strFaceCodeReg, vecRegexResults);
	int nRegexResultsCount = vecRegexResults.size();
	CXMLWrapperFormatLabel * pFormatLabelConfig = new CXMLWrapperFormatLabel;

	pFormatLabelConfig->Set_Width(m_fWidth);
	pFormatLabelConfig->Set_LineHeight(m_fLineHeight);
	pFormatLabelConfig->Set_LineSpace(m_fLineSpace);
	pFormatLabelConfig->Set_Font(m_strFontName);
	pFormatLabelConfig->Set_FontColor(m_ccColor);
	pFormatLabelConfig->Set_FontSize(m_fFontSize);
	int nCurStart = 0;
	for (int i = 0; i < nRegexResultsCount; i++)
	{
		const CBJMRegexHelpler::RegexResult & RegexResult = vecRegexResults[i];
		CXMLWrapperLabel * pLabelConfig = new CXMLWrapperLabel;
		if (nCurStart != RegexResult.nStartIndex)
		{
			pLabelConfig->Set_Font(strFontName.c_str());
			pLabelConfig->Set_FontColor(ccColor);
			pLabelConfig->Set_FontSize(fFontSize);
			const string & strText = strContent.substr(nCurStart, RegexResult.nStartIndex - nCurStart);
			pLabelConfig->Set_Text(strText);
			pFormatLabelConfig->Set_Segs(pLabelConfig);
		}
		pLabelConfig = new CXMLWrapperLabel;
		const string & strImg = strContent.substr(RegexResult.nStartIndex, RegexResult.nEndIndex - RegexResult.nStartIndex);
		pLabelConfig->Set_Img(strImg);
		pFormatLabelConfig->Set_Segs(pLabelConfig);
		nCurStart = RegexResult.nEndIndex;
	}
	if (nCurStart < strContent.length())
	{
		CXMLWrapperLabel * pLabelConfig = new CXMLWrapperLabel;
		pLabelConfig->Set_Font(strFontName.c_str());
		pLabelConfig->Set_FontColor(ccColor);
		pLabelConfig->Set_FontSize(fFontSize);
		const string & strText = strContent.substr(nCurStart, strContent.length() - nCurStart);
		pLabelConfig->Set_Text(strText);
		pFormatLabelConfig->Set_Segs(pLabelConfig);
	}

	CreateFromConfig(pFormatLabelConfig, "");

	ReleaseConfig(pFormatLabelConfig);
}

void CBJMFormatLabel::ReleaseConfig(CXMLWrapperFormatLabel *& pFormatLabelConfig)
{
	if (pFormatLabelConfig)
	{
		delete pFormatLabelConfig; pFormatLabelConfig = NULL;
	}	
}

void CBJMFormatLabel::LagLoad(const string & strStyleFileName)
{
	CXMLWrapperFormatLabel * pFormatLabelConfig = (CXMLWrapperFormatLabel *)GetConfig();
	if (pFormatLabelConfig)
	{
		CreateFromConfig(pFormatLabelConfig, strStyleFileName);
	}
}

void CBJMFormatLabel::SetLineHeightAuto(float fLineHeight)
{
	if (CCDirector::sharedDirector()->isRetinaDisplay())
	{
		m_fLineHeight =  fLineHeight * 0.5;
	}
	else
	{
		m_fLineHeight = fLineHeight;
	}
}

void CBJMFormatLabel::SetLineSpaceAuto(float fLineSpace)
{
	if (CCDirector::sharedDirector()->isRetinaDisplay())
	{
		m_fLineSpace =  fLineSpace * 0.5;
	}
	else
	{
		m_fLineSpace = fLineSpace;
	}
}

void CBJMFormatLabel::SetWidthAuto(float fWidth)
{
	if (CCDirector::sharedDirector()->isRetinaDisplay())
	{
		m_fWidth =  fWidth * 0.5;
	}
	else
	{
		m_fWidth = fWidth;
	}
}