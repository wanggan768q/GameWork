//
//  HSFormula.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 13-12-17.
//
//

#include "HSFormula.h"



/**
 *  连线距离
 */
float HSFormula::LianXianJuLi()
{
    FigureData_FigureProperty sp = *HS_GAME_CACHE()->GetFigureProperty(HS_TARGET_SELF().figureid());
    int sl = HS_TARGET_SELF().figurelevel();
    return HSFormula::_LianXianJuLi(sl,sp);
}

/**
 *  掉落时间间隔
 */
float HSFormula::DiaoLuoShiJianJianGe()
{
    FigureData_FigureProperty sp = *HS_GAME_CACHE()->GetFigureProperty(HS_TARGET_SELF().figureid());
    int sl = HS_TARGET_SELF().figurelevel();
    
    FigureData_FigureProperty tp = *HS_GAME_CACHE()->GetFigureProperty(HS_TARGET_TARGET().figureid());
    int tl = HS_TARGET_SELF().figurelevel();
    
    return HSFormula::_DiaoLuoShiJianJianGe(sl,sp,tl,tp);
}

/**
 *  石化时间
 */
float HSFormula::ShiHuaShiJian()
{
    FigureData_FigureProperty sp = *HS_GAME_CACHE()->GetFigureProperty(HS_TARGET_SELF().figureid());
    int sl = HS_TARGET_SELF().figurelevel();
    
    FigureData_FigureProperty tp = *HS_GAME_CACHE()->GetFigureProperty(HS_TARGET_TARGET().figureid());
    int tl = HS_TARGET_SELF().figurelevel();
    
    return HSFormula::_ShiHuaShiJian(sl,sp,tl,tp);
}
/**
 *  弹性
 */
float HSFormula::TanXiang()
{
    FigureData_FigureProperty sp = *HS_GAME_CACHE()->GetFigureProperty(HS_TARGET_SELF().figureid());
    int sl = HS_TARGET_SELF().figurelevel();
    
    FigureData_FigureProperty tp = *HS_GAME_CACHE()->GetFigureProperty(HS_TARGET_TARGET().figureid());
    int tl = HS_TARGET_SELF().figurelevel();
    
    return HSFormula::_TanXiang(sl,sp,tl,tp);
}
/**
 *  掉落数量
 */
int HSFormula::DiaoLuoShuLiang(float gameTime)
{
    FigureData_FigureProperty sp = *HS_GAME_CACHE()->GetFigureProperty(HS_TARGET_SELF().figureid());
    int sl = HS_TARGET_SELF().figurelevel();
    
    FigureData_FigureProperty tp = *HS_GAME_CACHE()->GetFigureProperty(HS_TARGET_TARGET().figureid());
    int tl = HS_TARGET_SELF().figurelevel();
    
    return HSFormula::_DiaoLuoShuLiang(gameTime,sl,sp,tl,tp);
}

/**
 *  石化球数量
 */
int HSFormula::ShiHuaQiuShuLiang(int destroyCount)
{
    FigureData_FigureProperty sp = *HS_GAME_CACHE()->GetFigureProperty(HS_TARGET_SELF().figureid());
    int sl = HS_TARGET_SELF().figurelevel();
    
    FigureData_FigureProperty tp = *HS_GAME_CACHE()->GetFigureProperty(HS_TARGET_TARGET().figureid());
    int tl = HS_TARGET_SELF().figurelevel();
    
    return HSFormula::_ShiHuaQiuShuLiang(destroyCount,sl,sp,tl,tp);
}






#pragma mark -
#pragma mark -
#pragma mark -
#pragma mark -

#pragma mark - 连线距离 ( 150 + 5 * a * x )

float HSFormula::_LianXianJuLi(int selfLever, const FigureData_FigureProperty& self)
{
    float r = 0.f;
    float a = (float)selfLever;
    float x = self.x_lian_xian_ju_li();
    
    r = 150.0 + 5.0 * a * x;
    
    HSAssert(r > 0, __FUNCTION__);
    
    return r;
}

#pragma mark - 掉落时间间隔 ( 3+(0.1*a*0.5*（1-x)*x）+（0.2*a*0.5*（1+x）*x）+(-0.1*b*y) )

float HSFormula::_DiaoLuoShiJianJianGe(int selfLever, const FigureData_FigureProperty& self , int targetLever,const FigureData_FigureProperty& target)
{
    float r = 0.f;
    float a = (float)selfLever;
    float b = (float)selfLever;
    float x = self.x_diao_luo_shi_jian_jian_ge();
    float y = target.y_diao_luo_shi_jian_jian_ge();
    
    r = 3.0 + (0.1 * a * 0.5 * (1.0 - x) * x) + (0.2 * a * 0.5 * (1.0 + x) * x) + (-0.1 * b * y);
    
    HSAssert(r > 0, __FUNCTION__);
    
    return r;
}

#pragma mark - 石化时间 ( 7+（0.3*a*x）+（-0.3*b*y） )

float HSFormula::_ShiHuaShiJian(int selfLever, const FigureData_FigureProperty& self , int targetLever,const FigureData_FigureProperty& target)
{
    float r = 0.f;
    float a = (float)selfLever;
    float b = (float)selfLever;
    float x = self.x_shi_hua_shi_jian();
    float y = target.y_shi_hua_shi_jian();
    
    r = 7.0 + (0.3 * a * x) + (-0.3 * b * y);
    
    HSAssert(r > 0, __FUNCTION__);
    
    return r;
}

#pragma mark - 弹性 ( 0.2+（-0.01*a*x）+（0.01*b*y） )

float HSFormula::_TanXiang(int selfLever, const FigureData_FigureProperty& self , int targetLever,const FigureData_FigureProperty& target)
{
    float r = 0.f;
    float a = (float)selfLever;
    float b = (float)selfLever;
    float x = self.x_tan_xing();
    float y = target.y_tan_xing();
    
    r = 0.2 + (-0.01 * a * x) + (0.01 * b * y);
    
    HSAssert(r > 0, __FUNCTION__);
    
    return r;
}

#pragma mark - 掉落数量 ( Round（1.75f+m_gameTime / 60.f)+(0.3*a*0.5*（1-x）*x)+(0.3*a*0.5*（1+x）*x)+（0.3*b*y） )

int HSFormula::_DiaoLuoShuLiang(float gameTime ,int selfLever, const FigureData_FigureProperty& self , int targetLever,const FigureData_FigureProperty& target)
{
    float r = 0;
    float a = (float)selfLever;
    float b = (float)selfLever;
    float x = self.x_diao_luo_shu_liang();
    float y = target.y_diao_luo_shu_liang();
    
    r = HSMath::Round( 1.75 + gameTime / 60.0) + (0.3 * a * 0.5 * (1.0 - x) * x) + (0.3 * a * 0.5 * (1.0 + x) * x) + (0.3 * b * y);
    
    HSAssert(r > 0, __FUNCTION__);
    
    return (int)r;
}

#pragma mark - 石化球数量 ( 消除数-4+（-0.2*a*x）+（0.2*b*y） )

int HSFormula::_ShiHuaQiuShuLiang(int destroyCount,int selfLever, const FigureData_FigureProperty& self , int targetLever,const FigureData_FigureProperty& target)
{
    float r = 0.f;
    float a = (float)selfLever;
    float b = (float)selfLever;
    float x = self.x_diao_luo_shu_liang();
    float y = target.y_diao_luo_shu_liang();

    r = (float)destroyCount - 4.0 + (-0.2 * a * x) + (0.2 * b * y);
    
    HSAssert(r > 0, __FUNCTION__);
    
    return (int)r;
}



