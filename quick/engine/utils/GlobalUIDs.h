#ifndef __GLOBALUIDS
#define __GLOBALUIDS

class GlobalUIDs {
public:
	static int getUID() {
		return _currentUID++;
	}
private:
	static int _currentUID;
};

int GlobalUIDs::_currentUID = 0;


#endif