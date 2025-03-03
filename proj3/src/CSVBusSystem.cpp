#include "CSVBusSystem.h"
#include <memory>
#include <unordered_map>
#include <vector>

// Constructor
CCSVBusSystem::CCSVBusSystem(std::shared_ptr<CDSVReader> stopsrc, std::shared_ptr<CDSVReader> routesrc) {
    // TODO: Parse CSV files and populate stops and routes
}

// Destructor
CCSVBusSystem::~CCSVBusSystem() {
    // Cleanup if necessary
}

// Return the number of stops
std::size_t CCSVBusSystem::StopCount() const noexcept {
    return stops.size();
}

// Return the number of routes
std::size_t CCSVBusSystem::RouteCount() const noexcept {
    return routes.size();
}

// Retrieve stop by index
std::shared_ptr<SStop> CCSVBusSystem::StopByIndex(std::size_t index) const noexcept {
    if (index >= stops.size()) return nullptr;
    return stops[index];
}

// Retrieve stop by ID
std::shared_ptr<SStop> CCSVBusSystem::StopByID(TStopID id) const noexcept {
    auto it = stopMap.find(id);
    if (it != stopMap.end()) return it->second;
    return nullptr;
}

// Retrieve route by index
std::shared_ptr<SRoute> CCSVBusSystem::RouteByIndex(std::size_t index) const noexcept {
    if (index >= routes.size()) return nullptr;
    return routes[index];
}

// Retrieve route by name
std::shared_ptr<SRoute> CCSVBusSystem::RouteByName(const std::string &name) const noexcept {
    auto it = routeMap.find(name);
    if (it != routeMap.end()) return it->second;
    return nullptr;
}
