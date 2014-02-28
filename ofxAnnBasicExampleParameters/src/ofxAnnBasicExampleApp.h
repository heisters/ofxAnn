#pragma once

#include "ofMain.h"
#include "ofxAnn.h"
#include <algorithm>

class ofxAnnBasicExampleApp : public ofBaseApp{
public:
    
    ofxAnnBasicExampleApp();
    
    //--parameter--------------------------
    class Parameter {
    public:
        Parameter()
        {}
        
        void addValue(float _value) {
            values.push_back(_value);
        }
        
        inline const vector<float> getValues() const { return values; }
        
    private:
        vector<float> values;
    };
    typedef vector< Parameter > parameters;
    typedef ofxAnn< parameters > ann_parameters;
    
    //--of----------------------------------
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private:
    
    int numParameters;
    parameters allParameters;
    ann_parameters ann_allParameters;
};
