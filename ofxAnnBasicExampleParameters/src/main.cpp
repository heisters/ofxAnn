#include "ofxAnnBasicExampleApp.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main(){
    ofSetLogLevel(OF_LOG_VERBOSE); // set it here so app can log immediately
    
	ofAppGlutWindow window; // create a window
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
	ofRunApp(new ofxAnnBasicExampleApp()); // start the app
}
