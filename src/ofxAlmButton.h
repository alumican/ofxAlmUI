#pragma once

#include "ofMain.h"
#include "ofxAlmInteractiveBox.h"

namespace alm {
	
	class ofxAlmButton : public ofxAlmInteractiveBox {
		
		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------
		
	public:
		// events
		ofEvent<ofxAlmEventArgs&> onVisible;
		ofEvent<ofxAlmEventArgs&> onHidden;
		
		// callbacks
		function<void(ofxAlmEventArgs&)> atVisible;
		function<void(ofxAlmEventArgs&)> atHidden;
		
	protected:
		
	private:
		bool isVisible;
		bool isAutoDraw;
		ofImage defaultImage;
		ofImage hoverImage;
		ofImage activeImage;
		ofImage disabledImage;
		
		
		
		
		
		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------
		
	public:
		ofxAlmButton();
		virtual ~ofxAlmButton();
		
		void setup();
		void setup(const string& defaultImage);
		void setup(const string& defaultImage, const string& hoverImage);
		void setup(const string& defaultImage, const string& hoverImage, const string& activeImage);
		void setup(const string& defaultImage, const string& hoverImage, const string& activeImage, const string& disabledImage);
		void setup(const ofImage& defaultImage);
		void setup(const ofImage& defaultImage, const ofImage& hoverImage);
		void setup(const ofImage& defaultImage, const ofImage& hoverImage, const ofImage& activeImage);
		void setup(const ofImage& defaultImage, const ofImage& hoverImage, const ofImage& activeImage, const ofImage& disabledImage);
		
		void setSizeByDefaultImage();
		void draw();
		
		bool getIsVisible() const;
		void setIsVisible(const bool visible);
		
		bool getIsAutoDraw() const;
		void setIsAutoDraw(const bool enabled);
		
		ofImage& getDefaultImage();
		void setDefaultImage(const string& path);
		void setDefaultImage(const ofImage& image);
		void clearDefaultImage();
		
		ofImage& getHoverImage();
		void setHoverImage(const string& path);
		void setHoverImage(const ofImage& image);
		void clearHoverImage();
		
		ofImage& getActiveImage();
		void setActiveImage(const string& path);
		void setActiveImage(const ofImage& image);
		void clearActiveImage();
		
		ofImage& getDisabledImage();
		void setDisabledImage(const string& path);
		void setDisabledImage(const ofImage& image);
		void clearDisabledImage();
		
	protected:
		// functions for overrided by sub class
		virtual void implVisible() {};
		virtual void implHidden() {};
		
	private:
		void clearCallback();
		
		void drawHandler(ofEventArgs &event);
	};
}

