#include "Block.h"
#include "Unit.h"
using namespace std;
Block::Block(void)
{
	zOrder = -998;
}

void Block::addUnit(Unit* pUnit)
{
	unit_vector_.push_back(pUnit);
	pUnit->setBlock(this);
}

int Block::getDtX()
{
	vector<Unit*>::iterator it = unit_vector_.begin();
	return (*it)->dtX;
}

int Block::getDtY()
{
	vector<Unit*>::iterator it = unit_vector_.begin();
	return (*it)->dtY;
}

bool Block::isConnector(Block* tarB){
	bool ret = false;
	for (vector<Unit*>::iterator its = this->unit_vector_.begin();
					its != this->unit_vector_.end(); ++its)
			{
				int x1 = (*its)->idxOfX;
				int y1 = (*its)->idxOfY;

				for (vector<Unit*>::iterator it = tarB->unit_vector_.begin();
					it != tarB->unit_vector_.end(); ++it)
				{
					int x2 = (*it)->idxOfX;
					int y2 = (*it)->idxOfY;

					int dtX = abs(x1 - x2);
					int dtY = abs(y1 - y2);

					if( (dtX == 0 && dtY == 1) || (dtX == 1 && dtY == 0)){
						return true;
					}
				}
			}
	return ret;
}

Block::~Block(void)
{
}
