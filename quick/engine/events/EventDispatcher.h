#ifndef __EVENTDISPATCHER
#define __EVENTDISPATCHER

#include <string>
#include <vector>
#include <unordered_map>

#include "../NameSpace.h"

NS_QUICK_EVENTS_BEGIN

class EventDispatcher;

class Event {
public:
	Event(std::string type);
	virtual ~Event();
public:
	const std::string& getType() const;
	const EventDispatcher * getTarget() const;
	void setTarget(EventDispatcher *target);
protected:
	Event();
protected:
	std::string _type;
	EventDispatcher *_target;
};

//--Obsolete.
//class Function {
//public:
//	Function();
//	Function(const char *funcKey);
//	~Function();
//public:
//	void call();
//	bool hasCalled() const;
//private:
//	bool _called;
//	std::string _funcKey;
//};

class EventDispatcher {
public:
	EventDispatcher();
	virtual ~EventDispatcher();
public:
	//void addEventListener(std::string type, Function *callback);
	void addEventListener(const char *type, const char *funcKey);
	//bool dispatchEvent(Event *evt);	//Obsolete...
	bool dispatchEvent(const char *type);
	//bool hasEventListener(std::string type) const;
	bool hasEventListener(const char *type) const;
	int  getEventListenerCount(const char *type);
	//void removeEventListener(std::string type, Function *callback);
	void removeEventListener(const char *type, const char *funcKey);
	//void removeEventListener(std::string type);
	void removeEventListener(const char *type);
	void removeAllEventListener();
private:
	void call(std::string funcKey);
private:
	//std::unordered_map<std::string, std::vector<Function*>* > _eventListenersMap;
	std::unordered_map<std::string, std::vector<std::string>* > _eventListenersMap;

	//typedef std::unordered_map<std::string, std::vector<Function*>* >::const_iterator _citMap;
	//typedef std::vector<Function*>::iterator _itVec;
	//typedef std::vector<Function*> _tVec;

	typedef std::unordered_map<std::string, std::vector<std::string>* >::const_iterator _citMap;
	typedef std::vector<std::string>::iterator _itVec;
	typedef std::vector<std::string> _tVec;
};

NS_QUICK_EVENTS_END

#endif