#include "ofxAlmInteractiveBox.h"

namespace alm {
	
	//--------------------------------------------------------------
	ofxAlmInteractiveBox::ofxAlmInteractiveBox() {
		name = "";
		isEnabled = false;
		isMouseOver = false;
		isMouseDown = false;
		isDraggedIn = false;
		isDraggable = false;
		isDragged = false;
		isKeyPressed = false;
		isVerbose = false;
		keyCode = -1;
		clearCallback();
		setIsEnabled(true);
	}
	
	ofxAlmInteractiveBox::ofxAlmInteractiveBox(const float x, const float y, const float width, const float height) : ofRectangle(x, y, width, height) {
		ofxAlmInteractiveBox();
	}
	
	ofxAlmInteractiveBox::ofxAlmInteractiveBox(const ofPoint& position, const float width, const float height) : ofRectangle(position, width, height) {
		ofxAlmInteractiveBox();
	}
	
	ofxAlmInteractiveBox::ofxAlmInteractiveBox(const ofRectangle& rect) : ofRectangle(rect) {
		ofxAlmInteractiveBox();
	}
	
	ofxAlmInteractiveBox::ofxAlmInteractiveBox(const ofPoint& point0, const ofPoint& point1) : ofRectangle(point0, point1) {
		ofxAlmInteractiveBox();
	}
	
	ofxAlmInteractiveBox::~ofxAlmInteractiveBox() {
		setIsEnabled(false);
		clearCallback();
	}
	
	//--------------------------------------------------------------
	void ofxAlmInteractiveBox::debugDraw() const {
		ofPushStyle();
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(255, 0, 0, isMouseDown ? 96 : isMouseOver ? 64 : 32);
		ofDrawRectangle(x, y, width, height);
		ofNoFill();
		ofSetLineWidth(1);
		ofSetColor(255, 0, 0, 128);
		ofDrawRectangle(x, y, width, height);
		ofDrawBitmapString(name, x + 5, y + 13);
		ofPopStyle();
	}
	
	//--------------------------------------------------------------
	bool ofxAlmInteractiveBox::hitTest(const float x, const float y) const {
		return (x >= this->x) && (x < this->x + width) && (y >= this->y) && (y < this->y + height);
	}
	
	//--------------------------------------------------------------
	string ofxAlmInteractiveBox::getName() const {
		return name;
	}
	
	void ofxAlmInteractiveBox::setName(const string& name) {
		this->name = name;
	}
	
	//--------------------------------------------------------------
	bool ofxAlmInteractiveBox::getIsMouseOver() const {
		return isMouseOver;
	}
	
	//--------------------------------------------------------------
	bool ofxAlmInteractiveBox::getIsMouseDown() const {
		return isMouseDown;
	}
	
	//--------------------------------------------------------------
	bool ofxAlmInteractiveBox::getIsDraggedIn() const {
		return isDraggedIn;
	}
	
	//--------------------------------------------------------------
	bool ofxAlmInteractiveBox::getIsDragged() const {
		return isDragged;
	}
	
	//--------------------------------------------------------------
	bool ofxAlmInteractiveBox::getIsKeyPressed() const {
		return isKeyPressed;
	}
	
	//--------------------------------------------------------------
	bool ofxAlmInteractiveBox::getIsEnabled() const {
		return isEnabled;
	}
	
	void ofxAlmInteractiveBox::setIsEnabled(const bool enabled) {
		if (enabled == isEnabled) return;
		isEnabled = enabled;
		
		if (isEnabled) {
			ofAddListener(ofEvents().mouseMoved, this, &ofxAlmInteractiveBox::mouseMovedHandler);
			ofAddListener(ofEvents().mouseDragged, this, &ofxAlmInteractiveBox::mouseDraggedHandler);
			ofAddListener(ofEvents().mousePressed, this, &ofxAlmInteractiveBox::mousePressedHandler);
			ofAddListener(ofEvents().mouseReleased, this, &ofxAlmInteractiveBox::mouseReleasedHandler);
			ofAddListener(ofEvents().keyPressed, this, &ofxAlmInteractiveBox::keyPressedHandler);
			ofAddListener(ofEvents().keyReleased, this, &ofxAlmInteractiveBox::keyReleasedHandler);
			dispatchEvent(ofxAlmEventArgs::Enabled, onEnabled, this, &ofxAlmInteractiveBox::implEnabled, atEnabled);
		} else {
			ofRemoveListener(ofEvents().mouseMoved, this, &ofxAlmInteractiveBox::mouseMovedHandler);
			ofRemoveListener(ofEvents().mouseDragged, this, &ofxAlmInteractiveBox::mouseDraggedHandler);
			ofRemoveListener(ofEvents().mousePressed, this, &ofxAlmInteractiveBox::mousePressedHandler);
			ofRemoveListener(ofEvents().mouseReleased, this, &ofxAlmInteractiveBox::mouseReleasedHandler);
			ofRemoveListener(ofEvents().keyPressed, this, &ofxAlmInteractiveBox::keyPressedHandler);
			ofRemoveListener(ofEvents().keyReleased, this, &ofxAlmInteractiveBox::keyReleasedHandler);
			dispatchEvent(ofxAlmEventArgs::Disabled, onDisabled, this, &ofxAlmInteractiveBox::implDisabled, atDisabled);
		}
		checkMouseOver();
	}
	
	//--------------------------------------------------------------
	bool ofxAlmInteractiveBox::getIsDraggable() const {
		return isDraggable;
	}
	
	void ofxAlmInteractiveBox::setIsDraggable(const bool draggable) {
		if (draggable == isDraggable) return;
		isDraggable = draggable;
		
		// Check drag end
		if (!isDraggable && isDragged) {
			isDragged = false;
			dispatchEvent(ofxAlmEventArgs::DragEnd, onDragEnd, this, &ofxAlmInteractiveBox::implDragEnd, atDragEnd);
		}
	}
	
	//--------------------------------------------------------------
	bool ofxAlmInteractiveBox::getIsVerbose() const {
		return isVerbose;
	}
	
	void ofxAlmInteractiveBox::setIsVerbose(const bool verbose) {
		isVerbose = verbose;
	}
	
	//--------------------------------------------------------------
	int ofxAlmInteractiveBox::getKeyCode() const {
		return keyCode;
	}
	
	void ofxAlmInteractiveBox::setKeyCode(const int keyCode) {
		if (keyCode == this->keyCode) return;
		this->keyCode = keyCode;
		
		// Check key released
		if (isKeyPressed) {
			isKeyPressed = false;
			dispatchEvent(ofxAlmEventArgs::KeyReleased, onKeyReleased, this, &ofxAlmInteractiveBox::implKeyReleased, atKeyReleased);
		}
	}
	
	//--------------------------------------------------------------
	string ofxAlmInteractiveBox::toString() const {
		stringstream ss;
		ss << "[ofxAlmInteractiveBox] name = '" << name << "', enabled = " << isEnabled << ", mouseOver = " << isMouseOver << ", mouseDown = " << isMouseDown << ", draggedIn = " << isDraggedIn << ", bounds = " << *this;
		return ss.str();
	}
	
	//--------------------------------------------------------------
	void ofxAlmInteractiveBox::checkMouseOver() {
		bool isHit = isEnabled && hitTest(ofGetMouseX(), ofGetMouseY());
		if (!isMouseOver && isHit) {
			isMouseOver = true;
			dispatchEvent(ofxAlmEventArgs::MouseOver, onMouseOver, this, &ofxAlmInteractiveBox::implMouseOver, atMouseOver);
			if (ofGetMousePressed()) {
				isDraggedIn = true;
				dispatchEvent(ofxAlmEventArgs::DragOver, onDragOver, this, &ofxAlmInteractiveBox::implDragOver, atDragOver);
			}
		} else if (isMouseOver && !isHit) {
			isMouseOver = false;
			dispatchEvent(ofxAlmEventArgs::MouseOut, onMouseOut, this, &ofxAlmInteractiveBox::implMouseOut, atMouseOut);
			if (isDraggedIn) {
				isDraggedIn = false;
				dispatchEvent(ofxAlmEventArgs::DragOut, onDragOut, this, &ofxAlmInteractiveBox::implDragOut, atDragOut);
			}
		}
	}
	
	//--------------------------------------------------------------
	void ofxAlmInteractiveBox::clearCallback() {
		atEnabled = nullptr;
		atDisabled = nullptr;
		atMouseOver = nullptr;
		atMouseOut = nullptr;
		atMouseDown = nullptr;
		atMouseUp = nullptr;
		atDragOver = nullptr;
		atDragOut = nullptr;
		atDragDrop = nullptr;
		atDragBegin = nullptr;
		atDragMove = nullptr;
		atDragEnd = nullptr;
		atClick = nullptr;
		atReleaseOutside = nullptr;
		atKeyPressed = nullptr;
		atKeyReleased = nullptr;
	}
	
	//--------------------------------------------------------------
	void ofxAlmInteractiveBox::mouseMovedHandler(ofMouseEventArgs &event) {
		checkMouseOver();
	}
	
	//--------------------------------------------------------------
	void ofxAlmInteractiveBox::mouseDraggedHandler(ofMouseEventArgs &event) {
		if (event.button != 0) return;
		checkMouseOver();
		
		// Check dragging
		if (isDraggable && isMouseDown) {
			x = ofGetMouseX() + dragOffset.x;
			y = ofGetMouseY() + dragOffset.y;
			if (!isDragged) {
				isDragged = true;
				dispatchEvent(ofxAlmEventArgs::DragBegin, onDragBegin, this, &ofxAlmInteractiveBox::implDragBegin, atDragBegin);
			}
			dispatchEvent(ofxAlmEventArgs::DragMove, onDragMove, this, &ofxAlmInteractiveBox::implDragMove, atDragMove);
		}
	}
	
	//--------------------------------------------------------------
	void ofxAlmInteractiveBox::mousePressedHandler(ofMouseEventArgs &event) {
		if (event.button != 0) return;
		
		// Check mouse down
		if (isMouseOver) {
			isMouseDown = true;
			mouseDownPosition.set(ofGetMouseX(), ofGetMouseY());
			dragOffset.set(x - mouseDownPosition.x, y - mouseDownPosition.y);
			dispatchEvent(ofxAlmEventArgs::MouseDown, onMouseDown, this, &ofxAlmInteractiveBox::implMouseDown, atMouseDown);
		}
	}
	
	//--------------------------------------------------------------
	void ofxAlmInteractiveBox::mouseReleasedHandler(ofMouseEventArgs &event) {
		if (event.button != 0) return;
		
		// Check drag end
		if (isDraggable && isDragged) {
			isDragged = false;
			dispatchEvent(ofxAlmEventArgs::DragEnd, onDragEnd, this, &ofxAlmInteractiveBox::implDragEnd, atDragEnd);
		}
		
		// Check mouse up
		if (isMouseOver) {
			if (isMouseDown) {
				// button down & release inside (click)
				isMouseDown = false;
				dispatchEvent(ofxAlmEventArgs::MouseUp, onMouseUp, this, &ofxAlmInteractiveBox::implMouseUp, atMouseUp);
				dispatchEvent(ofxAlmEventArgs::Click, onClick, this, &ofxAlmInteractiveBox::implClick, atClick);
			} else {
				// drag in & release inside (drag drop)
				isDraggedIn = false;
				dispatchEvent(ofxAlmEventArgs::MouseUp, onMouseUp, this, &ofxAlmInteractiveBox::implMouseUp, atMouseUp);
				dispatchEvent(ofxAlmEventArgs::DragDrop, onDragDrop, this, &ofxAlmInteractiveBox::implDragDrop, atDragDrop);
			}
		} else {
			if (isMouseDown) {
				// button down & release outside
				isMouseDown = false;
				dispatchEvent(ofxAlmEventArgs::MouseUp, onMouseUp, this, &ofxAlmInteractiveBox::implMouseUp, atMouseUp);
				dispatchEvent(ofxAlmEventArgs::ReleaseOutside, onReleaseOutside, this, &ofxAlmInteractiveBox::implReleaseOutside, atReleaseOutside);
			}
		}
	}
	
	//--------------------------------------------------------------
	void ofxAlmInteractiveBox::keyPressedHandler(ofKeyEventArgs &event) {
		if (event.keycode != keyCode) return;
		
		// Check key pressed
		isKeyPressed = true;
		dispatchEvent(ofxAlmEventArgs::KeyPressed, onKeyPressed, this, &ofxAlmInteractiveBox::implKeyPressed, atKeyPressed);
	}
	
	//--------------------------------------------------------------
	void ofxAlmInteractiveBox::keyReleasedHandler(ofKeyEventArgs &event) {
		if (event.keycode != keyCode) return;
		
		// Check key released
		if (isKeyPressed) {
			isKeyPressed = false;
			dispatchEvent(ofxAlmEventArgs::KeyReleased, onKeyReleased, this, &ofxAlmInteractiveBox::implKeyReleased, atKeyReleased);
		}
	}
}

