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
#include "NfDropdown.hpp"

namespace nfUI {

class NfNodeManager {
private:
    std::vector<std::shared_ptr<NfBoxxer>> nodes;
    std::vector<std::shared_ptr<NfBoxxer>> modalNodes;
    using ListenerID = size_t; // Unique identifier for listeners

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
        
        // Draw regular nodes first
        for (auto& node : nodes) {
            node->draw();
        }
        
        // Then draw modal nodes
        
        if (modalNodes.size()) {
            
            // Find the focused node - there should be only one probably but who knows now
            auto it = std::find_if(modalNodes.begin(), modalNodes.end(),
                                   [](const std::shared_ptr<NfBoxxer>& node) { return node->nodeIsFocused; });
            
            if (it != modalNodes.end()) {
                // Move the focused node to the end of the vector
                std::rotate(it, it + 1, modalNodes.end());
            }
            
            for (auto& modalNode : modalNodes) {
                modalNode->draw();
            }
            
        }
        
    }
    
    // Add a modal node
    void addModalNode(std::shared_ptr<NfBoxxer> node) {
        modalNodes.push_back(node);
    }

    // Remove a modal node by name
    bool removeModalNode(const std::string& name) {
        auto it = std::find_if(modalNodes.begin(), modalNodes.end(),
                               [&name](const std::shared_ptr<NfBoxxer>& node) { return node->_name == name; });
        if (it != modalNodes.end()) {
            modalNodes.erase(it);
            return true;
        }
        return false;
    }

    // Focus a node by name
    bool focusNode(const std::string& name) {
        bool found = unfocusAll(); // Unfocus all nodes first

        // Attempt to focus in regular nodes
        found = focusInCollection(nodes, name) || found;

        // Attempt to focus in modal nodes with higher priority
        found = focusInCollection(modalNodes, name) || found;

        return found; // Return true if any node was found and focused
    }

    bool unfocusAll() {
        for (auto& node : nodes) {
            node->nodeIsFocused = false;
        }
        for (auto& modalNode : modalNodes) {
            modalNode->nodeIsFocused = false;
        }
        return false; // Return false as a convenience for chaining
    }

    bool focusInCollection(std::vector<std::shared_ptr<NfBoxxer>>& collection, const std::string& name) {
        for (auto& node : collection) {
            if (node->_name == name) {
                node->nodeIsFocused = true;
                // emit event to the GUI - so it updates the hint
                g_eventManager.emit("gui_hint", "Node: " + name + " (" + ofToString(node->getChildCountOfRoot()) + " Elements)");
                return true; // Node found and focused
            }
        }
        return false; // Node not found in this collection
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
    
    
    // A method to handle requests from nodes to open modals.
    // This could involve passing a callback or using the event manager to handle the modal's response.
    void requestModalNode(std::shared_ptr<NfBoxxer> requestingNode, NfModalType modalType, NfUIConfig config, std::string name) {
        std::shared_ptr<NfBoxxer> modalNode;
        if (modalType == NfModalType::Dropdown) {
            modalNode = std::make_shared<NfDropdown>(config, name);
        }

        // Subscribe and save the listener ID
        ListenerID id = g_eventManager.subscribe("dropdown_selection", [requestingNode](const std::string& itemIndexStr) {
            int itemIndex = std::stoi(itemIndexStr);
            // requestingNode->setValueFromModal(itemIndex);
        });

        // Store the listener ID with the modal node or in a map
        modalNode->setListenerID(id); // Or modalListenerIDs[modalNodeName] = id;

        addModalNode(modalNode);
    }

    
    void closeModalNode(const std::string& modalNodeName) {
        // Retrieve the listener ID for the modal node
        // Assuming you have a way to get the modal node by name
        auto modalNode = getModalNodeByName(modalNodeName);
        if (modalNode) {
            ListenerID id = modalNode->getListenerID(); // Or id = modalListenerIDs[modalNodeName];
            
            // Unsubscribe using both the event type and the listener ID
            g_eventManager.unsubscribe("dropdown_selection", id);
            
            // Proceed to remove the modal node
            removeModalNode(modalNodeName);
            
            // Optionally, if using a map: modalListenerIDs.erase(modalNodeName);
        }
    }
    
    std::shared_ptr<NfBoxxer> getModalNodeByName(const std::string& modalNodeName) {
        // Search through the modalNodes collection for a node with the matching name
        for (const auto& modalNode : modalNodes) {
            if (modalNode->_name == modalNodeName) {
                return modalNode; // Return the found node
            }
        }
        // Return nullptr if no matching node is found
        return nullptr;
    }

    
    
};

} // namespace nfUI


#endif /* NfNodeManager_hpp */
