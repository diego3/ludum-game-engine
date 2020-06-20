#pragma once

#include "EventManager.h"

EventManager* EventManager::instance = 0;

// https://en.cppreference.com/w/cpp/utility/functional/bind
// https://en.cppreference.com/w/cpp/utility/functional/function
// https://stackoverflow.com/questions/9568150/what-is-a-c-delegate

EventManager* EventManager::Get() {
	if (instance == NULL) {
		instance = new EventManager();
	}
	return instance;
}

bool EventManager::AddListener(EventType evt, std::function<void(IEventData)> function) {
	listeners.push_back(function);

	std::map<EventType, EventListenerList>::iterator it = listenersMap.find(evt);
	if (it != listenersMap.end()) {
		EventListenerList lista = listenersMap[evt];
		lista.push_back(function);
	}
	else {
		EventListenerList newList = EventListenerList{};
		newList.push_back(function);
		listenersMap[evt] = newList;
	}

	return true;
}

bool EventManager::RemoveListener(EventType evt, std::function<void(IEventData)> function) {
	
	return false;
}

bool EventManager::QueueEvent(IEventData evt) {
	eventQueue.push_back(evt);
	return true;
}

void EventManager::Update(float deltaTime) {
	//eventQueue
	timer--;
	if (timer <= 0) {
		timer = 60;
	}

	while (!eventQueue.empty()) {
		IEventData eventData = eventQueue.front();
		eventQueue.pop_front();

		EventType evt = eventData.GetType();
		printf("[EventType::%d]\n", evt);
		std::map<EventType, EventListenerList>::iterator it = listenersMap.find(evt);
		if (it != listenersMap.end()) {
			EventListenerList lista = listenersMap[evt];
			for (std::function<void(IEventData)> fn : lista) {
				fn(eventData);
			}
		}
	}
}






IEventData::IEventData(EventType type, const char* name)
{
	this->type = type;
	this->name = name;
}

EventType IEventData::GetType()
{
	return this->type;
}
