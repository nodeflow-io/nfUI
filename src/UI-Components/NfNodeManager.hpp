//
//  NfNodeManager.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 26.02.24.
//

#pragma once

#include <vector>
#include <memory>
#include "NfBoxxer.hpp"
#include "NfEventManager.hpp"
#include "NfEventBus.hpp"
#include "ofEvents.h"
#include "NfSelection.hpp"

namespace nfUI {

class NfNodeManager {
private:
    std::vector<std::shared_ptr<NfBoxxer>> nodes;
    using ListenerID = size_t; // Unique identifier for listeners

    // Event handling
    void routeMousePressed(const Event& e);
    void routeMouseReleased(const Event& e);
    void routeMouseDragged(const Event& e);
    void routeMouseMoved(const Event& e);
    void routeMouseScrolled(const Event& e);
    void routeKeyPressed(const Event& e);
    void routeKeyReleased(const Event& e);
    

public:
    NfNodeManager();
    ~NfNodeManager(); // Destructor
    
    // Node management
    void addNode(std::shared_ptr<NfBoxxer> node);
    bool removeNode(const std::string& name);
    
    // Drawing
    void drawNodes();
    
    // Focus management
    bool focusNode(const std::string& name);
    bool unfocusAll();
    bool focusInCollection(std::vector<std::shared_ptr<NfBoxxer>>& collection, const std::string& name);
    
    // Selection management
    void closeAllDropdowns();
};

// Declaration only
extern NfNodeManager g_nodeManager;

} // namespace nfUI
