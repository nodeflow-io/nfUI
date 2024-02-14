#pragma once

#include "ofMain.h"
#include "ofxGui.h"


template <typename T>
class ReadOnlyTextInput {
public:
    void setup(const std::string& label, const ofParameter<T>& param, float x, float y, float width) {
        parameter = param;
        text = label + ": " + ofToString(parameter.get());
        // Set a default size for the text display
        this->x = x;
        this->y = y;
        this->width = width;
        height = 20;
    }

    void draw() const {
        ofDrawBitmapString(text, x, y + 12);
    }

    float getWidth() const {
        return width;
    }

    float getHeight() const {
        return height;
    }

private:
    ofParameter<T> parameter;
    std::string text;
    float x;
    float y;
    float width;
    float height;
};

class TextInputRenderer {
public:
    std::vector<std::pair<std::string, ofAbstractParameter&>> parameters;

    void setup(const std::vector<std::pair<std::string, ofAbstractParameter&>>& params) {
        parameters = params;
        float x = 10;
        float y = 10;
        float width = 200;

        for (const auto& paramPair : parameters) {
            const auto& label = paramPair.first;
            auto& param = paramPair.second;

            if (param.type() == typeid(ofParameter<float>).name()) {
                auto& floatParam = dynamic_cast<ofParameter<float>&>(param);
                addInputField<float>(label, floatParam, x, y, width);
            } else if (param.type() == typeid(ofParameter<int>).name()) {
                auto& intParam = dynamic_cast<ofParameter<int>&>(param);
                addInputField<int>(label, intParam, x, y, width);
            } else {
                ofLogWarning("TextInputRenderer") << "Unsupported parameter type: "; //  << param.type().name();
            }

            y += 25; // Adjust the vertical spacing
        }
    }

    void draw() {
        for (auto& inputField : intInputFields) {
            inputField.draw();
        }
    }

private:
    std::vector<ReadOnlyTextInput<float>> floatInputFields;
    std::vector<ReadOnlyTextInput<int>> intInputFields;

    template <typename T>
    void addInputField(const std::string& label, const ofParameter<T>& param, float x, float y, float width) {
        ReadOnlyTextInput<T> textInput;
        textInput.setup(label, param, x, y, width);

        if constexpr (std::is_same<T, float>::value) {
            floatInputFields.push_back(textInput);
        } else if constexpr (std::is_same<T, int>::value) {
            intInputFields.push_back(textInput);
        }
    }
};


class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
    
private:
    TextInputRenderer textInputRenderer;
    std::vector<std::pair<std::string, ofAbstractParameter&>> parameters;

		
};
