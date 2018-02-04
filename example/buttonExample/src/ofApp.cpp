#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetLogLevel(ofLogLevel::OF_LOG_VERBOSE);
	ofBackground(255);
	
	box.setIsVerbose(true);
	box.set(10, 10, 200, 50);
	box.setName("myBox");
	box.setIsDraggable(true);
	
	button.setup("default.png", "hover.png", "active.png", "disabled.png");
	button.setIsVerbose(true);
	button.setName("myButton");
	button.setSizeByDefaultImage();
	button.setPosition(10, 100);
	//button.setIsAutoDraw(false);
	
	ofAddListener(button.onMouseOver, this, &ofApp::buttonMouseOverHandler);
	ofAddListener(button.onMouseDown, this, &ofApp::buttonMouseDownHandler);
	ofAddListener(button.onMouseUp, this, &ofApp::buttonMouseUpHandler);
	button.atClick = [&](ofxAlmEventArgs& event) { ofLog() << event.target->getName() << " : onClick"; };
}

//--------------------------------------------------------------
void ofApp::buttonMouseOverHandler(ofxAlmEventArgs& event) {
	ofLog() << event.target->getName() << " : " << event.getTypeName();
}

//--------------------------------------------------------------
void ofApp::buttonMouseDownHandler(ofxAlmEventArgs& event) {
	ofLog() << event.target->getName() << " : onMouseDown";
}

//--------------------------------------------------------------
void ofApp::buttonMouseUpHandler(ofxAlmEventArgs& event) {
	ofLog() << event.target->getName() << " : onMouseUp";
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {
	box.debugDraw();
	
	//button.draw();
	//button.debugDraw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}

