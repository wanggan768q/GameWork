//////////////////////////////////////
//  FileName:    BJMFormatLabel.h
//	Author:	     zx
//  Date:        2012.5.4
//  Description: formatted label
//////////////////////////////////////

#ifndef __BJM_FORMAT_LABEL_H__
#define __BJM_FORMAT_LABEL_H__

#include "CCNode.h"
#include "CCSprite.h"
#include "CCLabelTTF.h"
#include "CCGeometry.h"
using namespace cocos2d;

#include <map>
#include <vector>
using namespace std;

class CBJMFace;
class CXMLWrapperFormatLabel;
class CXMLWrapperLabel;
class CBJMPanel;
class CC_DLL CBJMFormatLabel : public CCNode
{
public:
	typedef map<float, CCSize> MAP_FLOAT_SIZE;

	enum FontType
	{
		FT_Num,
		FT_Ch,
		FT_EnBig,
		FT_EnSmall,
		FT_PuncFull,
		FT_PuncHalf,
	};

	typedef vector<CCNode *> VEC_SEGS;

public:
	CBJMFormatLabel();
	~CBJMFormatLabel();
	void Reset();

	inline float GetWidth() const { return m_fWidth; }
	inline void SetWidth(float val) { m_fWidth = val; }
	void SetWidthAuto(float fWidth);
	
	inline float GetLineHeight() const { return m_fLineHeight; }
	inline void SetLineHeight(float val) { m_fLineHeight = val; }
	void SetLineHeightAuto(float fLineHeight);

	inline float GetLineSpace() const { return m_fLineSpace; }
	inline void SetLineSpace(float val) { m_fLineSpace = val; }
	void SetLineSpaceAuto(float fLineSpace);

	inline cocos2d::ccColor4B GetColor() const { return m_ccColor; }
	inline void SetColor(cocos2d::ccColor4B val) { m_ccColor = val; }

	inline float GetFontSize() const { return m_fFontSize; }
	inline void SetFontSize(float val) { m_fFontSize = val; }

	inline std::string GetFontName() const { return m_strFontName; }
	inline void SetFontName(std::string val) { m_strFontName = val; }

	inline bool GetIsMoveUpper() const { return m_bIsMoveUpper; }
	inline void SetIsMoveUpper(bool val) { m_bIsMoveUpper = val; }

	void CreateFromConfig(CXMLWrapperFormatLabel * pFormatLabelConfig, const string & strStyleFileName, CBJMPanel * pLogicPanel = NULL);
	void CreateFromString(const string & strContent, const string & strFontName, float fFontSize, ccColor4B ccColor);

protected:
	float m_fWidth;
	float m_fLineHeight;	
	float m_fLineSpace;
	ccColor4B m_ccColor;	
	float m_fFontSize;	
	string m_strFontName;

	CCPoint m_ptStartPos;
	CCPoint m_ptEndPos;	

	float m_fCurRight;
	float m_nCurLine;

	bool m_bIsMoveUpper;
	int m_nLineCount;

	void AddLabel(CXMLWrapperLabel * pLabelConfig, const string & strStyleFileName, CBJMPanel * pLogicPanel = NULL);
	void AddFace(CXMLWrapperLabel * pLabelConfig);
	void AddFace(const string & strFaceCode);
	bool CheckNeedChangeLine(const CCSize & sizeItem);
	void MoveLine();
	void CreateSubLabel(int & nStartIndex, int nEndIndex, const wstring & wstrUnicodeLabel, const string & strFontName, float fFontSize, const ccColor4B & ccColor, const string & strLink, CBJMPanel * pLogicPanel = NULL);

	VEC_SEGS m_vecSegs;
	
protected:	
	static string s_strFaceCodeHead;
	static string s_strFaceCodeReg;

public:
	static inline std::string GetFaceCodeHead() { return s_strFaceCodeHead; }
	static inline void SetFaceCodeHead(std::string val) { s_strFaceCodeHead = val; }
	static std::string GetFaceCodeReg() { return s_strFaceCodeReg; }
	static void SetFaceCodeReg(std::string val) { s_strFaceCodeReg = val; }
	void LagLoad(const string & strStyleFileName);

private:
	void ReleaseConfig(CXMLWrapperFormatLabel *& pFormatLabelConfig);
	void StartNewLine();
};

#endif