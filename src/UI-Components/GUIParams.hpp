//
//  GUIParams.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 17.02.24.
//

#ifndef GUIParams_hpp
#define GUIParams_hpp

// Standard library includes
#include <string>

// Project includes
#include "ofMain.h"

class GUIParams {
public:
    // Constructor
    GUIParams();
    
    // Getter and setter for showStatusBar
    bool getShowStatusBar() const;
    void setShowStatusBar(bool show);

    // Getter and setter for statusBarHeight
    uint32_t getStatusBarHeight() const;
    void setStatusBarHeight(uint32_t height);

    // Getter and setter for statusBarColor
    const ofColor& getStatusBarColor() const;
    void setStatusBarColor(const ofColor& color);
    
    // Getter and setter for statusBarTextColor
    const ofColor& getStatusBarTextColor() const;
    void setStatusBarTextColor(const ofColor& color);
    
    // Getter and setter for showGrid
    bool getShowGrid() const;
    void setShowGrid(bool show);
    
    // Getter and setter for gridSize
    uint32_t getGridSize() const;
    void setGridSize(uint32_t size);
    
    // Getter and setter for majorStep
    uint32_t getMajorStep() const;
    void setMajorStep(uint32_t size);
    
    // Getter and setter for gridColor
    const ofColor& getMajorGridColor() const;
    void setMajorGridColor(const ofColor& color);
    
    // Getter and setter for minorGridColor
    const ofColor& getMinorGridColor() const;
    void setMinorGridColor(const ofColor& color);
    
    // Getter and setter for scalingFactor
    const double getScalingFactor() const;
    void setScalingFactor(const double& scalingFactor);
    
    // Getter and setter for statusBarText1
    const std::string& getStatusBarText1() const;
    void setStatusBarText1(const std::string& statusBarText);
    
    // Getter and setter for statusBarText2
    const std::string& getStatusBarText2() const;
    void setStatusBarText2(const std::string& statusBarText);
    
    // Getter and setter for statusBarText3
    const std::string& getStatusBarText3() const;
    void setStatusBarText3(const std::string& statusBarText);
    
    // Getter and setter for showFPS
    const bool getShowFPS() const;
    void setShowFPS(const bool showFPS);

private:
    bool _showStatusBar;
    uint32_t _statusBarHeight;
    ofColor _statusBarColor;
    ofColor _statusBarTextColor;
    std::string _statusBarText1;
    std::string _statusBarText2;
    std::string _statusBarText3;
    bool _showGrid;
    uint32_t _gridSize;
    uint32_t _majorStep;
    ofColor _majorGridColor;
    ofColor _minorGridColor;
    double _scalingFactor;
    bool _showFPS;
};

#endif /* GUIParams_hpp */
