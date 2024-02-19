
# nodeFlowUI v.0.0.2

# Components 

## textinput field
### TODO
- respect input type (double, int, bool, hex, ...) when entering text
- add the multiline feature
- implement redndering of text selection colors (text, selection)
- display * for password input

## button
### TODO
- focus onMouseover (instead of click and release)


## UI Element Properties
### implemeted a DOM like representation
```
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
std::string text;
ofRectangle bounds;
```

## Offsets
```
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

