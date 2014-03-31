#include "StagesBoard.h"
#include "res.h"
#include "GameScene.h"

using namespace cocos2d;
int stageIndex;
bool StagesBoard::init()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	selectedStage = CCSprite::spriteWithFile(stage_sel);
	stage_selected = false;
	item_selected = NULL;
	selectedStage->setVisible(stage_selected);
	this->addChild(selectedStage, 9);
	dltX = 0;
	return true;
}

bool StagesBoard::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if ( !containsTouchLocation(touch) ) return false;
	CCPoint current_point = getPosition();
	
	//
	CCNode* child;
	CCArray * pArray = getChildren();
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(pArray, pObject)
	{
		if(pObject == NULL)
			break;
		//child->getUserData();
		child = (CCNode*)pObject;
		if(child->getUserData() == NULL)
			continue;
		CCSize node_size = child->getContentSize();

		CCPoint dstPoint = child->getPosition();
		if(CCRect::CCRectContainsPoint(CCRectMake(dstPoint.x - node_size.width/2, dstPoint.y - node_size.height/2, node_size.width, node_size.height), convertTouchToNodeSpaceAR(touch)))
		{
			selectedStage->setPosition(dstPoint);
			stage_selected = true;
			item_selected = (CCSprite*)child;
			stageInfo* tmp = (stageInfo*)(item_selected->getUserData());
			selectedStage->setVisible(stage_selected);
			break;
		}
	}
	
	////CCLog("touched: %f,%f", current_point.x, current_point.y);
	return true;
}

void StagesBoard::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	
	if(stage_selected)
	{
		//CCLog("choose the stage.");
		stage_selected = false;
		selectedStage->setVisible(stage_selected);
		//item_selected with action
		stageInfo* tmp = (stageInfo*)(item_selected->getUserData());
		if(tmp->isLocked)//locked
		{
			item_selected->setScale(0.8f);
			CCActionInterval* actionTo = CCScaleTo::actionWithDuration( 0.6, 1.0f);
			CCActionInterval* move_ease_out = CCEaseElasticOut::actionWithAction(actionTo);
			item_selected->runAction(move_ease_out);
			return;
		}else//unlocked
		{
			
			
			
			stageIndex = tmp->stageIndex;
			CCScene *pScene = Game::scene();
			CCScene *tmpScene = CCTransitionFade::transitionWithDuration(1.2f, pScene);
			
			CCDirector::sharedDirector()->replaceScene(tmpScene);
		}
		return;
	}

	float leftP = -824;
	float rightP = -2100;
	float tmp = 0;
	dltX = getPosition().x;
	//CCLog("dltX: %f", dltX);
	
	if(dltX > leftP || dltX < rightP)
	{
		dltX > leftP ? tmp = leftP : tmp = rightP;
		CCActionInterval* move = CCMoveBy::actionWithDuration(1.0f, ccp(- dltX + tmp, 0));
		CCActionInterval* move_ease_out = CCEaseElasticOut::actionWithAction((CCActionInterval*)(move->copy()->autorelease()) );

		this->runAction(move_ease_out);

		return;
	}

}

void StagesBoard::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	// If it weren't for the TouchDispatcher, you would need to keep a reference
	// to the touch from touchBegan and check that the current touch is the same
	// as that one.
	// Actually, it would be even more complicated since in the Cocos dispatcher
	// you get CCSets instead of 1 UITouch, so you'd need to loop through the set
	// in each touchXXX method.
	stage_selected = false;
	selectedStage->setVisible(stage_selected);
	CCPoint pre_position = touch->previousLocationInView();
	pre_position = CCDirector::sharedDirector()->convertToGL(pre_position);
	//CCLog("pre_position: %f,%f", pre_position.x, pre_position.y);

	CCPoint touchPoint = touch->locationInView();
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
	//CCLog("touchPoint: %f,%f", touchPoint.x, touchPoint.y);

	CCPoint current_point = getPosition();
	CCPoint tmp = ccp(touchPoint.x - pre_position.x ,  touchPoint.y - pre_position.y);
	//CCLog("tmp: %f,%f", tmp.x, tmp.y);
	setPosition(ccp(current_point.x + tmp.x, current_point.y));
}

void StagesBoard::setRect(float a, float b, float c, float d)
{
	xori = a;
	yori = b;
	x = c;
	y = d;
}

CCRect StagesBoard::rect()
{
	return CCRectMake(xori, yori, x, y);
}

bool StagesBoard::containsTouchLocation(CCTouch* touch)
{
	CCPoint touchPoint = touch->locationInView();  
    touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);  
      
    return CCRect::CCRectContainsPoint(rect(), touchPoint);  

	//return CCRect::CCRectContainsPoint(rect(), convertTouchToNodeSpaceAR(touch));
}

void StagesBoard::onExit()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}	