//
//  Button.hpp
//  nodeflowUI
//
//  Created by Matthias Strohmaier on 17.02.24.
//

#ifndef Button_hpp
#define Button_hpp

#include "ofMain.h"
#include "UIElement.hpp"

#ifndef OFX_TEXTFIELD_FONT_RENDERER
#define OFX_TEXTFIELD_FONT_RENDERER ofTrueTypeFont
#endif
// TODO: wrapping
#include "ofxTextInputFieldFontRenderer.h"

namespace nfUI {
class Button : public nfUI::UIElement {
    
public:
    // Constructor for Button
    Button(const NfUIConfig& config = NfUIConfig());
    virtual ~Button();
    //swap in a font!
    void setFont(OFX_TEXTFIELD_FONT_RENDERER& font);
    
    void setup();
    
    void enable();
    void disable();
    bool getIsEnabled();
    
    ofRectangle bounds, position;
    
    void draw();
    void clear();
    
    string text;
 
    // ofEvent<string> textChanged;
    void keyPressed(ofKeyEventArgs &a);
    void keyReleased(ofKeyEventArgs &a);

    
protected:
    ofxTextInput::FontRenderer* fontRef;
    bool    isEnabled;
    bool    mouseDownInRect;
    void    mousePressed(ofMouseEventArgs& args);
    // void    mouseDragged(ofMouseEventArgs& args);
    void    mouseReleased(ofMouseEventArgs& args);

};
}

#endif /* Button_hpp */
