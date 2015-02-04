#ifndef __STAGE
#define __STAGE

#include "../NameSpace.h"
#include "DisplayObjectContainer.h"
#include "Layer.h"

#include <vector>

NS_QUICK_DISPLAY_BEGIN

enum StageDisplayState {
	NORMAL,
	FULL_SCREEN
};

class Stage : public DisplayObjectContainer {
public:
	Stage();
	~Stage();
public:
	static Stage * getInstance();
	void draw() override;

	void addLayer(Layer *layer);
	void addLayerAt(Layer *layer, int index);
	void removeLayer(Layer *layer);
	void removeLayerAt(int index);
	Layer * getLayerAt(int index);
	Layer * getLayerByName(std::string name);
	int getLayerIndex(Layer *layer);
	void setLayerIndex(Layer *layer, int index);
	void swapLayers(Layer *layer1, Layer *layer2);
	void swapLayersAt(int index1, int index2);

	int getFrameRate() const;
	void setFrameRate(int frameRate);

	float getStageWidth() const;
	float getStageHeight() const;
	void setStageWidth(float w);
	void setStageHeight(float h);

	int getStageDisplayState() const;
	void setStageDisplayState(StageDisplayState state);
private:
	int _frameRate;
	float _stageWidth, _stageHeight;
	int _displayState;
};

NS_QUICK_DISPLAY_END

#endif