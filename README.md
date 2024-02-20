# nodeFlowUI v.0.0.2

# Demo UI

## Show Grid (Bool)
## Grid Size (Int)
## Major Step (Int)
## Minor Step (Int)
## Status Text (String)
## Password (String)
## Button (String)

# Supported UI Elements 

## textinput field
- respect input type (string, double, int, bool ...) when entering text
- added checking of maxTextLength 
- display asterisks for password input
### TODO
- add the multiline feature
- implement rendering of text selection colors (text, selection)

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
## GUI config: status bar string & stats as methods for projects using nfGUI

