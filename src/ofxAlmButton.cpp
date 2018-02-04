#include "ofxAlmButton.h"

namespace alm {
	
	//--------------------------------------------------------------
	ofxAlmButton::ofxAlmButton() : ofxAlmInteractiveBox() {
		isVisible = true;
		isAutoDraw = false;
		clearCallback();
	}
	
	ofxAlmButton::~ofxAlmButton() {
		setIsAutoDraw(false);
		clearDefaultImage();
		clearHoverImage();
		clearActiveImage();
		clearDisabledImage();
		clearCallback();
	}
	
	//--------------------------------------------------------------
	void ofxAlmButton::setup() {
		setIsAutoDraw(true);
	}
	
	void ofxAlmButton::setup(const string& defaultImage) {
		setDefaultImage(defaultImage);
		setup();
	}
	
	void ofxAlmButton::setup(const string& defaultImage, const string& hoverImage) {
		setDefaultImage(defaultImage);
		setHoverImage(hoverImage);
		setup();
	}
	
	void ofxAlmButton::setup(const string& defaultImage, const string& hoverImage, const string& activeImage) {
		setDefaultImage(defaultImage);
		setHoverImage(hoverImage);
		setActiveImage(activeImage);
		setup();
	}
	
	void ofxAlmButton::setup(const string& defaultImage, const string& hoverImage, const string& activeImage, const string& disabledImage) {
		setDefaultImage(defaultImage);
		setHoverImage(hoverImage);
		setActiveImage(activeImage);
		setDisabledImage(disabledImage);
		setup();
	}
	
	void ofxAlmButton::setup(const ofImage& defaultImage) {
		setDefaultImage(defaultImage);
		setup();
	}
	
	void ofxAlmButton::setup(const ofImage& defaultImage, const ofImage& hoverImage) {
		setDefaultImage(defaultImage);
		setHoverImage(hoverImage);
		setup();
	}
	
	void ofxAlmButton::setup(const ofImage& defaultImage, const ofImage& hoverImage, const ofImage& activeImage) {
		setDefaultImage(defaultImage);
		setHoverImage(hoverImage);
		setActiveImage(activeImage);
		setup();
	}
	
	void ofxAlmButton::setup(const ofImage& defaultImage, const ofImage& hoverImage, const ofImage& activeImage, const ofImage& disabledImage) {
		setDefaultImage(defaultImage);
		setHoverImage(hoverImage);
		setActiveImage(activeImage);
		setDisabledImage(disabledImage);
		setup();
	}
	
	//--------------------------------------------------------------
	void ofxAlmButton::setSizeByDefaultImage() {
		if (defaultImage.isAllocated()) {
			setSize(defaultImage.getWidth(), defaultImage.getHeight());
		}
	}
	
	//--------------------------------------------------------------
	void ofxAlmButton::draw() {
		if (!isVisible) return;
		if (!getIsEnabled() && disabledImage.isAllocated()) {
			disabledImage.draw(x, y);
		} else if (getIsMouseDown() && activeImage.isAllocated()) {
			activeImage.draw(x, y);
		} else if (getIsMouseOver() && hoverImage.isAllocated()) {
			hoverImage.draw(x, y);
		} else if (defaultImage.isAllocated()) {
			defaultImage.draw(x, y);
		}
	}
	
	//--------------------------------------------------------------
	void ofxAlmButton::clearCallback() {
		atVisible = nullptr;
		atHidden = nullptr;
	}
	
	//--------------------------------------------------------------
	bool ofxAlmButton::getIsVisible() const {
		return isVisible;
	}
	
	void ofxAlmButton::setIsVisible(const bool visible) {
		if (visible == isVisible) return;
		isVisible = visible;
		
		if (isVisible) {
			dispatchEvent(ofxAlmEventArgs::Visible, onVisible, this, &ofxAlmButton::implVisible, atVisible);
		} else {
			dispatchEvent(ofxAlmEventArgs::Hidden, onHidden, this, &ofxAlmButton::implHidden, atHidden);
		}
	}
	
	//--------------------------------------------------------------
	bool ofxAlmButton::getIsAutoDraw() const {
		return isAutoDraw;
	}
	
	void ofxAlmButton::setIsAutoDraw(const bool enabled) {
		if (isAutoDraw == enabled) return;
		isAutoDraw = enabled;
		if (isAutoDraw) {
			ofAddListener(ofEvents().draw, this, &ofxAlmButton::drawHandler);
		} else {
			ofRemoveListener(ofEvents().draw, this, &ofxAlmButton::drawHandler);
		}
	}
	
	//--------------------------------------------------------------
	ofImage& ofxAlmButton::getDefaultImage() {
		return defaultImage;
	}
	
	void ofxAlmButton::setDefaultImage(const string& path) {
		clearDefaultImage();
		defaultImage.load(path);
	}
	
	void ofxAlmButton::setDefaultImage(const ofImage& image) {
		clearDefaultImage();
		defaultImage = image;
	}
	
	void ofxAlmButton::clearDefaultImage() {
		if (defaultImage.isAllocated()) {
			defaultImage.clear();
		}
	}
	
	//--------------------------------------------------------------
	ofImage& ofxAlmButton::getHoverImage() {
		return hoverImage;
	}
	
	void ofxAlmButton::setHoverImage(const string& path) {
		clearHoverImage();
		hoverImage.load(path);
	}
	
	void ofxAlmButton::setHoverImage(const ofImage& image) {
		clearHoverImage();
		hoverImage = image;
	}
	
	void ofxAlmButton::clearHoverImage() {
		if (hoverImage.isAllocated()) {
			hoverImage.clear();
		}
	}
	
	//--------------------------------------------------------------
	ofImage& ofxAlmButton::getActiveImage() {
		return activeImage;
	}
	
	void ofxAlmButton::setActiveImage(const string& path) {
		clearActiveImage();
		activeImage.load(path);
	}
	
	void ofxAlmButton::setActiveImage(const ofImage& image) {
		clearActiveImage();
		activeImage = image;
	}
	
	void ofxAlmButton::clearActiveImage() {
		if (activeImage.isAllocated()) {
			activeImage.clear();
		}
	}
	
	//--------------------------------------------------------------
	ofImage& ofxAlmButton::getDisabledImage() {
		return defaultImage;
	}
	
	void ofxAlmButton::setDisabledImage(const string& path) {
		clearDisabledImage();
		disabledImage.load(path);
	}
	
	void ofxAlmButton::setDisabledImage(const ofImage& image) {
		clearDisabledImage();
		disabledImage = image;
	}
	
	void ofxAlmButton::clearDisabledImage() {
		if (disabledImage.isAllocated()) {
			disabledImage.clear();
		}
	}
	
	//--------------------------------------------------------------
	void ofxAlmButton::drawHandler(ofEventArgs &event) {
		draw();
	}
}

