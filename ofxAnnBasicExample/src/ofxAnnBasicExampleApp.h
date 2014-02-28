#pragma once

#include "ofMain.h"
#include "ofxAnn.h"
#include <algorithm>

class ofxAnnBasicExampleApp : public ofBaseApp{
public:
    ofxAnnBasicExampleApp() :
    // set the initial number of points
    numPoints(100),
    // allocate all the points
    allPoints(points(numPoints)),
    // initialize the ANN index by passing it the container to be searched,
    // allPoints
    ann_allPoints(ann_points(allPoints))
    {  }
    
    class Point {
    public:
        Point() :
        point(ofPoint(-1, -1))
        { }
        void randomize() { point = ofPoint(ofRandomWidth(), ofRandomHeight()); }
        void update()
        {
            if ( point.x == -1 && point.y == -1 ) {
                randomize();
            }
            
            float d = 2.f;
            point.x = std::max(std::min(point.x + ofRandom(-d, d),
                                        (float)ofGetWidth()),
                               0.f);
            point.y = std::max(std::min(point.y + ofRandom(-d, d),
                                        (float)ofGetHeight()),
                               0.f);
        }
        
        // getPoint() is the one callback that must be implemented by the class
        // of objects in the collection passed to ofxAnn below.
        inline const ofPoint getPoint() const { return point; }
        
    private:
        ofPoint point;
    };
    
    // a type for a container of points, to be passed to ofxAnn
    typedef vector< Point > points;
    // a type for the ofxAnn class that searches a collection of points
    typedef ofxAnn< points > ann_points;
    
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
    int numPoints;
    points allPoints;
    ann_points ann_allPoints;
};
