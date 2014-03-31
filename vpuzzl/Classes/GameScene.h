#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "NoTouchLayer.h"
#include "SimpleAudioEngine.h"
#include "Block.h"

#define NUMBER_AREA_TAG 4
#define NUMBER_AREA_Z_ORDER 4
#define THUMB_SPRITE_Z_ORDER 3
#define PIECE_LAYER_Z_ORDER 2

using namespace cocos2d;


class Game : public cocos2d::CCLayer
{
public:
	cocos2d::CCPoint maskInitPos[6][6];
	 cocos2d::CCSprite* pSprites[6][6];
	 cocos2d::CCSprite* shadowSprites[6][6];
	 cocos2d::CCSprite* maskSprites[6][6];
	 bool isSpritesUsed[6][6];
	float	m_time;
	std::vector<Block*> blocks;
	cocos2d::CCSprite* pSprite_;
	Block* pActiveBlk;
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(); 
	virtual void onExit();
	virtual void menuPauseCallback(CCObject* pSender);
	virtual void menuBackCallback(CCObject* pSender);
	virtual void menuHelpCallback(CCObject* pSender);
	virtual void menuSoundPlayCallback(CCObject* pSender);
	
	virtual void menuMagic1Callback(CCObject* pSender);
	virtual void menuMagic2Callback(CCObject* pSender);
	virtual void menuMagic3Callback(CCObject* pSender);

	
	virtual void menuContinueCallback(CCObject* pSender);
	virtual void menuRestartCallback(CCObject* pSender);
	virtual void menuMainMenuCallback(CCObject* pSender);

	
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	//virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	//virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	static cocos2d::CCPoint GetFirstTouchPosInGL(cocos2d::CCSet* touches);
	static cocos2d::CCPoint GetFirstTouchPrePosInGL(cocos2d::CCSet* touches);
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
	void step(float dt);
    
	NODE_FUNC(Game);
private:
	cocos2d::CCSize winSize;
	NoTouchLayer* pauseLayer;
	cocos2d::CCLayer *piecesLayer;
};
#endif
