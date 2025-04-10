//
//  NfNodeManager.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 26.02.24.
//

#include "NfNodeManager.hpp"

namespace nfUI {

// Global instance definition
NfNodeManager g_nodeManager;

// Constructor
NfNodeManager::NfNodeManager() {
    // Subscribe to node focus events
    nfUI::NfEventManager::getEventManager().subscribe("node_focus", [this](const std::string& nodeName) {
        this->focusNode(nodeName);
    });
}

// Node management
void NfNodeManager::addNode(std::shared_ptr<NfBoxxer> node) {
    nodes.push_back(node);
}

void NfNodeManager::addModalNode(std::shared_ptr<NfBoxxer> node) {
    modalNodes.push_back(node);
}

bool NfNodeManager::removeNode(const std::string& name) {
    auto it = std::find_if(nodes.begin(), nodes.end(),
                           [&name](const std::shared_ptr<NfBoxxer>& node) { return node->_name == name; });
    if (it != nodes.end()) {
        nodes.erase(it);
        return true;
    }
    return false;
}

bool NfNodeManager::removeModalNode(const std::string& name) {
    auto it = std::find_if(modalNodes.begin(), modalNodes.end(),
                           [&name](const std::shared_ptr<NfBoxxer>& node) { return node->_name == name; });
    if (it != modalNodes.end()) {
        modalNodes.erase(it);
        return true;
    }
    return false;
}

// Drawing
void NfNodeManager::drawNodes() {
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

// Focus management
bool NfNodeManager::focusNode(const std::string& name) {
    bool found = unfocusAll(); // Unfocus all nodes first

    // Attempt to focus in regular nodes
    found = focusInCollection(nodes, name) || found;

    // Attempt to focus in modal nodes with higher priority
    found = focusInCollection(modalNodes, name) || found;

    return found; // Return true if any node was found and focused
}

bool NfNodeManager::unfocusAll() {
    for (auto& node : nodes) {
        node->nodeIsFocused = false;
    }
    for (auto& modalNode : modalNodes) {
        modalNode->nodeIsFocused = false;
    }
    return false; // Return false as a convenience for chaining
}

bool NfNodeManager::focusInCollection(std::vector<std::shared_ptr<NfBoxxer>>& collection, const std::string& name) {
    for (auto& node : collection) {
        if (node->_name == name) {
            node->nodeIsFocused = true;
            // emit event to the GUI - so it updates the hint
            nfUI::NfEventManager::getEventManager().emit("gui_hint", "Node: " + name + " (" + ofToString(node->getChildCountOfRoot()) + " Elements)");
            return true; // Node found and focused
        }
    }
    return false; // Node not found in this collection
}

// Modal management
void NfNodeManager::requestModalNode(std::shared_ptr<NfBoxxer> requestingNode, NfModalType modalType, NfUIConfig config, std::string name) {
    std::shared_ptr<NfBoxxer> modalNode;
    if (modalType == NfModalType::Dropdown) {
        modalNode = std::make_shared<NfDropdown>(config, name);
    }

    // Subscribe and save the listener ID
    ListenerID id = nfUI::NfEventManager::getEventManager().subscribe("dropdown_selection", [requestingNode](const std::string& itemIndexStr) {
        int itemIndex = std::stoi(itemIndexStr);
        // requestingNode->setValueFromModal(itemIndex);
    });

    // Store the listener ID with the modal node or in a map
    modalNode->setListenerID(id); // Or modalListenerIDs[modalNodeName] = id;

    addModalNode(modalNode);
}

void NfNodeManager::closeModalNode(const std::string& modalNodeName) {
    // Retrieve the listener ID for the modal node
    auto modalNode = getModalNodeByName(modalNodeName);
    if (modalNode) {
        ListenerID id = modalNode->getListenerID(); // Or id = modalListenerIDs[modalNodeName];
        
        // Unsubscribe using both the event type and the listener ID
        nfUI::NfEventManager::getEventManager().unsubscribe("dropdown_selection", id);
        
        // Proceed to remove the modal node
        removeModalNode(modalNodeName);
    }
}

std::shared_ptr<NfBoxxer> NfNodeManager::getModalNodeByName(const std::string& modalNodeName) {
    // Search through the modalNodes collection for a node with the matching name
    for (const auto& modalNode : modalNodes) {
        if (modalNode->_name == modalNodeName) {
            return modalNode; // Return the found node
        }
    }
    // Return nullptr if no matching node is found
    return nullptr;
}

} // namespace nfUI
