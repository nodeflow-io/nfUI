# nodeFlowUI v.0.0.3

# Demo UI

## Status Bar
- Text1
- Text2
- Hints - TODO add to config
- FPS - TODO add to config

## Components Panel

- Show Grid (Bool)
- Grid Size (Int)
- Major Step (Int)
- Status Text1 (String)
- Status Text2 (String)
- Password (String)
- Button (String)

# GUI Parameters

```(cpp)
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
        _majorGridColor(255),
        _minorGridColor(200),
        _scalingFactor(1.2f),
        _statusBarText1("nodeFlowUI"),
        _statusBarText2("vx.x.x")
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
    
    // Getter and setter for scalingFactor
    const double getScalingFactor() const {
        return _scalingFactor;
    }
    
    void setScalingFactor(const double& scalingFactor) {
        _scalingFactor = scalingFactor;
    }
    
    // Getter and setter for StatusbarTexts
    const std::string& getStatusBarText1() const {
        return _statusBarText1;
    }
    
    void setStatusBarText1(const std::string& statusBarText) {
        _statusBarText1 = statusBarText;
    }

    const std::string& getStatusBarText2() const {
        return _statusBarText2;
    }
    
    void setStatusBarText2(const std::string& statusBarText) {
        _statusBarText2 = statusBarText;
    }
    

    // Statusbar parameters
    bool _showStatusBar;
    uint32_t _statusBarHeight;
    ofColor _statusBarColor;
    ofColor _statusBarTextColor;
    std::string _statusBarText1;
    std::string _statusBarText2;
    
    // Grid parameters
    bool _showGrid;
    uint32_t _gridSize;
    uint32_t _majorStep;
    ofColor _majorGridColor;
    ofColor _minorGridColor;
    double _scalingFactor;
    
};
```

## Event handlers

- Key: F1 -> toggle grid display
- Key: F2 -> toggle StatusBar display
- Button SetParams -> update GUI Parameters


# Supported UI Elements 

## textinput field
- respect input type (string, double, int, bool ...) when entering text
- added checking of maxTextLength 
- display asterisks for password input
### TODO
- add the multiline feature
- implement rendering of text selection colors (text, selection)
- add type hint (optional)
- tab handler (optiona)

## button
### TODO
- focus onMouseover (instead of click and release)


## UI Element Properties
### implemeted a DOM like representation
```(cpp)
ofParameterGroup parameters;
ofParameter<ofColor> backgroundColor;
ofParameter<ofColor> textColor;
ofParameter<ofColor> borderColor;
ofParameter<ofColor> focusColor;
ofParameter<ofColor> focusBackgroundColor;
Offsets padding;
Offsets margin;
ofParameter<float> borderSize;
ofParameter<float> width;
ofParameter<float> height;
ofParameter<float> minWidth;
ofParameter<float> minHeight;
ofParameter<float> maxWidth;
ofParameter<float> maxHeight;
ofParameter<bool> isFocused;
ofParameter<bool> isVisible;
ofParameter<uint32_t> maxTextLength;
std::string text;
ofParameter<bool> textIsPassword;
ofRectangle bounds;
```

## Offsets
```(cpp)
ofParameterGroup parameters;
ofParameter<float> top;
ofParameter<float> right;
ofParameter<float> bottom;
ofParameter<float> left;
```

### TODO
- implement configuration of text selection color
- in inspect view render margins and paddings like in a browser inspect view

# Features Roadmap

## Boxxer - the box rendering engine
### a recursive box render model

## GUI help pane

# Changelog

- 0.0.1 f0001-textinput: basic text input
- 0.0.2 f0002-button: buttons, configuration, statusbar
- 0.0.3 f0002-boxxer:

