//
//  GUIParams.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 17.02.24.
//

#ifndef GUIParams_hpp
#define GUIParams_hpp

#include "ofMain.h"

class GUIParams {
public:
    
    GUIParams() :
        _showStatusBar(true),
        _statusBarHeight(30),
        _statusBarColor(ofColor::grey),
        _statusBarTextColor(ofColor::yellow),
        _showGrid(true),
        _gridSize(10),
        _majorStep(100),
        _minorStep(10),
        _majorGridColor(255),
        _minorGridColor(200),
        _scalingFactor(1.0f)
        
    {}
    
    // Getter and setter for showStatusBar
    bool getShowStatusBar() const {
        return _showStatusBar;
    }

    void setShowStatusBar(bool show) {
        _showStatusBar = show;
    }

    // Getter and setter for statusBarHeight
    uint32_t getStatusBarHeight() const {
        return _statusBarHeight;
    }

    void setStatusBarHeight(uint32_t height) {
        _statusBarHeight = height;
    }

    // Getter and setter for statusBarColor
    const ofColor& getStatusBarColor() const {
        return _statusBarColor;
    }

    void setStatusBarColor(const ofColor& color) {
        _statusBarColor = color;
    }
    
    // Getter and setter for statusBarTextColor
    const ofColor& getStatusBarTextColor() const {
        return _statusBarTextColor;
    }

    void setStatusBarTextColor(const ofColor& color) {
        _statusBarTextColor = color;
    }
    
    // Getter and setter for showGrid
    bool getShowGrid() const {
        return _showGrid;
    }
    
    void setShowGrid(bool show) {
        _showGrid = show;
    }
    
    // Getter and setter for gridSize
    uint32_t getGridSize() const {
        return _gridSize;
    }
    
    void setGridSize(uint32_t size) {
        _gridSize = size;
    }
    
    // Getter and setter for majorStep
    uint32_t getMajorStep() const {
        return _majorStep;
    }
    
    void setMajorStep(uint32_t size) {
        _majorStep = size;
    }
    
    // Getter and setter for minorStep
    uint32_t getMinorStep() const {
        return _minorStep;
    }
    
    void setMinorStep(uint32_t size) {
        _minorStep = size;
    }
    
    // Getter and setter for gridColor
    const ofColor& getMajorGridColor() const {
        return _majorGridColor;
    }
    
    void setMajorGridColor(const ofColor& color) {
        _majorGridColor = color;
    }
    
    const ofColor& getMinorGridColor() const {
        return _minorGridColor;
    }
    
    void setMinorGridColor(const ofColor& color) {
        _minorGridColor = color;
    }
    
    const double getScalingFactor() const {
        return _scalingFactor;
    }
    
    void setScalingFactor(const double& scalingFactor) {
        _scalingFactor = scalingFactor;
    }
    
    // Statusbar parameters
    bool _showStatusBar;
    uint32_t _statusBarHeight;
    ofColor _statusBarColor;
    ofColor _statusBarTextColor;
    
    // Grid parameters
    bool _showGrid;
    uint32_t _gridSize;
    uint32_t _majorStep;
    uint32_t _minorStep;
    ofColor _majorGridColor;
    ofColor _minorGridColor;
    double _scalingFactor;
    
};

#endif /* GUIParams_hpp */
