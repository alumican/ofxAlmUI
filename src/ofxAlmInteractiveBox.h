#pragma once

#include "ofMain.h"
#include "ofxAlmEventArgs.h"

namespace alm {
	
	class ofxAlmInteractiveBox : public ofRectangle {
		
		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------
		
	public:
		// events
		ofEvent<ofxAlmEventArgs&> onEnabled;
		ofEvent<ofxAlmEventArgs&> onDisabled;
		ofEvent<ofxAlmEventArgs&> onMouseOver;
		ofEvent<ofxAlmEventArgs&> onMouseOut;
		ofEvent<ofxAlmEventArgs&> onMouseDown;
		ofEvent<ofxAlmEventArgs&> onMouseUp;
		ofEvent<ofxAlmEventArgs&> onDragOver;
		ofEvent<ofxAlmEventArgs&> onDragOut;
		ofEvent<ofxAlmEventArgs&> onDragDrop;
		ofEvent<ofxAlmEventArgs&> onDragBegin;
		ofEvent<ofxAlmEventArgs&> onDragMove;
		ofEvent<ofxAlmEventArgs&> onDragEnd;
		ofEvent<ofxAlmEventArgs&> onClick;
		ofEvent<ofxAlmEventArgs&> onReleaseOutside;
		ofEvent<ofxAlmEventArgs&> onKeyPressed;
		ofEvent<ofxAlmEventArgs&> onKeyReleased;
		
		// callbacks
		function<void(ofxAlmEventArgs&)> atEnabled;
		function<void(ofxAlmEventArgs&)> atDisabled;
		function<void(ofxAlmEventArgs&)> atMouseOver;
		function<void(ofxAlmEventArgs&)> atMouseOut;
		function<void(ofxAlmEventArgs&)> atMouseDown;
		function<void(ofxAlmEventArgs&)> atMouseUp;
		function<void(ofxAlmEventArgs&)> atDragOver;
		function<void(ofxAlmEventArgs&)> atDragOut;
		function<void(ofxAlmEventArgs&)> atDragDrop;
		function<void(ofxAlmEventArgs&)> atDragBegin;
		function<void(ofxAlmEventArgs&)> atDragMove;
		function<void(ofxAlmEventArgs&)> atDragEnd;
		function<void(ofxAlmEventArgs&)> atClick;
		function<void(ofxAlmEventArgs&)> atReleaseOutside;
		function<void(ofxAlmEventArgs&)> atKeyPressed;
		function<void(ofxAlmEventArgs&)> atKeyReleased;
		
	protected:
		
	private:
		string name;
		bool isEnabled;
		bool isMouseOver;
		bool isMouseDown;
		bool isDraggedIn;
		bool isDraggable;
		bool isDragged;
		bool isKeyPressed;
		bool isVerbose;
		ofVec2f mouseDownPosition;
		ofVec2f dragOffset;
		int keyCode;
		
		
		
		
		
		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------
		
	public:
		ofxAlmInteractiveBox();
		ofxAlmInteractiveBox(const float x, const float y, const float width, const float height);
		ofxAlmInteractiveBox(const ofPoint& position, const float width, const float height);
		ofxAlmInteractiveBox(const ofRectangle& rect);
		ofxAlmInteractiveBox(const ofPoint& point0, const ofPoint& point1);
		virtual ~ofxAlmInteractiveBox();
		
		void debugDraw() const;
		bool hitTest(const float x, const float y) const;
		string toString() const;
		
		// name
		string getName() const;
		void setName(const string& name);
		
		// state
		bool getIsMouseOver() const;
		bool getIsMouseDown() const;
		bool getIsDraggedIn() const;
		bool getIsDragged() const;
		bool getIsKeyPressed() const;
		
		// behavior
		bool getIsEnabled() const;
		void setIsEnabled(const bool enabled);
		
		bool getIsDraggable() const;
		void setIsDraggable(const bool enabled);
		
		bool getIsVerbose() const;
		void setIsVerbose(const bool enabled);
		
		int getKeyCode() const;
		void setKeyCode(const int keyCode);
		
	protected:
		// functions for overrided by sub class
		virtual void implEnabled() {};
		virtual void implDisabled() {};
		virtual void implMouseOver() {};
		virtual void implMouseOut() {};
		virtual void implMouseDown() {};
		virtual void implMouseUp() {};
		virtual void implDragOver() {};
		virtual void implDragOut() {};
		virtual void implDragDrop() {};
		virtual void implDragBegin() {};
		virtual void implDragMove() {};
		virtual void implDragEnd() {};
		virtual void implClick() {};
		virtual void implReleaseOutside() {};
		virtual void implKeyPressed() {};
		virtual void implKeyReleased() {};
		
		// event system
		template <class Event, typename T>
		void dispatchEvent(const ofxAlmEventArgs::Type type, Event& event, T* target, void (T::*implFunction)(), function<void(ofxAlmEventArgs&)>& callback) {
			if (isVerbose) ofLogVerbose() << "ofxAlmInteractiveBox : '" << name << "' " << ofxAlmEventArgs::getTypeName(type);
			ofxAlmEventArgs eventArgs(type, target);
			if (callback != nullptr) {
				callback(eventArgs);
			} else {
				(target->*implFunction)();
			}
			ofNotifyEvent(event, eventArgs);
		};
		
	private:
		void checkMouseOver();
		void clearCallback();
		
		void mouseMovedHandler(ofMouseEventArgs &event);
		void mouseDraggedHandler(ofMouseEventArgs &event);
		void mousePressedHandler(ofMouseEventArgs &event);
		void mouseReleasedHandler(ofMouseEventArgs &event);
		void keyPressedHandler(ofKeyEventArgs &event);
		void keyReleasedHandler(ofKeyEventArgs &event);
	};
}

