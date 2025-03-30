//
//  GUIParams.cpp
//  nodeflowUI
//
//  Created by Ulrike Siegl on 17.02.24.
//

#include "GUIParams.hpp"

GUIParams::GUIParams() :
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
bool GUIParams::getShowStatusBar() const {
    return _showStatusBar;
}

void GUIParams::setShowStatusBar(bool show) {
    _showStatusBar = show;
}

// Getter and setter for statusBarHeight
uint32_t GUIParams::getStatusBarHeight() const {
    return _statusBarHeight;
}

void GUIParams::setStatusBarHeight(uint32_t height) {
    _statusBarHeight = height;
}

// Getter and setter for statusBarColor
const ofColor& GUIParams::getStatusBarColor() const {
    return _statusBarColor;
}

void GUIParams::setStatusBarColor(const ofColor& color) {
    _statusBarColor = color;
}

// Getter and setter for statusBarTextColor
const ofColor& GUIParams::getStatusBarTextColor() const {
    return _statusBarTextColor;
}

void GUIParams::setStatusBarTextColor(const ofColor& color) {
    _statusBarTextColor = color;
}

// Getter and setter for showGrid
bool GUIParams::getShowGrid() const {
    return _showGrid;
}

void GUIParams::setShowGrid(bool show) {
    _showGrid = show;
}

// Getter and setter for gridSize
uint32_t GUIParams::getGridSize() const {
    return _gridSize;
}

void GUIParams::setGridSize(uint32_t size) {
    _gridSize = size;
}

// Getter and setter for majorStep
uint32_t GUIParams::getMajorStep() const {
    return _majorStep;
}

void GUIParams::setMajorStep(uint32_t size) {
    _majorStep = size;
}

// Getter and setter for gridColor
const ofColor& GUIParams::getMajorGridColor() const {
    return _majorGridColor;
}

void GUIParams::setMajorGridColor(const ofColor& color) {
    _majorGridColor = color;
}

// Getter and setter for minorGridColor
const ofColor& GUIParams::getMinorGridColor() const {
    return _minorGridColor;
}

void GUIParams::setMinorGridColor(const ofColor& color) {
    _minorGridColor = color;
}

// Getter and setter for scalingFactor
const double GUIParams::getScalingFactor() const {
    return _scalingFactor;
}

void GUIParams::setScalingFactor(const double& scalingFactor) {
    _scalingFactor = scalingFactor;
}

// Getter and setter for statusBarText1
const std::string& GUIParams::getStatusBarText1() const {
    return _statusBarText1;
}

void GUIParams::setStatusBarText1(const std::string& statusBarText) {
    _statusBarText1 = statusBarText;
}

// Getter and setter for statusBarText2
const std::string& GUIParams::getStatusBarText2() const {
    return _statusBarText2;
}

void GUIParams::setStatusBarText2(const std::string& statusBarText) {
    _statusBarText2 = statusBarText;
}

// Getter and setter for statusBarText3
const std::string& GUIParams::getStatusBarText3() const {
    return _statusBarText3;
}

void GUIParams::setStatusBarText3(const std::string& statusBarText) {
    _statusBarText3 = statusBarText;
}

// Getter and setter for showFPS
const bool GUIParams::getShowFPS() const {
    return _showFPS;
}

void GUIParams::setShowFPS(const bool showFPS) {
    _showFPS = showFPS;
}
