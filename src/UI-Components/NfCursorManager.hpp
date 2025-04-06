#pragma once

#include "ofMain.h"
#include <GLFW/glfw3.h>

namespace nfUI {

class NfCursorManager {
public:
    static void setCursor(int cursorType) {
        auto* glfwWindow = getGLFWWindow();
        if (glfwWindow) {
            glfwSetCursor(glfwWindow, glfwCreateStandardCursor(cursorType));
        }
    }
    
    static void setDefaultCursor() {
        setCursor(GLFW_ARROW_CURSOR);
    }
    
    static void setHandCursor() {
        setCursor(GLFW_HAND_CURSOR);
    }
    
    static void setIBeamCursor() {
        setCursor(GLFW_IBEAM_CURSOR);
    }
    
    static void setResizeNSCursor() {
        setCursor(GLFW_VRESIZE_CURSOR);
    }
    
    static void setResizeEWCursor() {
        setCursor(GLFW_HRESIZE_CURSOR);
    }

private:
    static GLFWwindow* getGLFWWindow() {
        ofAppGLFWWindow* glfwWindow = dynamic_cast<ofAppGLFWWindow*>(ofGetWindowPtr());
        if (glfwWindow) {
            return glfwWindow->getGLFWWindow();
        }
        ofLogError("NfCursorManager") << "Error: Could not get GLFW window pointer.";
        return nullptr;
    }
};

} // namespace nfUI 
