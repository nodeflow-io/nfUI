
# nodeFlowUI Changelog

## Version 0.0.8 - April 2025
### Features & Enhancements
- **Selection Component**  
  - Added new `NFSelection` component and stub implementation.  
  - Integrated selection into `NFValue`.  
  - Implemented click-and-release handling for selection.  
  - Updated `NFSelection` with latest improvements.  

- **Event Handling Improvements**  
  - Introduced hierarchical event managing system (initial implementation).  
  - Switched actions to trigger on mouse release instead of press.  
  - Toggle switches now activate on release instead of press.  
  - Close all open dropdowns when a mouse click is not handled by the component.  
  - Decoupled UI component rendering from event handling calculations.  
  - Standardized all event handlers to use global coordinates.  

- **UI & Visual Updates**  
  - Changed focus color for selection.  
  - Added cursor style handling.  
  - Revamped drawing updates and `mouseBounds` calculation.  
  - Updated `NfLabel` to respect border size.  
  - Position values in inspector now update when widget position changes.  
  - `NodeManager`: Adding a node now updates the focus.  

### Code Cleanup
- Removed old modal handlers.  
- Eliminated unused code.  
- Removed debug output.  

### Minor Changes
- Various small tweaks and improvements.  

---

## Version 0.0.7 - f0007-refactoring
### Code Cleanup
- Performed code refactoring 
- Added include paths for VS Code.  
- Sorted sources in Xcode.  

---

## Version 0.0.6
*No changes recorded; version skipped in provided data.*

---

## Version 0.0.5 - f0005-refactor
### Features & Enhancements
- Added `NodeManager` and `EventManager`.  
- Introduced events for focusing nodes (focused nodes are rendered in the foreground).  
- Added GUI events to display the active node in the status bar (text 3).  
- Added configuration option to display FPS in the status bar.  
- Implemented `F3` key to toggle FPS display in the status bar.  
- Added `NfToggleSwitch` component.  
- Integrated toggle switches into the UI demo (options: show grid, show status bar, show FPS).  

---

## Version 0.0.4 - f0004-inspector
### Features & Enhancements
- Added `NodeManager`.  
- Introduced a property inspector widget for nodes.  
- Enhanced UI interactions:  
  - Button hover colors (text & background).  
  - Label hover colors (text & background).  
  - Panel hover colors (text & background).  
  - Text input focus color (background).  
- Added drag-and-drop functionality for labels.  
- Included demo animation in `/docs` and `README.md`.  

---

## Version 0.0.3 - f0003-boxxer
### Features & Enhancements
- Introduced a simple box rendering engine (`boxxer`).  

---

## Version 0.0.2 - f0002-button
### Features & Enhancements
- Added button functionality with configuration options.  
- Implemented status bar.  

---

## Version 0.0.1 - f0001-textinput
### Features & Enhancements
- Added basic text input functionality.  

---