#include "Events.hpp"

std::unordered_map<std::type_index, std::vector<std::function<void(const void *)>>> Events::m_eventHandlers;

