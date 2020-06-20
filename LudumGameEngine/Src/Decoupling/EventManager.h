#pragma once

// https://www.udemy.com/course/patterns-cplusplus/learn  Observer Section
// https://gameprogrammingpatterns.com/observer.html
// https://blog.molecular-matters.com/2011/09/19/generic-type-safe-delegates-and-events-in-c/


#include <iostream>
#include <list>
#include <string>
#include <map>
#include <algorithm>
#include <functional>
#include <memory>
#include <strstream>

// {1BA06E67-4F6C-4E7C-9E01-BC06142B0916}
//DEFINE_GUID(<< name >> ,0x1ba06e67, 0x4f6c, 0x4e7c, 0x9e, 0x1, 0xbc, 0x6, 0x14, 0x2b, 0x9, 0x16);

enum class EventType {
	GAME_STARTED,
	GAME_OVER,
	COLLISION_ENTER,
	PLAYER_MOVE_LEFT,
	PLAYER_MOVE_RIGHT,
	PLAYER_MOVE
};

class IEventData {
public:
	IEventData(EventType type, const char* name);

	const char* name;
	EventType type;
	EventType GetType();
	virtual const char* GetName() { return "IEventDataGetNameEmpty"; };
};

/*
class IEventData {
	public:
	virtual const EventType& GetEventType(void) const = 0;
	virtual float GetTimeStamp(void) const = 0;
	virtual void Serialize(std::ostrstream& out) const = 0;
	virtual std::shared_ptr<IEventData> VCopy(void) const = 0;
	virtual const char* GetName(void) const = 0;
};


class BaseEventData : public IEventData
{
	const float timeStamp;
public:
	explicit BaseEventData(const float timeStamp = 0.0f) :
	m_timeStamp(timeStamp) { }
	virtual ˜BaseEventData(void) {}
	// Returns the type of the event
	virtual const EventType& GetEventType(void) const = 0;
	float GetTimeStamp(void) const { return timeStamp; }
	// Serializing for network out.
	virtual void Serialize(std::ostrstream &out) const { }
};
*/

class EventCollision : public IEventData {
public:
	///Player* other;
	EventCollision(EventType type, const char* name /*, Player* object*/)
		: IEventData(type, name)
	{
		printf("EventCollision constructor\n");
		//other = object;
	}

	const char* GetName() override {
		return "EventCollision";
	}
};

class EventManager {
public:

	static EventManager* Get();

	bool AddListener(EventType evt, std::function<void(std::shared_ptr<IEventData>)> function);

	bool RemoveListener(EventType evt, std::function<void(std::shared_ptr<IEventData>)> function);

	bool QueueEvent(const std::shared_ptr<IEventData>& evt);

	void Update(float deltaTime);

private:
	typedef std::list<std::function<void(std::shared_ptr<IEventData>)>> EventListenerList;

	int timer = 60;

	EventManager() {}
	EventManager(const EventManager&) = delete;
	EventManager& operator=(const EventManager&) = delete;

	static EventManager* instance;

	EventListenerList listeners;
	std::map<EventType, EventListenerList> listenersMap;
	std::list<std::shared_ptr<IEventData>> eventQueue;

	int currentQueue = 0;
};

