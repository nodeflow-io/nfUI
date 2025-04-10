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
#include "NfEventManager.hpp"

namespace nfUI {

class NfNodeManager {
private:
    std::vector<std::shared_ptr<NfBoxxer>> nodes;
    std::vector<std::shared_ptr<NfBoxxer>> modalNodes;
    using ListenerID = size_t; // Unique identifier for listeners

public:
    NfNodeManager();
    
    // Node management
    void addNode(std::shared_ptr<NfBoxxer> node);
    void addModalNode(std::shared_ptr<NfBoxxer> node);
    bool removeNode(const std::string& name);
    bool removeModalNode(const std::string& name);
    
    // Drawing
    void drawNodes();
    
    // Focus management
    bool focusNode(const std::string& name);
    bool unfocusAll();
    bool focusInCollection(std::vector<std::shared_ptr<NfBoxxer>>& collection, const std::string& name);
    
    // Modal management
    void requestModalNode(std::shared_ptr<NfBoxxer> requestingNode, NfModalType modalType, NfUIConfig config, std::string name);
    void closeModalNode(const std::string& modalNodeName);
    std::shared_ptr<NfBoxxer> getModalNodeByName(const std::string& modalNodeName);
};

// Declaration only
extern NfNodeManager g_nodeManager;

} // namespace nfUI

#endif /* NfNodeManager_hpp */
