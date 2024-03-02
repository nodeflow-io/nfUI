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
    
    NfNodeManager() {
        // Subscribe to node focus events
        g_eventManager.subscribe("node_focus", [this](const std::string& nodeName) {
            this->focusNode(nodeName);
        });
    }
    
    // Add a node
    void addNode(std::shared_ptr<NfBoxxer> node) {
        nodes.push_back(node);
    }

    // Draw all nodes, ensuring the focused node is drawn last
    void drawNodes() {
        // Find the focused node
        auto it = std::find_if(nodes.begin(), nodes.end(),
                               [](const std::shared_ptr<NfBoxxer>& node) { return node->nodeIsFocused; });
        
        if (it != nodes.end()) {
            // Move the focused node to the end of the vector
            std::rotate(it, it + 1, nodes.end());
        }

        // Draw the nodes, with the focused node being drawn last
        for (auto& node : nodes) {
            node->draw();
        }
    }

    // Focus a node by name
    bool focusNode(const std::string& name) {
        bool found = false;

        // First, unfocus all nodes
        for (auto& node : nodes) {
            node->nodeIsFocused = false; // Assuming each node has an isFocused boolean property
        }

        // Then, find and focus the specified node
        for (auto& node : nodes) {
            if (node->_name == name) {
                node->nodeIsFocused = true;
                // emit event to the gui - so it updates the hint
                g_eventManager.emit("gui_hint", "Node: "+ name+" ("+ofToString(node->getChildCountOfRoot())+" Elements)");
                found = true;
                break; // Stop the loop once the focused node is found
            }
        }

        return found; // Return true if the node was found and focused, false otherwise
    }


    // Remove a node
    bool removeNode(const std::string& name) {
        auto it = std::find_if(nodes.begin(), nodes.end(),
                               [&name](const std::shared_ptr<NfBoxxer>& node) { return node->_name == name; });
        if (it != nodes.end()) {
            nodes.erase(it);
            return true;
        }
        return false;
    }
};
} // namespace nfUI


#endif /* NfNodeManager_hpp */
