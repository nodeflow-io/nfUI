//
//  NfNodeManager.cpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 26.02.24.
//

#include "NfNodeManager.hpp"
#include "NfEventBus.hpp"

namespace nfUI {

// Forward declaration of helper function
void closeDropdownsInNode(NfBoxxer* node);

// Global instance definition
NfNodeManager g_nodeManager;

// Constructor
NfNodeManager::NfNodeManager() {
    // Subscribe to node focus events
    nfUI::NfEventManager::getEventManager().subscribe("node_focus", [this](const std::string& nodeName) {
        this->focusNode(nodeName);
    });

    // We'll set up the event bus subscriptions, but the actual OF event listeners
    // will be initialized later when the window is ready
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
    // Clear regular nodes
    nodes.clear();
    // Unsubscribe from all events
    // nfUI::NfEventManager::getEventManager().unsubscribeAll(this);
    BUS.unsubscribeAll(this);
}

// Node management
void NfNodeManager::addNode(std::shared_ptr<NfBoxxer> node) {
    nodes.push_back(node);
    focusNode(node->_name); // Focus the newly added node
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

// Drawing
void NfNodeManager::drawNodes() {
    // Draw regular nodes first
    for (auto& node : nodes) {
        node->draw();
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

    return found; // Return true if any node was found and focused
}

bool NfNodeManager::unfocusAll() {
    for (auto& node : nodes) {
        node->nodeIsFocused = false;
        node->parameters.getBool("IsFocused") = false;
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


// --- Event Bus ---

void NfNodeManager::routeMousePressed(const Event& e) {
    // ofLogNotice("NfNodeManager") << "Received mouse press event";
    try {
        auto args = e.payload_as<ofMouseEventArgs>();
        ofPoint globalPoint(args.x, args.y);
        // ofLogNotice("NfNodeManager") << "Processing mouse press at: " << args.x << "," << args.y;
        
        bool floatingElementHandledEvent = false;
        
        // First check for floating elements like open dropdowns
        for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
            auto& node = *it;
            bool consumed = node->routeEventToFloatingElements(AppEventType::MOUSE_PRESSED, globalPoint, args.button);
            if (consumed) {
                floatingElementHandledEvent = true;
                break;
            }
        }
        
        // If no floating element handled it, close all open dropdowns
        if (!floatingElementHandledEvent) {
            closeAllDropdowns();
        }
        
        // If no floating element handled it, proceed with normal event flow
        // Iterate children in reverse (topmost first)
        for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
            auto& node = *it;
            if (node->boundsMouse.inside(globalPoint)) {
                // ofLogNotice("NfNodeManager::routeMousePressed") << "Node pressed: " + node->_name;
                // Use globalPoint instead of localPoint
                bool consumed = node->handleRoutedMouseEvent(AppEventType::MOUSE_PRESSED, globalPoint, args.button);
                if (consumed) {
                    return;
                }
            }
        }
    } catch (const std::bad_any_cast& e) {
        ofLogError("NfNodeManager::routeMousePressed") << "Bad payload cast for MOUSE_PRESSED";
    }
}

void NfNodeManager::routeMouseReleased(const Event& e) {
    try {
        auto args = e.payload_as<ofMouseEventArgs>();
        ofPoint globalPoint(args.x, args.y);
        // ofLogNotice("NfNodeManager") << "Processing mouse release at: " << args.x << "," << args.y;
        
        bool floatingElementHandledEvent = false;
        
        // First check for floating elements like open dropdowns
        for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
            auto& node = *it;
            bool consumed = node->routeEventToFloatingElements(AppEventType::MOUSE_RELEASED, globalPoint, args.button);
            if (consumed) {
                floatingElementHandledEvent = true;
                break;
            }
        }
        
        // If no floating element handled it, proceed with normal event flow
        // Iterate children in reverse (topmost first)
        for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
            auto& node = *it;
            if (node->boundsMouse.inside(globalPoint)) {
                // ofLogNotice("NfNodeManager::routeMouseReleased") << "Node released: " + node->_name;
                bool consumed = node->handleRoutedMouseEvent(AppEventType::MOUSE_RELEASED, globalPoint, args.button);
                if (consumed) {
                    return;
                }
            }
        }
    } catch (const std::bad_any_cast& e) {
        ofLogError("NfNodeManager::routeMouseReleased") << "Bad payload cast for MOUSE_RELEASED";
    }
}

void NfNodeManager::routeMouseDragged(const Event& e) {
    try {
        auto args = e.payload_as<ofMouseEventArgs>();
        ofPoint globalPoint(args.x, args.y);

        // First check for floating elements like open dropdowns
        for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
            auto& node = *it;
            bool consumed = node->routeEventToFloatingElements(AppEventType::MOUSE_DRAGGED, globalPoint, args.button);
            if (consumed) {
                return;
            }
        }

        // Iterate children in reverse (topmost first)
        for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
            auto& node = *it;
    
            // ofLogNotice("NfNodeManager::routeMouseDragged") << "Node dragged: " + node->_name;
            bool consumed = node->handleRoutedMouseEvent(AppEventType::MOUSE_DRAGGED, globalPoint, args.button);
            if (consumed) {
                return;
            }
            
        }
    } catch (const std::bad_any_cast& e) {
        ofLogError("NfNodeManager::routeMouseDragged") << "Bad payload cast for MOUSE_DRAGGED";
    }
}

void NfNodeManager::routeMouseMoved(const Event& e) {
    try {
        auto args = e.payload_as<ofMouseEventArgs>();
        ofPoint globalPoint(args.x, args.y);

        // First check for floating elements like open dropdowns
        for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
            auto& node = *it;
            bool consumed = node->routeEventToFloatingElements(AppEventType::MOUSE_MOVED, globalPoint, args.button);
            if (consumed) {
                return;
            }
        }

        // Iterate children in reverse (topmost first)
        for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
            auto& node = *it;
            // ofLogNotice("NfNodeManager::routeMouseMoved") << "Node mouseover: " + node->_name;
            bool consumed = node->handleRoutedMouseEvent(AppEventType::MOUSE_MOVED, globalPoint, args.button);
            if (consumed) {
                return;
            }
            
        }
    } catch (const std::bad_any_cast& e) {
        ofLogError("NfNodeManager::routeMouseMoved") << "Bad payload cast for MOUSE_MOVED";
    }
}

void NfNodeManager::routeMouseScrolled(const Event& e) {
    try {
        auto args = e.payload_as<ofMouseEventArgs>();
        ofPoint globalPoint(args.x, args.y);

        // Iterate children in reverse (topmost first)
        for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
            auto& node = *it;
            if (node->boundsMouse.inside(globalPoint)) {
                // ofLogNotice("NfNodeManager::routeMouseScrolled") << "Node scrolled: " + node->_name;
                // Pass scrollX and scrollY through the button parameter for now
                bool consumed = node->handleRoutedMouseEvent(AppEventType::MOUSE_SCROLLED, globalPoint, args.button);
                if (consumed) {
                    return;
                }
            }
        }
    } catch (const std::bad_any_cast& e) {
        ofLogError("NfNodeManager::routeMouseScrolled") << "Bad payload cast for MOUSE_SCROLLED";
    }
}

void NfNodeManager::routeKeyPressed(const Event& e) {
    try {
        auto args = e.payload_as<ofKeyEventArgs>();
        
        // Find focused node and send key event to it
        for (auto& node : nodes) {
            if (node->nodeIsFocused) {
                //ofLogNotice("NfNodeManager::routeKeyPressed") << "Key pressed to focused node: " + node->_name;
                bool consumed = node->handleRoutedKeyEvent(AppEventType::KEY_PRESSED, args.key);
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
        auto args = e.payload_as<ofKeyEventArgs>();
        
        // Find focused node and send key event to it
        for (auto& node : nodes) {
            if (node->nodeIsFocused) {
                // ofLogNotice("NfNodeManager::routeKeyReleased") << "Key released to focused node: " + node->_name;
                bool consumed = node->handleRoutedKeyEvent(AppEventType::KEY_RELEASED, args.key);
                if (consumed) {
                    return;
                }
            }
        }
        
    } catch (const std::bad_any_cast& e) {
        ofLogError("NfNodeManager::routeKeyReleased") << "Bad payload cast for KEY_RELEASED";
    }
}

void NfNodeManager::closeAllDropdowns() {
    // Iterate through all nodes and find all open dropdowns
    for (auto& node : nodes) {
        // Recursively visit all children of each node
        closeDropdownsInNode(node.get());
    }
}

// Helper function to recursively close dropdowns in node hierarchy
void closeDropdownsInNode(NfBoxxer* node) {
    // Check if this is a selection with an open dropdown
    auto selection = dynamic_cast<NfSelection*>(node);
    if (selection && selection->_isDropdownOpen) {
        selection->_isDropdownOpen = false;
    }
    
    // Recursively check children
    for (auto& child : node->children) {
        auto childBoxer = dynamic_cast<NfBoxxer*>(child.get());
        if (childBoxer) {
            closeDropdownsInNode(childBoxer);
        }
    }
}

} // namespace nfUI
