#include "ofxAlmEventArgs.h"

namespace alm {
	
	//--------------------------------------------------------------
	const string ofxAlmEventArgs::typeNames[] = {
		// ofxAlmInteractiveBox
		"Enabled",
		"Disabled",
		"MouseOver",
		"MouseOut",
		"MouseDown",
		"MouseUp",
		"DragOver",
		"DragOut",
		"DragDrop",
		"DragBegin",
		"DragMove",
		"DragEnd",
		"Click",
		"ReleaseOutside",
		"KeyPressed",
		"KeyReleased",
		// ofxAlmButton
		"Visible",
		"Hidden",
	};
	
	//--------------------------------------------------------------
	ofxAlmEventArgs::ofxAlmEventArgs() : type(Enabled), target(NULL) {
	};
	
	//--------------------------------------------------------------
	ofxAlmEventArgs::ofxAlmEventArgs(Type type, ofxAlmInteractiveBox* target) : type(type), target(target) {
	};
	
	//--------------------------------------------------------------
	ofxAlmEventArgs::~ofxAlmEventArgs() {
		target = NULL;
	};
	
	//--------------------------------------------------------------
	string ofxAlmEventArgs::getTypeName() {
		return ofxAlmEventArgs::getTypeName(type);
	}
	
	//--------------------------------------------------------------
	string ofxAlmEventArgs::getTypeName(Type type) {
		return typeNames[type];
	}
}

