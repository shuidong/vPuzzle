#include "PiecesBoard.h"
#include"GameScene.h"
#include "Unit.h"

#include "res.h"

using namespace cocos2d;
using namespace std;
 int zOrderIdx = 10;
bool PiecesBoard::init(){ 
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	return true;  
}  

//void PiecesBoard::registerWithTouchDispatcher(){   
//   CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, INT_MIN + 1, true);  
//   CCLayer::registerWithTouchDispatcher();  
//}

bool PiecesBoard::ccTouchBegan (CCTouch *pTouch, CCEvent *pEvent){   

	isBlockSelected  = false;
	if ( !containsTouchLocation(pTouch) ){
		isBoardSlide = false;
	}else{
		isBoardSlide = true;
	}

	CCPoint pos = convertTouchToNodeSpace(pTouch);
	pSprite_ = NULL;
	pShadowSprite_ = NULL;
	pActiveBlk = NULL;

	Unit* pu = NULL;
	for(int i=0; i<6; i++){
		for(int j=0; j<6; j++){
			if(CCRect::CCRectContainsPoint(((CCNode* )pGame->pSprites[i][j])->boundingBox(), pos)){
				pGame->isSpritesUsed[i][j] = true;
				pSprite_ = pGame->pSprites[i][j];

				pu = (Unit*)pSprite_->getUserData();
				if(!pActiveBlk)//first hit
				{
					pActiveBlk = pu->parentBlock;
				}else
				{
					if( pu->parentBlock->zOrder > pActiveBlk->zOrder){
						pActiveBlk = pu->parentBlock;
					}
				}
			}
		}
	}
	if(!pActiveBlk){
		return true;
	}
	//for(int i=0; i<6; i++){
	//	for(int j=0; j<6; j++){
	//		if(CCRect::CCRectContainsPoint(((CCNode* )pGame->pSprites[i][j])->boundingBox(), pos)){

				pActiveBlk = pu->parentBlock;
				int tmp = 200;

				for (vector<Unit*>::iterator it = pActiveBlk->unit_vector_.begin();
					it != pActiveBlk->unit_vector_.end(); ++it)
				{
					CCAction*  action = CCSpawn::actions(
						CCScaleTo::actionWithDuration( 0.2, 1.05f),
						//	CCMoveBy::actionWithDuration( 0.2, CCPointMake(-5,-10)),
						CCFadeTo::actionWithDuration(0.2, 180),
						NULL);

					pShadowSprite_ = pGame->shadowSprites[(*it)->idxOfX][(*it)->idxOfY];
					reorderChild(pShadowSprite_, tmp);
					//CCLog("action...");
					pShadowSprite_->runAction( action);
				}
				for (vector<Unit*>::iterator it = pActiveBlk->unit_vector_.begin();
					it != pActiveBlk->unit_vector_.end(); ++it)
				{
					reorderChild((*it)->mSprite, tmp);
				}

				isBlockSelected  = true;
				isBoardSlide = false;

				return true;
			/*}
		}
	}*/
	return true;  
}  

CCRect PiecesBoard::rect()
{
	return CCRectMake(xori, yori, x, y);
}

void PiecesBoard::setRect(float a, float b, float c, float d)
{
	xori = a;
	yori = b;
	x = c;
	y = d;
}

bool PiecesBoard::containsTouchLocation(CCTouch* touch)
{
	CCPoint touchPoint = touch->locationInView();  
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);  

	return CCRect::CCRectContainsPoint(rect(), touchPoint);  

}

void PiecesBoard::ccTouchMoved (cocos2d::CCTouch *touch, CCEvent *pEvent){
	CCPoint pre_position = touch->previousLocationInView();
	pre_position = CCDirector::sharedDirector()->convertToGL(pre_position);

	CCPoint position = touch->locationInView( );
	position = CCDirector::sharedDirector()->convertToGL( position );

	CCPoint current_point = this->getPosition();
	if(this->isBoardSlide)
	{
		for(int i=0; i<6; i++){
			for(int j=0; j<6; j++){
				if(!pGame->isSpritesUsed[i][j])
				{
					CCPoint pSrpite_current_point = pGame->pSprites[i][j]->getPosition();
					CCPoint pShadow_Srpite_current_point = pGame->shadowSprites[i][j]->getPosition();
					pGame->pSprites[i][j]->setPosition(ccp(pSrpite_current_point.x, pSrpite_current_point.y + position.y - pre_position.y));
					pGame->shadowSprites[i][j]->setPosition(ccp(pShadow_Srpite_current_point.x, pShadow_Srpite_current_point.y + position.y - pre_position.y));

					Unit* pu = (Unit*)pGame->pSprites[i][j]->getUserData();
					pu->dtY += (position.y - pre_position.y);
				}
			}
		}
		return;
	}
	if(pSprite_ && isBlockSelected)
	{
		for (vector<Unit*>::iterator it = pActiveBlk->unit_vector_.begin();
			it != pActiveBlk->unit_vector_.end(); ++it)
		{
			CCPoint pSrpite_current_point = (*it)->mSprite->getPosition();
			CCPoint pShadow_Srpite_current_point = pGame->shadowSprites[(*it)->idxOfX][(*it)->idxOfY]->getPosition();

			(*it)->mSprite->setPosition(ccp(pSrpite_current_point.x + position.x - pre_position.x, pSrpite_current_point.y + position.y - pre_position.y));
			pGame->shadowSprites[(*it)->idxOfX][(*it)->idxOfY]->setPosition(ccp(pShadow_Srpite_current_point.x + position.x - pre_position.x, pShadow_Srpite_current_point.y + position.y - pre_position.y));

			(*it)->dtX += (position.x - pre_position.x);
			(*it)->dtY += (position.y - pre_position.y);
		}
	}
}  


void PiecesBoard::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent){ 
	if(pActiveBlk != NULL)
	{	
		pActiveBlk ->zOrder = zOrderIdx++;
		for (vector<Unit*>::iterator it = pActiveBlk->unit_vector_.begin();
			it != pActiveBlk->unit_vector_.end(); ++it)
		{
			CCSprite* tmpS = pGame->shadowSprites[(*it)->idxOfX][(*it)->idxOfY];

			CCAction*  action = CCSpawn::actions(
				CCScaleTo::actionWithDuration( 0.2, 1.0f),
				CCFadeTo::actionWithDuration(0.2, 255),
				NULL);


			tmpS->runAction( action);
		}
	}

	if(NULL != pActiveBlk){
		bool shouldRemov = false;
		Block* targetBlk;
		for (vector<Block*>::iterator it = pGame->blocks.begin();
			it != pGame->blocks.end(); ++it)
		{
			if(*it != pActiveBlk ){
				int dtx = (*it)->getDtX() - pActiveBlk->getDtX() ;
				int dty = (*it)->getDtY() - pActiveBlk->getDtY() ;

				if(true && abs(dtx) < 15 && abs(dty) < 15 && pActiveBlk->isConnector((*it))){
					//CCLog("should be remove");
					shouldRemov = true;
					targetBlk = (*it);
					for (vector<Unit*>::iterator its = pActiveBlk->unit_vector_.begin();
						its != pActiveBlk->unit_vector_.end(); ++its)
					{
						CCPoint current_point = (*its)->mSprite->getPosition();
						(*its)->mSprite->setPosition(ccp((*its)->ox + (*it)->getDtX() + (*its)->mSprite->getContentSize().width/2, 
							(*its)->oy + (*it)->getDtY() - (*its)->mSprite->getContentSize().height/2));

						pGame->shadowSprites[(*its)->idxOfX][(*its)->idxOfY]->setPosition(ccpAdd((*its)->mSprite->getPosition(), ccp(5, -5)));
						reorderChild(pGame->shadowSprites[(*its)->idxOfX][(*its)->idxOfY], 100);

						(*its)->dtX = (*it)->getDtX();
						(*its)->dtY = (*it)->getDtY();
						CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(merge_Eff);
					}
					break;

				}
			}
		}

		if(true == shouldRemov)
		{
			//remove the pActiveBlk
			//blocks.erase(pActiveBlk);
			for (vector<Unit*>::iterator its = pActiveBlk->unit_vector_.begin();
				its != pActiveBlk->unit_vector_.end(); ++its)
			{
				targetBlk->unit_vector_.push_back(*its);
				(*its)->parentBlock = targetBlk;
			}
			targetBlk ->zOrder = zOrderIdx++;
			pActiveBlk->unit_vector_.clear();//del from activeBlk

			//del activeBlk from blocks
			for (vector<Block*>::iterator it = pGame->blocks.begin();
				it != pGame->blocks.end(); ++it)
			{
				if(*it == pActiveBlk){
					pGame->blocks.erase(it);

					int resultBlocks = pGame->blocks.size();
					if(1 == resultBlocks){
						//CCLog("you win.");
					}

					break;
				}
			}
		}
	}
	pSprite_= NULL;
	pActiveBlk = NULL;

}  

void PiecesBoard::ccTouchCancelled (CCTouch *pTouch, CCEvent *pEvent){ 
}  