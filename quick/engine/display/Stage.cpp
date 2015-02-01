#include "Stage.h"

NS_QUICK_DISPLAY_BEGIN

Stage::Stage() 
:_frameRate(30), _stageWidth(960), _stageHeight(640)
{
	
}

Stage::~Stage() {
	
}

void Stage::draw() {

}

int Stage::getFrameRate() const {
	return _frameRate;
}

void Stage::setFrameRate(int frameRate) {
	_frameRate = frameRate;
}

float Stage::getStageWidth() const {
	return _stageWidth;
}

float Stage::getStageHeight() const {
	return _stageHeight;
}

void Stage::setStageWidth(float w) {
	_stageWidth = w;
}

void Stage::setStageHeight(float h) {
	_stageHeight = h;
}

int Stage::getStageDisplayState() const {
	return _displayState;
}

void Stage::setStageDisplayState(StageDisplayState state) {
	_displayState = state;
}

NS_QUICK_DISPLAY_END