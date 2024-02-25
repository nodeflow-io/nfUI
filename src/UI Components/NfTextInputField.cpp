//
//  NfTextInputField.cpp
//  nodeflowUI
//
//  Co-Created by Matthias Strohmaier on 22.02.24.
//  originally Created by Elliot Woods on 09/12/2011.
//  Copyright 2011 Kimchi and Chips.
//
//  modified by James George 12/2/2011
//  modified by Momo the Monster 7/10/2012
//  swappable fonts added by James George 9/11/2012
//  removed some depreceated drawing calls - Matthias Strohmaier 2/14/2024
//  added input filtering for keys - Matthias Strohmaier 2/19/2024
//  TODO: plattform agnostic keys - shift mapps

#include "NfTextInputField.hpp"

namespace nfUI {
// init variables
void NfTextInputField::init() {
    ofLogVerbose("NfTextInputField::init()");

    shiftMap[44] = '<';
    shiftMap[45] = '_';
    shiftMap[46] = '>';
    shiftMap[48] = ')';
    shiftMap[49] = '!';
    shiftMap[50] = '@';
    shiftMap[51] = '#';
    shiftMap[52] = '$';
    shiftMap[53] = '%';
    shiftMap[54] = '^';
    shiftMap[55] = '&';
    shiftMap[56] = '*';
    shiftMap[57] = '(';
    shiftMap[61] = '+';
    shiftMap[63] = '/';
    shiftMap[91] = '{';
    shiftMap[92] = '|';
    shiftMap[93] = '}';
    shiftMap[96] = '~';
    
    text = "";
    multiline = false;
    autoTab = true;
    cursorPosition = 0;
    selectionBegin = 0;
    selectionEnd = 0;
    selecting = false;
    
    
    fontRef = NULL;
    isEnabled = false;
    isEditing = false;
    // bounds = ofRectangle(0,0,100,22);
    
    drawCursor = false;
    autoClear = false;
    mouseDownInRect = false;
    
    fontRef = new ofxTextInput::BitmapFontRenderer();
    //isSetup = false;
    
    VERTICAL_PADDING = 3;
    HORIZONTAL_PADDING = 3;
    lastTimeCursorMoved = ofGetElapsedTimef();
}



NfTextInputField::~NfTextInputField(){
    if(isEnabled){
        disable();
    }
    
}

void NfTextInputField::setup(){
    enable();
}


void NfTextInputField::enable(){
    if(!isEnabled){
        ofAddListener(ofEvents().mousePressed, this, &NfTextInputField::mousePressed);
        ofAddListener(ofEvents().mouseDragged, this, &NfTextInputField::mouseDragged);
        ofAddListener(ofEvents().mouseReleased, this, &NfTextInputField::mouseReleased);
        isEnabled = true;
    }
}

void NfTextInputField::disable(){
    if(isEditing){
        endEditing();
    }
    if(isEnabled){
        ofRemoveListener(ofEvents().mousePressed, this, &NfTextInputField::mousePressed);
        ofRemoveListener(ofEvents().mouseDragged, this, &NfTextInputField::mouseDragged);
        ofRemoveListener(ofEvents().mouseReleased, this, &NfTextInputField::mouseReleased);
        isEnabled = false;
    }
    
}

void NfTextInputField::beginEditing() {
    if(!isEditing){
        ofAddListener(ofEvents().keyPressed, this, &NfTextInputField::keyPressed);
        ofAddListener(ofEvents().keyReleased, this, &NfTextInputField::keyReleased);
        ofSendMessage(TEXTFIELD_IS_ACTIVE);
        isEditing = true;
        drawCursor = true;
        if(autoClear){
            clear();
        }
        else{
            
            
        }
    }
}

void NfTextInputField::endEditing() {
    if(isEditing){
        ofRemoveListener(ofEvents().keyPressed, this, &NfTextInputField::keyPressed);
        ofSendMessage(TEXTFIELD_IS_INACTIVE);
        ofNotifyEvent(textChanged, text, this);
        isEditing = false;
        drawCursor = false;
    }
}

void NfTextInputField::setFont(OFX_TEXTFIELD_FONT_RENDERER& font){
    if(fontRef->isBitmapFont()) {
        delete fontRef;
    }
    fontRef = new ofxTextInput::TypedFontRenderer(&font);
}

bool NfTextInputField::getIsEditing(){
    return isEditing;
}

bool NfTextInputField::getIsEnabled(){
    return isEnabled;
}

void NfTextInputField::draw() {
    this->setup();
    // this->setBounds(valuePosition);
    ofPushMatrix(); // Save the current drawing context
    NfBoxxer::draw(); // Call base class draw for common drawing code if needed
    
    // Textbox-specific drawing code here
    if (_firstRender) {
        this->init();
        if (_config.isDebug) {
            std::cout << "NfTextInputField: " << _name << std::endl;
        }
        // Init text as string from value
        NFValue* valueRawPtr = this->getValue();
        if (valueRawPtr != nullptr) {
            std::string valueAsString = valueRawPtr->toString();
            this->text = valueAsString;
        } else {
            this->text = "";
            std::cout << "NfTextInputField: " << _name << ":no value available." << std::endl;
        }
        _firstRender=false;
    }
    
    
    
    float textfieldWith = bounds.width;
    // Draw the label text
    ofSetColor(textColor.get());
    // ofDrawBitmapString(_name, _config.paddingLeft, _config.paddingTop + fontRef->getLineHeight());
    if (_config.showLabel) {
        fontRef->drawString(_name, 0, _config.paddingTop + fontRef->getLineHeight());
        textfieldWith /= 2;
        boundsMouse.width /= 2;
    }
    
    // draw the background text pannel
    if (_config.showLabel) {
        ofTranslate(textfieldWith, 0);
        translateBounds(boundsMouse, textfieldWith, 0, _name);
    }
    ofSetColor(backgroundColor.get());
    ofDrawRectangle(0,0, textfieldWith, bounds.height);
    
    ofSetColor(textColor.get());
    // Draw the text inside the textbox
    this->drawText();

    ofPopMatrix(); // Restore the drawing context
}

void NfTextInputField::drawText() {
    
    // visual debugging of hot area for the mouse
    /*
    ofPushStyle();
    ofSetHexColor(0x6988db);
    ofFill();
    ofDrawRectangle(boundsMouse);
    ofSetColor(ofColor(0,255,255));
    std::string position = ofToString(boundsMouse.x) +","+ ofToString(boundsMouse.y);
    fontRef->drawString(position, _config.paddingLeft, _config.paddingTop + fontRef->getLineHeight());
    ofPopStyle();
    */
    
    if(selecting) {
        ofPushStyle();
        // argh, splitting all the time.
        vector<string> lines = ofSplitString(text, "\n");
        int beginCursorX, beginCursorY;
        int endCursorX, endCursorY;
        getCursorCoords(selectionBegin, beginCursorX, beginCursorY);
        getCursorCoords(selectionEnd, endCursorX, endCursorY);
        
        float startX = fontRef->stringWidth(lines[beginCursorY].substr(0,beginCursorX));
        float endX = fontRef->stringWidth(lines[endCursorY].substr(0, endCursorX));
        
        ofSetHexColor(0x6988db);
        ofFill();
        
        if(beginCursorY==endCursorY) {
            // single line selection
            ofDrawRectangle(_config.paddingLeft + startX, _config.paddingTop + fontRef->getLineHeight()*beginCursorY,
                            endX - startX, fontRef->getLineHeight());
        } else {
            
            // multiline selection.
            // do first line to the end
            ofDrawRectangle(_config.paddingLeft + startX, _config.paddingTop + fontRef->getLineHeight()*beginCursorY,
                            fontRef->stringWidth(lines[beginCursorY]) - startX,
                            fontRef->getLineHeight()
                            );
            
            // loop through entirely selected lines
            for(int i = beginCursorY + 1; i < endCursorY; i++) {
                ofDrawRectangle(_config.paddingLeft, _config.paddingTop + fontRef->getLineHeight()*i,
                                fontRef->stringWidth(lines[i]),
                                fontRef->getLineHeight()
                                );
            }
            // do last line up to endX
            ofDrawRectangle(_config.paddingLeft, _config.paddingTop + fontRef->getLineHeight()*endCursorY,
                            endX, fontRef->getLineHeight()
                            );
        }
        ofPopStyle();
        
        
        //draw cursor line
    } else if(drawCursor) {
        ofPushStyle();
        // cursor should only blink when its been idle, and animation
        // should be a clipped sine wave
        float timeFrac = 0.5 * ofClamp(cos(6.0f * (ofGetElapsedTimef()-lastTimeCursorMoved))*4, -1, 1) + 0.5;
        
        ofColor col = ofGetStyle().color;
        ofSetColor(col.r * timeFrac, col.g * timeFrac, col.b * timeFrac);
        
        
        // argh, splitting all the time.
        vector<string> lines = ofSplitString(text, "\n");
        
        
        // calculate this every loop.
        int cursorX, cursorY;
        getCursorCoords(cursorPosition, cursorX, cursorY);
        //    printf("Pos: %d    X: %d   Y: %d\n", cursorPosition, cursorX, cursorY);
        int cursorPos = _config.paddingLeft + fontRef->stringWidth(lines[cursorY].substr(0,cursorX));
        
        
        int cursorTop = _config.paddingTop + fontRef->getLineHeight()*cursorY;
        int cursorBottom = cursorTop + fontRef->getLineHeight();
        
        ofSetLineWidth(1.0f);
        //TODO: multiline with fontRef
        ofDrawLine(cursorPos, cursorTop,
                   cursorPos, cursorBottom);
        ofPopStyle();
    }

    if (parameters.getBool("textIsPassword")) {
        // Generate a string of asterisks "*" with the same length as `text`
        std::string password(text.size(), '*');
        fontRef->drawString(password, _config.paddingLeft, _config.paddingTop + fontRef->getLineHeight());
    } else {
        // Draw the actual text
        
        // vertical was fontRef->getLineHeight() + VERTICAL_PADDING
        fontRef->drawString(text, _config.paddingLeft, _config.paddingTop + fontRef->getLineHeight());
    }
    
}

void NfTextInputField::getCursorCoords(int pos, int &cursorX, int &cursorY) {
    vector<string> lines = ofSplitString(text, "\n");
    
    
    int c = 0;
    
    
    for(int i = 0; i < lines.size(); i++) {
        if(pos<=c+lines[i].size()) {
            cursorY = i;
            cursorX = pos - c;
            return;
        }
        c += lines[i].size() + 1;
    }
    
}

/*
 void NfTextInputField::setCursorPositionFromXY() {
 cursorPosition = cursorx;
 vector<string> parts = ofSplitString(text, "\n");
 for(int i = 0 ; i < cursory; i++) {
 cursorPosition += parts[i].size() + i; // for carriage returns
 }
 }
 
 */
int NfTextInputField::getCursorPositionFromMouse(int x, int y) {
    int cursorX = 0;
    int cursorY = 0;
    float pos = y - boundsMouse.y - VERTICAL_PADDING;
    pos /= fontRef->getLineHeight();
    int line = pos;
    cursorY = line;
    
    vector<string> lines = ofSplitString(text, "\n");
    if(cursorY>=lines.size()-1) cursorY = lines.size()-1;
    if(lines.size()>0) {
        cursorX = fontRef->getPosition(lines[cursorY], x - HORIZONTAL_PADDING - boundsMouse.x);
    }
    int c = 0;
    for(int i = 0; i < cursorY; i++) {
        c += lines[i].size() + 1;
    }
    c += cursorX;
    return c;
}


void NfTextInputField::mousePressed(ofMouseEventArgs& args){
    mouseDownInRect = boundsMouse.inside(args.x, args.y);
    if(mouseDownInRect) {
        cursorPosition = getCursorPositionFromMouse(args.x, args.y);
        lastTimeCursorMoved = ofGetElapsedTimef();
        selecting = false;
    }
}


void NfTextInputField::mouseDragged(ofMouseEventArgs& args) {
    if(boundsMouse.inside(args.x, args.y)) {
        int pos = getCursorPositionFromMouse(args.x, args.y);
        if(pos!=cursorPosition) {
            selecting = true;
            selectionBegin = MIN(pos, cursorPosition);
            selectionEnd = MAX(pos, cursorPosition);
            
        } else {
            selecting = false;
        }
    }
}

void NfTextInputField::mouseReleased(ofMouseEventArgs& args){
    
    if(boundsMouse.inside(args.x, args.y)) {
        if(!isEditing && mouseDownInRect){
            beginEditing();
        }
    }
    else if(isEditing){
        endEditing();
    }
}





#ifdef USE_GLFW_CLIPBOARD


#if (_MSC_VER)
#include <GLFW/glfw3.h>
#else
#include "GLFW/glfw3.h"
#endif


void NfTextInputField::setClipboard(string clippy)
{
    glfwSetClipboardString( (GLFWwindow*) ofGetWindowPtr()->getCocoaWindow(), clippy.c_str());
}

string NfTextInputField::getClipboard()
{
    const char *clip = glfwGetClipboardString((GLFWwindow*) ofGetWindowPtr()->getCocoaWindow());
    if(clip!=NULL) {
        return string(clip);
    } else {
        return "";
    }
    
}

#endif

void NfTextInputField::keyPressed(ofKeyEventArgs& args) {
    //ew: add charachter (non unicode sorry!)
    //jg: made a step closer to this with swappable renderers and ofxFTGL -- but need unicode text input...
    //ms: added filtering of invalid characters for a particular type
    int key = args.key;
    char asciiChar = args.keycode;                  // Convert the key to an ASCII character
    
    std::string valueTypeString = getValueTypeString(valueType);
    
    lastTimeCursorMoved = ofGetElapsedTimef();
    std::cout << parameters.getName() << " (key pressed): " << key << " (ascii): " << asciiChar << std::endl;
    
    bool isControlKey = false;

    // Check if it's a control key
    switch (key) {
        case OF_KEY_RETURN:
        case OF_KEY_SHIFT:
        case OF_KEY_BACKSPACE:
        case OF_KEY_TAB:
        case OF_KEY_UP:
        case OF_KEY_DOWN:
        case OF_KEY_LEFT:
        case OF_KEY_RIGHT:
        case 3686:                      // OS X cmd-key
            isControlKey = true;
            break;
        // Add more cases for other control keys if needed
    }
    
    if(!isControlKey) {
        // Check if the key is valid for the type
        if (isValidChar(valueType, static_cast<char>(asciiChar))) {
            std::cout << "Character '" << asciiChar << "' is valid for " << valueTypeString << "." << std::endl;
        } else {
            std::cout << "Character '" << asciiChar << "' is NOT valid for " << valueTypeString << "." << std::endl;
            return;
        }
        // check size of Textfield
        if (text.size() < parameters.getInt("maxTextLength")) {
            // add key to text
        } else {
            return;
        }
    }

    
    if(key == OF_KEY_SHIFT) {
        isShifted = true;
    }
    
    if(key == 3686) {               // windows = 4352
        isCommand = true;
    }
    
#ifdef USE_GLFW_CLIPBOARD
    if(key == 'c' && isCommand ) {
        setClipboard(text.substr(selectionBegin, selectionEnd - selectionBegin));
        return;
    }
    
    if(key == 'v' && isCommand ) {
        text.insert(cursorPosition, getClipboard());
        return;
    }
#endif
    
    if ((key >=32 && key <=126) || key=='\t' || key==OF_KEY_RETURN) {
        if(selecting) {
            text.erase(text.begin() + selectionBegin,
                       text.begin() + selectionEnd
                       );
            cursorPosition = selectionBegin;
            selecting = false;
        }
    }
    
    
    if (key == OF_KEY_RETURN) {
        if(!multiline) {
            endEditing();
            return;
        }
        text.insert(text.begin()+cursorPosition, '\n');
        cursorPosition++;
        
        
        if(autoTab) {
            // how much whitespace is there on the previous line?
            int xx, yy;
            getCursorCoords(cursorPosition, xx, yy);
            vector<string> lines = ofSplitString(text, "\n");
            if(yy>0) {
                
                // collect all the whitespace on the previous line.
                string previousWhitespace = "";
                string previousLine = lines[yy-1];
                int pos = 0;
                for(int i = 0; i < previousLine.size(); i++) {
                    if(previousLine[i]==' ' || previousLine[i]=='\t') {
                        previousWhitespace += previousLine[i];
                    } else {
                        break;
                    }
                }
                // if we have a curly brace as the last char on the previous line
                // increase the indentation
                if(previousLine[previousLine.size()-1]=='{') {
                    if(previousWhitespace=="") {
                        previousWhitespace = "\t";
                    } else {
                        previousWhitespace += previousWhitespace[previousWhitespace.size()-1];
                    }
                }
                text = text.insert(cursorPosition, previousWhitespace);
                cursorPosition += previousWhitespace.size();
            }
        }
        
        return;
    }
    
    if ((key >=32 && key <=126) || key=='\t') {
        
        if(isShifted) {
            
            char toInsert;
            if( !(key > 96 && key < 123) && !(key > 65 && key < 90) && shiftMap.find(key) != shiftMap.end() ) {
                toInsert = shiftMap[key];//toInsert = key - 32;
            } else {
                toInsert = key;
            }
            
            text.insert(text.begin()+cursorPosition, toInsert);
        } else {
            text.insert(text.begin()+cursorPosition, key);
        }
        cursorPosition++;
    }
    
    
    if (key==OF_KEY_BACKSPACE) {
        if(selecting) {
            text.erase(text.begin() + selectionBegin,
                       text.begin() + selectionEnd
                       );
            cursorPosition = selectionBegin;
            selecting = false;
        } else {
            if (cursorPosition>0) {
                text.erase(text.begin()+cursorPosition-1);
                --cursorPosition;
            }
        }
    }
    
    if (key==OF_KEY_DEL) {
        if(selecting) {
            text.erase(text.begin() + selectionBegin,
                       text.begin() + selectionEnd
                       );
            cursorPosition = selectionBegin;
            selecting = false;
        } else {
            if (text.size() > cursorPosition) {
                text.erase(text.begin()+cursorPosition);
            }
        }
    }
    
    if (key==OF_KEY_LEFT){
        if(selecting) {
            cursorPosition = selectionBegin;
            selecting = false;
            
        } else {
            if (cursorPosition>0){
                --cursorPosition;
            }
        }
    }
    
    
    
    if (key==OF_KEY_RIGHT){
        if(selecting) {
            cursorPosition = selectionEnd;
            selecting = false;
        } else {
            if (cursorPosition<text.size()){
                ++cursorPosition;
            }
        }
    }
    
    
    if (key==OF_KEY_UP){
        if(selecting) {
            cursorPosition = selectionBegin;
            selecting = false;
            
        } else {
            if (cursorPosition>0) {
                int xx, yy;
                getCursorCoords(cursorPosition, xx, yy);
                if(yy>0) {
                    yy--;
                    vector<string> lines = ofSplitString(text, "\n");
                    xx = MIN(lines[yy].size()-1, xx);
                    cursorPosition = xx;
                    for(int i = 0; i < yy; i++) cursorPosition += lines[i].size()+1;
                    printf("Cursor position: %d\n", cursorPosition);
                } else {
                    cursorPosition = 0;
                }
            }
        }
    }
    
    
    
    if (key==OF_KEY_DOWN){
        if(selecting) {
            cursorPosition = selectionEnd;
            selecting = false;
        } else {
            int xx, yy;
            getCursorCoords(cursorPosition, xx, yy);
            vector<string> lines = ofSplitString(text, "\n");
            yy++;
            if(yy<lines.size()-1) {
                
                xx = MIN(lines[yy].size()-1, xx);
                cursorPosition = xx;
                for(int i = 0; i < yy; i++) cursorPosition += lines[i].size()+1;
                printf("Cursor position: %d\n", cursorPosition);
            } else {
                cursorPosition = text.size()-1;
            }
        }
    }
    
    
    
    
}

void NfTextInputField::keyReleased(ofKeyEventArgs &a)
{
    
    if(a.key == 3686) {
        isCommand = false;
    }
    
    if(a.key == OF_KEY_SHIFT) {
        isShifted = false;
    }
}

void NfTextInputField::clear() {
    text.clear();
    cursorPosition = 0;
}

// Function to check if a character is in the whitelist for a given ValueType
bool NfTextInputField::isValidChar(nfAPI::ValueType valueType, char inputChar) {
    // If the valueType is String, accept every character.
    if (valueType == nfAPI::ValueType::String) {
        return true;
    }

    static std::unordered_map<nfAPI::ValueType, std::unordered_set<char>> charWhitelists = {
        {nfAPI::ValueType::Bool, {'0', '1', '\n', '\t', '\b', '\r', '\x1b'}}, // Example for BoolType
        {nfAPI::ValueType::Int, {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '+', '\n', '\t', '\b', '\r', '\x1b'}}, // Example for IntType
        {nfAPI::ValueType::Double, {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '+', '.', 'e', 'E', '\n', '\t', '\b', '\r', '\x1b'}} // Example for DoubleType
    };

    auto whitelistIt = charWhitelists.find(valueType);
    if (whitelistIt != charWhitelists.end()) {
        // Check if the inputChar is in the whitelist for the given ValueType
        return whitelistIt->second.find(inputChar) != whitelistIt->second.end();
    }

    // Handle the case where the ValueType is not recognized
    return false;
}


}
