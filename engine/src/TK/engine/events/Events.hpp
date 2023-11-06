#ifndef ZENIT_EVENTS_HPP
#define ZENIT_EVENTS_HPP

#include <stdexcept>
#include <typeindex>
#include <functional>
#include "glm/vec2.hpp"
#include "TK/engine/utils/Log.hpp"

/**
 * A simple event system class that handles the subscribing to events and also deleting of events.
 * @author ChikyuKido
 */
class Events {
public:
    /**
     * Adds a function to the handler list for a specific event.
     * @tparam T The event type you will subscribe to
     * @param function the function that handles the event
     * @note IMPORTANT: The event will be deleted after all the handlers have received the event.
     * So copy the event or only the relevant data.
     * @author ChikyuKido
     */
    template<typename T>
    static void subscribe(std::function<void(const T *)> function) {
        m_eventHandlers[typeid(T)].emplace_back([function](const void *event) {
            if (event != nullptr) {
                function(static_cast<const T *>(event));
            }
        });
    }

    /**
     * Fires a event to all the subscribe handlers.
     * @tparam T the event type that will be fired
     * @param event the event that is fired
     * @note the event will be automatically freed after every handler has received the event
     * @author ChikyuKido
     */
    template<typename T>
    static void fire(const T *event) {
        for (const auto &handler: m_eventHandlers[typeid(T)]) {
            try {
                handler(event);
            } catch (const std::exception &e) {
                TK_LOG_E("Engine") << "Handler couldn't handle the event. Message: " << e.what();
            }
        }
        delete event;
    }

private:
    static std::unordered_map<std::type_index, std::vector<std::function<void(const void *)>>>
            m_eventHandlers;
};

/**
 * A event to change the current Screen.
 * @author ChikyuKido
 */
struct SwitchScreenEvent {
    std::type_index newScreen;

    explicit SwitchScreenEvent(const std::type_index &newScreen) : newScreen(newScreen) {}
};

/**
 * This event is fired when a screen was switched
 * @author ChikyuKido
 */
struct ScreenSwitchedEvent {
    std::string oldScreen;
    std::string newScreen;

    ScreenSwitchedEvent(std::string oldScreen, std::string newScreen)
            : oldScreen(std::move(oldScreen)), newScreen(std::move(newScreen)) {}
};

/**
 * A simple keyPressedEvent with the keycode.
 * This event is called repeated.
 * So if a key is pressed for a longer period this event gets called multiple times
 * @author ChikyuKido
 */
struct KeyPressedEvent {
    u_int keyCode;

    explicit KeyPressedEvent(const u_int keyCode) : keyCode(keyCode) {}
};

/**
 * A simple keyPressedEvent with the keycode.
 * This event is called repeated.
 * So if a key is pressed for a longer period this event gets called multiple times
 * @author ChikyuKido
 */
struct KeyReleasedEvent {
    u_int keyCode;

    explicit KeyReleasedEvent(const u_int keyCode) : keyCode(keyCode) {}
};

/**
 * A simple mousePressedEvent with the pos and the button.
 * This event is called repeated.
 * So if a button is pressed for a longer period this event gets called multiple times
 * @author ChikyuKido
 */
/*
struct MousePressedEvent {
   glm::vec2 pos;
   sf::Mouse::Button button;

   MousePressedEvent(sf::Vector2i pos, sf::Mouse::Button button) : pos(pos), button(button) {}
};


struct MouseMovedEvent {
   sf::Vector2i pos;

   explicit MouseMovedEvent(sf::Vector2i pos) : pos(pos) {}
};

struct MouseDraggedMovedEvent {
   sf::Vector2i pos;
   sf::Mouse::Button button;

   MouseDraggedMovedEvent(sf::Vector2i pos, sf::Mouse::Button button) : pos(pos), button(button) {}
};

struct MapChangeEvent {
   std::shared_ptr<tson::Map> map;

   explicit MapChangeEvent(const std::shared_ptr<tson::Map> &map) : map(map) {}
};*/

#endif
