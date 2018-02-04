#pragma once

#include "ofMain.h"

namespace alm {
	
	class ofxAlmInteractiveBox;
	
	class ofxAlmEventArgs : public ofEventArgs {
		
		// ----------------------------------------
		//
		// FIELD
		//
		// ----------------------------------------
		
	public:
		enum Type {
			// ofxAlmInteractiveBox
			Enabled,
			Disabled,
			MouseOver,
			MouseOut,
			MouseDown,
			MouseUp,
			DragOver,
			DragOut,
			DragDrop,
			DragBegin,
			DragMove,
			DragEnd,
			Click,
			ReleaseOutside,
			KeyPressed,
			KeyReleased,
			// ofxAlmButton
			Visible,
			Hidden,
		};
		
		Type type;
		ofxAlmInteractiveBox* target;
		
	protected:
		
	private:
		static const string typeNames[];
		
		
		
		
		
		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------
		
	public:
		ofxAlmEventArgs();
		ofxAlmEventArgs(Type type, ofxAlmInteractiveBox* target);
		virtual ~ofxAlmEventArgs();
		
		string getTypeName();
		static string getTypeName(Type type);
		
	protected:
		
	private:
	};
}

