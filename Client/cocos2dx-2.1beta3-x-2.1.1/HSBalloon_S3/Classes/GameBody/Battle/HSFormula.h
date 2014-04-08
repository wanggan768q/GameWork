//
//  HSFormula.h
//  HSBalloon_S3
//
//  Created by Ambition on 13-12-17.
//
//

#ifndef __HSBalloon_S3__HSFormula__
#define __HSBalloon_S3__HSFormula__

#include <iostream>
#include "HSTool.h"
/**
 *  自己等级=a，对方等级=b，x=有属性时1，无属性时0
 */

class HSFormula
{
public:
    
    HSFormula() = delete;
    ~HSFormula() = delete;
    
    
public:
    /**
     *  连线距离
     */
    static float LianXianJuLi();
    
    /**
     *  掉落时间间隔
     */
    static float DiaoLuoShiJianJianGe();
    /**
     *  石化时间
     */
    static float ShiHuaShiJian();
    /**
     *  弹性
     */
    static float TanXiang();
    /**
     *  掉落数量
     */
    static int DiaoLuoShuLiang(float gameTime);
    
    /**
     *  石化球数量
     */
    static int ShiHuaQiuShuLiang(int destroyCount);
    
    
    
private:
    
    /**
     *  连线距离
     */
    static float _LianXianJuLi( int selfLever,const FigureData_FigureProperty& self );
    
    /**
     *  掉落时间间隔
     */
    static float _DiaoLuoShiJianJianGe(int selfLever, const FigureData_FigureProperty& self , int targetLever,const FigureData_FigureProperty& target);
    /**
     *  石化时间
     */
    static float _ShiHuaShiJian(int selfLever, const FigureData_FigureProperty& self , int targetLever,const FigureData_FigureProperty& target);
    /**
     *  弹性
     */
    static float _TanXiang(int selfLever, const FigureData_FigureProperty& self , int targetLever,const FigureData_FigureProperty& target);
    /**
     *  掉落数量
     */
    static int _DiaoLuoShuLiang(float gameTime ,int selfLever, const FigureData_FigureProperty& self , int targetLever,const FigureData_FigureProperty& target);
    
    /**
     *  石化球数量
     */
    static int _ShiHuaQiuShuLiang(int destroyCount,int selfLever, const FigureData_FigureProperty& self , int targetLever,const FigureData_FigureProperty& target);

};
















#endif /* defined(__HSBalloon_S3__HSFormula__) */
