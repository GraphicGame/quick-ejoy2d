#ifndef __STAGE
#define __STAGE

#include "../NameSpace.h"
#include "DisplayObjectContainer.h"

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
	void draw() override;

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