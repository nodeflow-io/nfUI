//
//  NfNodeManager.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 26.02.24.
//

#ifndef NfNodeManager_hpp
#define NfNodeManager_hpp

#include <vector>
#include <memory>
#include "NfBoxxer.hpp"

namespace nfUI {

class NfNodeManager {
private:
    std::vector<std::shared_ptr<NfBoxxer>> nodes;

public:
    // Add a reference to an existing NfBoxxer node
    void addNode(std::shared_ptr<NfBoxxer> node) {
        nodes.push_back(node);
    }

    // Draw all NfBoxxer nodes
    void drawNodes() {
        for (auto& node : nodes) {
            node->draw(); // Call the draw method of each node
        }
    }

    // Remove a NfBoxxer node by name
    bool removeNode(const std::string& name) {
        auto it = std::find_if(nodes.begin(), nodes.end(),
                               [&name](const std::shared_ptr<NfBoxxer>& node) { return node->_name == name; });
        if (it != nodes.end()) {
            nodes.erase(it);
            return true; // Successfully removed
        }
        return false; // Node not found
    }
};

} // namespace nfUI


#endif /* NfNodeManager_hpp */
