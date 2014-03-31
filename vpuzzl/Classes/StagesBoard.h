#ifndef _STAGESBOARD__H_
#define _STAGESBOARD__H_

#include "cocos2d.h"
#include "res.h"
using namespace cocos2d;

class StagesBoard: public cocos2d::CCLayer   
{  
public: 
    CCSprite* stages[10];
	stageInfo stageInfos[10];

    virtual bool init();  
    virtual void onExit();
    NODE_FUNC(StagesBoard);  
    void setRect(float, float, float, float);
	CCRect rect();

	bool containsTouchLocation(cocos2d::CCTouch* touch);
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);  
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);  
    /*virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);*/
private:
	float xori, yori, x, y;
	float dltX;
	CCSprite* selectedStage;
	bool stage_selected;
	CCSprite* item_selected;

	
};

#endif