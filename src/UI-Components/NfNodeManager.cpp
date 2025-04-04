//
//  NfNodeManager.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 26.02.24.
//

#include "NfNodeManager.hpp"
#include "NfEventBus.hpp"

namespace nfUI {

// Global instance definition
NfNodeManager g_nodeManager;

// Constructor
NfNodeManager::NfNodeManager() {
    // Subscribe to node focus events
    nfUI::NfEventManager::getEventManager().subscribe("node_focus", [this](const std::string& nodeName) {
        this->focusNode(nodeName);
    });

    BUS.subscribe(AppEventType::MOUSE_PRESSED,
                       [this](const Event& e){ this->routeMousePressed(e); },
                       nullptr, this);
    BUS.subscribe(AppEventType::MOUSE_RELEASED,
                       [this](const Event& e){ this->routeMouseReleased(e); },
                       nullptr, this);
    BUS.subscribe(AppEventType::MOUSE_MOVED,
                       [this](const Event& e){ this->routeMouseMoved(e); },
                       nullptr, this);
    BUS.subscribe(AppEventType::MOUSE_DRAGGED,
                       [this](const Event& e){ this->routeMouseDragged(e); },
                       nullptr, this);
    BUS.subscribe(AppEventType::MOUSE_SCROLLED,
                       [this](const Event& e){ this->routeMouseScrolled(e); },
                       nullptr, this);
    BUS.subscribe(AppEventType::KEY_PRESSED,
                       [this](const Event& e){ this->routeKeyPressed(e); },
                       nullptr, this);
    BUS.subscribe(AppEventType::KEY_RELEASED,
                       [this](const Event& e){ this->routeKeyReleased(e); },
                       nullptr, this);
}

// Destructor
NfNodeManager::~NfNodeManager() {
    // Clean up all modal nodes first
    for (auto& modalNode : modalNodes) {
        if (modalNode) {
            closeModalNode(modalNode->_name);
        }
    }
    modalNodes.clear();

    // Clear regular nodes
    nodes.clear();

    // Unsubscribe from all events
    // nfUI::NfEventManager::getEventManager().unsubscribeAll(this);
    BUS.unsubscribeAll(this);
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
    // Draw regular nodes first
    for (auto& node : nodes) {
        node->draw();
    }
    
    // Then draw modal nodes
    if (modalNodes.size()) {
        
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

    // Find the focused node
    auto it = std::find_if(nodes.begin(), nodes.end(),
                           [](const std::shared_ptr<NfBoxxer>& node) { return node->nodeIsFocused; });
    
    if (it != nodes.end()) {
        // Move the focused node to the end of the vector
        std::rotate(it, it + 1, nodes.end());
    }

    // Attempt to focus in modal nodes with higher priority
    found = focusInCollection(modalNodes, name) || found;

    // Find the focused node - there should be only one probably but who knows now
    it = std::find_if(modalNodes.begin(), modalNodes.end(),
                            [](const std::shared_ptr<NfBoxxer>& node) { return node->nodeIsFocused; });
    
    if (it != modalNodes.end()) {
        // Move the focused node to the end of the vector
        std::rotate(it, it + 1, modalNodes.end());
    }

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


// --- Event Bus ---

void NfNodeManager::routeMousePressed(const Event& e) {
    try {
            auto globalCoordsPair = std::any_cast<std::tuple<int, int, int>>(e.payload);
            ofPoint globalPoint(std::get<0>(globalCoordsPair), std::get<1>(globalCoordsPair));
            int button = std::get<2>(globalCoordsPair);

            // Iterate children in reverse (topmost first)
            for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
                auto& node = *it;
                if (node->boundsMouse.inside(globalPoint)) {
                    ofLogNotice("NfNodeManager::routeMousePressed") << "Node pressed: " + node->_name;
                    // 3. Calculate local coordinates for the child
                    ofPoint localPoint = globalPoint - node->boundsMouse.getPosition();
                    bool consumed = node->handleRoutedMouseEvent(AppEventType::MOUSE_PRESSED, localPoint, button);
                    if (consumed) {
                        return; // Child handled it, stop processing.
                    }
                }
            }
            // No child consumed it, Panel handles it (optional)
            // ofLogNotice("Panel " + id) << "Panel itself was pressed.";
            // Start dragging panel? Publish PANEL_PRESSED? Set internal state?

        } catch (const std::bad_any_cast& e) {
             ofLogError("NfNodeManager::routeMousePressed") << "Bad payload cast for MOUSE_PRESSED";
        }
}

void NfNodeManager::routeMouseReleased(const Event& e) {
    try {
            auto globalCoordsPair = std::any_cast<std::tuple<int, int, int>>(e.payload);
            ofPoint globalPoint(std::get<0>(globalCoordsPair), std::get<1>(globalCoordsPair));
            int button = std::get<2>(globalCoordsPair);

            // Iterate children in reverse (topmost first)
            for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
                auto& node = *it;
                if (node->boundsMouse.inside(globalPoint)) {
                    ofLogNotice("NfNodeManager::routeMouseReleased") << "Node released: " + node->_name;
                    // 3. Calculate local coordinates for the child
                    ofPoint localPoint = globalPoint - node->boundsMouse.getPosition();
                    bool consumed = node->handleRoutedMouseEvent(AppEventType::MOUSE_RELEASED, localPoint, button);
                    if (consumed) {
                        return; // Child handled it, stop processing.
                    }
                }
            }
            // No child consumed it, Panel handles it (optional)
            // ofLogNotice("Panel " + id) << "Panel itself was pressed.";
            // Start dragging panel? Publish PANEL_PRESSED? Set internal state?

        } catch (const std::bad_any_cast& e) {
             ofLogError("NfNodeManager::routeMouseReleased") << "Bad payload cast for MOUSE_RELEASED";
        }
}

void NfNodeManager::routeMouseDragged(const Event& e) {
    try {
        auto coords = std::any_cast<std::tuple<int, int, int>>(e.payload);
        ofPoint globalPoint(std::get<0>(coords), std::get<1>(coords));
        int button = std::get<2>(coords);

        // Iterate children in reverse (topmost first)
        for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
            auto& node = *it;
            if (node->boundsMouse.inside(globalPoint)) {
                ofLogNotice("NfNodeManager::routeMouseDragged") << "Node dragged: " + node->_name;
                // Calculate local coordinates for the child
                ofPoint localPoint = globalPoint - node->boundsMouse.getPosition();
                bool consumed = node->handleRoutedMouseEvent(AppEventType::MOUSE_DRAGGED, localPoint, button);
                if (consumed) {
                    return; // Child handled it, stop processing.
                }
            }
        }
    } catch (const std::bad_any_cast& e) {
        ofLogError("NfNodeManager::routeMouseDragged") << "Bad payload cast for MOUSE_DRAGGED";
    }
}

void NfNodeManager::routeMouseMoved(const Event& e) {
    try {
        auto coords = std::any_cast<std::tuple<int, int>>(e.payload);
        ofPoint globalPoint(std::get<0>(coords), std::get<1>(coords));

        // Iterate children in reverse (topmost first)
        for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
            auto& node = *it;
            if (node->boundsMouse.inside(globalPoint)) {
                // Calculate local coordinates for the child
                ofPoint localPoint = globalPoint - node->boundsMouse.getPosition();
                bool consumed = node->handleRoutedMouseEvent(AppEventType::MOUSE_MOVED, localPoint, 0);
                if (consumed) {
                    return; // Child handled it, stop processing.
                }
            }
        }
    } catch (const std::bad_any_cast& e) {
        ofLogError("NfNodeManager::routeMouseMoved") << "Bad payload cast for MOUSE_MOVED";
    }
}

void NfNodeManager::routeMouseScrolled(const Event& e) {
    try {
        auto scrollData = std::any_cast<std::tuple<int, int, float, float>>(e.payload);
        ofPoint globalPoint(std::get<0>(scrollData), std::get<1>(scrollData));
        float scrollX = std::get<2>(scrollData);
        float scrollY = std::get<3>(scrollData);

        // Iterate children in reverse (topmost first)
        for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
            auto& node = *it;
            if (node->boundsMouse.inside(globalPoint)) {
                ofLogNotice("NfNodeManager::routeMouseScrolled") << "Node scrolled: " + node->_name;
                // Calculate local coordinates for the child
                ofPoint localPoint = globalPoint - node->boundsMouse.getPosition();
                // We need to extend the handleRoutedMouseEvent method to handle scroll events, 
                // but for now just passing 0 as button to maintain compatibility
                bool consumed = node->handleRoutedMouseEvent(AppEventType::MOUSE_SCROLLED, localPoint, 0);
                if (consumed) {
                    return; // Child handled it, stop processing.
                }
            }
        }
    } catch (const std::bad_any_cast& e) {
        ofLogError("NfNodeManager::routeMouseScrolled") << "Bad payload cast for MOUSE_SCROLLED";
    }
}

void NfNodeManager::routeKeyPressed(const Event& e) {
    try {
        int key = std::any_cast<int>(e.payload);
        
        // Find focused node and send key event to it
        for (auto& node : nodes) {
            if (node->nodeIsFocused) {
                ofLogNotice("NfNodeManager::routeKeyPressed") << "Key pressed to focused node: " + node->_name;
                bool consumed = node->handleRoutedKeyEvent(AppEventType::KEY_PRESSED, key);
                if (consumed) {
                    return; // Node handled it, stop processing
                }
            }
        }
        
        // Also check modal nodes if any
        for (auto& node : modalNodes) {
            if (node->nodeIsFocused) {
                bool consumed = node->handleRoutedKeyEvent(AppEventType::KEY_PRESSED, key);
                if (consumed) {
                    return;
                }
            }
        }
    } catch (const std::bad_any_cast& e) {
        ofLogError("NfNodeManager::routeKeyPressed") << "Bad payload cast for KEY_PRESSED";
    }
}

void NfNodeManager::routeKeyReleased(const Event& e) {
    try {
        int key = std::any_cast<int>(e.payload);
        
        // Find focused node and send key event to it
        for (auto& node : nodes) {
            if (node->nodeIsFocused) {
                ofLogNotice("NfNodeManager::routeKeyReleased") << "Key released to focused node: " + node->_name;
                bool consumed = node->handleRoutedKeyEvent(AppEventType::KEY_RELEASED, key);
                if (consumed) {
                    return; // Node handled it, stop processing
                }
            }
        }
        
        // Also check modal nodes if any
        for (auto& node : modalNodes) {
            if (node->nodeIsFocused) {
                bool consumed = node->handleRoutedKeyEvent(AppEventType::KEY_RELEASED, key);
                if (consumed) {
                    return;
                }
            }
        }
    } catch (const std::bad_any_cast& e) {
        ofLogError("NfNodeManager::routeKeyReleased") << "Bad payload cast for KEY_RELEASED";
    }
}

} // namespace nfUI
