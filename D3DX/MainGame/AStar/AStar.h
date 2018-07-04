#pragma once
#include "Cell.h"

class AStar
{
	//전체 타일
	//vector<ST_CELL*> _vTotalList;
	//vector<ST_CELL*>::iterator _viTotalList;
	//
	////갈수 있는 타일 벡터
	//vector<ST_CELL*> _vOpenList;
	//vector<ST_CELL*>::iterator _viOpenList;
	//
	////최종적으로 제일 가까운 경로 담는 벡터
	//vector<ST_CELL*> _vCloseList;
	//vector<ST_CELL*>::iterator _viCloseList;
	//
	//ST_CELL* _startTile;
	//ST_CELL* _endTile;
	//ST_CELL* _currentTile;
	//
	//tagTile* _currentGameTile;

public:
	AStar();
	~AStar();
};

