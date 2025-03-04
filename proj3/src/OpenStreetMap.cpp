#include "OpenStreetMap.h"
#include "XMLReader.h"
#include <memory>
#include <unordered_map>
#include <vector>

struct COpenStreetMap::SImplementation {
    std::unordered_map<CStreetMap::TNodeID, std::shared_ptr<CStreetMap::SNode>> nodes; // Node ID -> Node object
    std::unordered_map<CStreetMap::TWayID, std::shared_ptr<CStreetMap::SWay>> ways;   // Way ID -> Way object
};

// Constructor
COpenStreetMap::COpenStreetMap(std::shared_ptr<CXMLReader> src) : DImplementation(std::make_unique<SImplementation>()) {
    SXMLEntity entity;
    std::vector<std::string> row;

    // Read XML entities
    while (!src->End()) {
        if (!src->ReadEntity(entity)) {
            break; // If reading the entity failed, break the loop
        }

        // Process node elements
        if (entity.DType == SXMLEntity::EType::StartElement && entity.DNameData == "node") {
            CStreetMap::TNodeID nodeID = std::stoull(entity.AttributeValue("id"));
            double lat = std::stod(entity.AttributeValue("lat"));
            double lon = std::stod(entity.AttributeValue("lon"));

            // Create SNode implementation
            struct SNodeImpl : public CStreetMap::SNode {
                CStreetMap::TNodeID nodeID;
                CStreetMap::TLocation location;
                SNodeImpl(CStreetMap::TNodeID id, double latitude, double longitude)
                    : nodeID(id), location(latitude, longitude) {}

                CStreetMap::TNodeID ID() const noexcept override { return nodeID; }
                CStreetMap::TLocation Location() const noexcept override { return location; }
                std::size_t AttributeCount() const noexcept override { return 0; }
                std::string GetAttributeKey(std::size_t index) const noexcept override { return ""; }
                bool HasAttribute(const std::string &key) const noexcept override { return false; }
                std::string GetAttribute(const std::string &key) const noexcept override { return ""; }
            };

            DImplementation->nodes[nodeID] = std::make_shared<SNodeImpl>(nodeID, lat, lon);
        }

        // Process way elements
        if (entity.DType == SXMLEntity::EType::StartElement && entity.DNameData == "way") {
            CStreetMap::TWayID wayID = std::stoull(entity.AttributeValue("id"));
            std::vector<CStreetMap::TNodeID> wayNodes;

            // Read child nodes of the way (assuming that <nd> tags represent nodes in the way)
            while (src->ReadEntity(entity)) {
                if (entity.DType == SXMLEntity::EType::StartElement && entity.DNameData == "nd") {
                    CStreetMap::TNodeID nodeRef = std::stoull(entity.AttributeValue("ref"));
                    wayNodes.push_back(nodeRef);
                }

                // If we reach the end of the way element, stop processing
                if (entity.DType == SXMLEntity::EType::EndElement && entity.DNameData == "way") {
                    break;
                }
            }

            // Create SWay implementation
            struct SWayImpl : public CStreetMap::SWay {
                CStreetMap::TWayID wayID;
                std::vector<CStreetMap::TNodeID> nodeRefs;
            
                SWayImpl(CStreetMap::TWayID id, const std::vector<CStreetMap::TNodeID>& nodes)
                    : wayID(id), nodeRefs(nodes) {}
            
                std::size_t NodeCount() const noexcept override { 
                    return nodeRefs.size(); 
                }
            
                CStreetMap::TNodeID GetNodeID(std::size_t index) const noexcept override {
                    return index < nodeRefs.size() ? nodeRefs[index] : CStreetMap::InvalidNodeID;
                }
            };

            DImplementation->ways[wayID] = std::make_shared<SWayImpl>(wayID, wayNodes);
        }
    }
}


// Destructor
COpenStreetMap::~COpenStreetMap() {
    // Cleanup if necessary
}

std::size_t COpenStreetMap::NodeCount() const noexcept {
    return DImplementation->nodes.size();  // Return the size of the 'nodes' unordered_map
}

std::size_t COpenStreetMap::WayCount() const noexcept {
    return DImplementation->ways.size();  // Return the size of the 'ways' unordered_map
}

// Retrieve node by index
std::shared_ptr<CStreetMap::SNode> COpenStreetMap::NodeByIndex(std::size_t index) const noexcept {
    if (index >= DImplementation->nodes.size()) {
        return nullptr;  // Index out of bounds
    }

    // Convert the unordered_map to a vector and return the element at 'index'
    auto it = DImplementation->nodes.begin();
    std::advance(it, index);  // Advance the iterator to the specified index
    return it->second;  // Return the corresponding node
}
// Retrieve node by ID
std::shared_ptr<CStreetMap::SNode> COpenStreetMap::NodeByID(CStreetMap::TNodeID id) const noexcept {
    auto it = DImplementation->nodes.find(id);  // Search for the node ID in the unordered_map
    if (it != DImplementation->nodes.end()) {
        return it->second;  // Return the corresponding node
    }
    return nullptr;  // Return nullptr if not found
}
// Retrieve way by index
std::shared_ptr<CStreetMap::SWay> COpenStreetMap::WayByIndex(std::size_t index) const noexcept {
    if (index >= DImplementation->ways.size()) {
        return nullptr;  // Index out of bounds
    }

    // Convert the unordered_map to a vector and return the element at 'index'
    auto it = DImplementation->ways.begin();
    std::advance(it, index);  // Advance the iterator to the specified index
    return it->second;  // Return the corresponding way
}
// Retrieve way by ID
std::shared_ptr<CStreetMap::SWay> COpenStreetMap::WayByID(CStreetMap::TWayID id) const noexcept {
    auto it = DImplementation->ways.find(id);  // Search for the way ID in the unordered_map
    if (it != DImplementation->ways.end()) {
        return it->second;  // Return the corresponding way
    }
    return nullptr;  // Return nullptr if not found
}