#include "OpenStreetMap.h"
#include "XMLReader.h"
#include <memory>
#include <unordered_map>
#include <vector>

// Constructor
COpenStreetMap::COpenStreetMap(std::shared_ptr<CXMLReader> src) {
    // TODO: Parse XML and populate nodes and ways
}

// Destructor
COpenStreetMap::~COpenStreetMap() {
    // Cleanup if necessary
}

// Return number of nodes
std::size_t COpenStreetMap::NodeCount() const noexcept {
    return nodes.size();
}

// Return number of ways
std::size_t COpenStreetMap::WayCount() const noexcept {
    return ways.size();
}

// Retrieve node by index
std::shared_ptr<SNode> COpenStreetMap::NodeByIndex(std::size_t index) const noexcept {
    if (index >= nodes.size()) return nullptr;
    return nodes[index];
}

// Retrieve node by ID
std::shared_ptr<SNode> COpenStreetMap::NodeByID(TNodeID id) const noexcept {
    auto it = nodeMap.find(id);
    if (it != nodeMap.end()) return it->second;
    return nullptr;
}

// Retrieve way by index
std::shared_ptr<SWay> COpenStreetMap::WayByIndex(std::size_t index) const noexcept {
    if (index >= ways.size()) return nullptr;
    return ways[index];
}

// Retrieve way by ID
std::shared_ptr<SWay> COpenStreetMap::WayByID(TWayID id) const noexcept {
    auto it = wayMap.find(id);
    if (it != wayMap.end()) return it->second;
    return nullptr;
}
