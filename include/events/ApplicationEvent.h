//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXLENGINE_APPLICATIONEVENTS_H
#define PIXLENGINE_APPLICATIONEVENTS_H

#include "events/Event.h"


class AppTickEvent : public Event {
public:
    AppTickEvent() = default;

    EVENT_CLASS_TYPE(AppTick)

    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppUpdateEvent : public Event {
public:
    AppUpdateEvent() = default;

    EVENT_CLASS_TYPE(AppUpdate)

    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppRenderEvent : public Event {
public:
    AppRenderEvent() = default;

    EVENT_CLASS_TYPE(AppRender)

    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppQuitEvent : public Event {
public:
    AppQuitEvent() = default;

    EVENT_CLASS_TYPE(AppQuit)

    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

#endif //PIXLENGINE_APPLICATIONEVENTS_H
