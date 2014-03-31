#ifndef __PIECES_BOARD_H__
#define __PIECES_BOARD_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "Block.h"

using namespace cocos2d;

class PiecesBoard : public cocos2d::CCLayer{ 
public: 
	bool isBlockSelected;
	bool isActioned;
	bool isBoardSlide;
	Game* pGame;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone 
    virtual bool init();   
     
    // implement the "static node()" method manually 
    NODE_FUNC(PiecesBoard); 
	//static NoTouchLayer::CCLayerColor* node(); 
	void setRect(float, float, float, float);
    CCRect rect();

	bool containsTouchLocation(cocos2d::CCTouch* touch);
    //virtual void registerWithTouchDispatcher(); 
     
    virtual bool ccTouchBegan (cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent); 
    virtual void ccTouchMoved (cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent); 
    virtual void ccTouchEnded (cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled (cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
private:
	float xori, yori, x, y;
	cocos2d::CCSprite* pSprite_;
	Block* pActiveBlk;
	cocos2d::CCSprite* pShadowSprite_;
}; 

#endif