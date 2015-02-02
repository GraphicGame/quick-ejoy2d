#include "Stage.h"
#include "DisplayObjectType.h"

NS_QUICK_DISPLAY_BEGIN

Stage::Stage() 
:_frameRate(30), _stageWidth(960), _stageHeight(640)
{
	setType(STAGE);
}

Stage::~Stage() {
	
}

void Stage::draw() {

}

void Stage::addLayer(Layer *layer) {
	addChild(layer);
}

void Stage::addLayerAt(Layer *layer, int index) {
	addChildAt(layer, index);
}

void Stage::removeLayer(Layer *layer) {
	removeChild(layer);
}

void Stage::removeLayerAt(int index) {
	removeChildAt(index);
}

DisplayObject * Stage::getLayerAt(int index) {
	return getChildAt(index);
}

DisplayObject * Stage::getLayerByName(std::string name) {
	return getChildByName(name);
}

int Stage::getLayerIndex(Layer *layer) {
	return getChildIndex(layer);
}

void Stage::setLayerIndex(Layer *layer, int index) {
	setChildIndex(layer, index);
}

void Stage::swapLayers(Layer *layer1, Layer *layer2) {
	swapChildren(layer1, layer2);
}

void Stage::swapLayersAt(int index1, int index2) {
	swapChildrenAt(index1, index2);
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