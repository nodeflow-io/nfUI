//
//  NfTextInputField.hpp
//  nodeflowUI
//
//  modified by Matthias Strohmaier on 22.02.24 using ofxTextInputField as a base
//  ofxTextInputField was created by Elliot Woods on 09/12/2011.
//  Copyright 2011 Kimchi and Chips.
//
//  modified by James George 12/2/2011
//  modified by Momo the Monster 7/10/2012
//  swappable fonts added by James George 9/11/2012
//
//    MIT license
//    http://www.opensource.org/licenses/mit-license.php

#ifndef NfTextInputField_hpp
#define NfTextInputField_hpp

#include "ofMain.h"
#include "NfBoxxer.hpp"

//For lack of a type abstraction, this lets you #define a font renderer so
//(like ofxFTGL or ofxFont)
//to use ofxFTGL use somethinglike this:
//#define OFX_TEXTFIELD_FONT_RENDERER ofxFTGLFont
//#define OFX_TEXTFIELD_FONT_RENDERER "ofxFTGLFont.h"

#ifndef OFX_TEXTFIELD_FONT_RENDERER
#define OFX_TEXTFIELD_FONT_RENDERER ofTrueTypeFont
#endif

#ifdef OFX_TEXTFIELD_FONT_INCLUDE
#include OFX_TEXTFIELD_FONT_INCLUDE
#endif

#define TEXTFIELD_IS_ACTIVE "textfieldIsActive"
#define TEXTFIELD_IS_INACTIVE "textfieldIsInactive"

#ifdef OF_VERSION_MINOR
#if OF_VERSION_MINOR>=8 || OF_VERSION_MAJOR>0
#define USE_GLFW_CLIPBOARD

#endif
#endif
// TODO: wrapping
#include "ofxTextInputFieldFontRenderer.h"
#include <unordered_map>
#include <unordered_set>  // Make sure to include this header

namespace nfUI {

class NfTextInputField : public NfBoxxer {
    
protected:
    bool _firstRender = true; // Flag to track if draw() was called for the first time
    uint32_t verticalTextOffset; // font size dependant
    uint32_t horizontalTextOffset;
    
    // from ofxTextinput -------------------
    float lastTimeCursorMoved;
    int VERTICAL_PADDING;
    int HORIZONTAL_PADDING;
    ofxTextInput::FontRenderer* fontRef;
    
    bool    isEnabled;
    bool    isEditing;
    bool    mouseDownInRect;
    void    mousePressed(ofMouseEventArgs& args);
    void    mouseDragged(ofMouseEventArgs& args);
    void    mouseReleased(ofMouseEventArgs& args);
    
    
    //int getLineForPosition(int pos);
    
    //void setCursorPositionFromXY();
    //void setCursorFromMouse(int x, int y);
    //void setCursorXYFromPosition();
    void getCursorCoords(int pos, int &cursorX, int &cursorY);
    int getCursorPositionFromMouse(int x, int y);
    
    bool isShifted, isCommand;
    map<int, char> shiftMap;
    ofColor colorBackground = {255,0,0,255};
    
public:
    // Inherit NfBoxxer constructor
    using NfBoxxer::NfBoxxer;
    
    // ...
    virtual ~NfTextInputField();
    //swap in a font!
    void setFont(OFX_TEXTFIELD_FONT_RENDERER& font);
    void init();
    void setup();
    
    void enable();
    void disable();
    bool getIsEnabled();
    
    bool getIsEditing();
    void beginEditing();
    void endEditing();
    
    //can be set manually or otherwise is controlled by enable/disable
    bool drawCursor;
    
    // ofRectangle bounds;
    ofRectangle position;
    
    void draw() override;
    void drawText();
    void clear();
    
    
    int cursorPosition;
    
    int selectionBegin;
    int selectionEnd;
    bool selecting;
    
    ofEvent<string> textChanged;
    void keyPressed(ofKeyEventArgs &a);
    void keyReleased(ofKeyEventArgs &a);
    
    bool autoClear;
    bool autoTab;
    
    bool multiline;
    
#ifdef USE_GLFW_CLIPBOARD
    void setClipboard(string clippy);
    string getClipboard();
#endif
    
    bool isValidChar(nfAPI::ValueType valueType, char inputChar);
    
};

}

#endif /* NfTextInputField_hpp */
