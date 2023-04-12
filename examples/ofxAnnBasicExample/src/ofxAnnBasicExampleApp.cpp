#include "ofxAnnBasicExampleApp.h"
#include <iostream>

//--------------------------------------------------------------
void ofxAnnBasicExampleApp::setup(){
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    ofEnableSmoothing();
    
    points::iterator pit;
    for ( pit = allPoints.begin(); pit != allPoints.end(); pit++ ) {
        pit->randomize();
    }
}

//--------------------------------------------------------------
void ofxAnnBasicExampleApp::update(){
    if ( numPoints != allPoints.size() ) {
        allPoints.resize(numPoints);
    }
    
    points::iterator pit;
    for ( pit = allPoints.begin(); pit != allPoints.end(); pit++ ) {
        pit->update();
    }
    
    ann_allPoints.buildIndex();
}

//--------------------------------------------------------------
void ofxAnnBasicExampleApp::draw(){
    ofBackground(3, 43, 55);
    
    int start = ofGetElapsedTimeMillis();
    
    points::iterator pit;
    for ( pit = allPoints.begin(); pit != allPoints.end(); pit++ ) {
        ofPoint center = pit->getPoint();
        
        // nearest neighbors in a threshold
        ofPoint m = { ofGetMouseX(), ofGetMouseY() };
        float threshold = 10000.f;
        bool isNeighbor = false;
        ann_points::result_radius neighborsRadius = ann_allPoints.findWithin(m, threshold);
        for ( auto &n : neighborsRadius.data ) {
            if ( center == allPoints[n.first].getPoint() ) {
                isNeighbor = true;
                break;
            }
        }

        // draw the point itself
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(4);
        if ( !isNeighbor ) {
            ofSetColor(ofColor::cyan, 100);
        } else {
            ofSetColor(ofColor::red, 100);
        }
        
        ofCircle(center, 10);
        ofPopStyle();

        //draw threshold
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(1);
        ofSetColor(ofColor::red, 100);
        ofCircle( m, sqrt(threshold));
        ofPopStyle();

        
        // draw lines to its nearest neighbors
        ofPushStyle();
        ofSetLineWidth(2);
        ofSetColor(ofColor::magenta, 75);
        
        ann_points::result_knn neighbors = ann_allPoints.findNeighbors(m, 5);
        for (neighbors.indices_it = neighbors.indices.begin();
             neighbors.indices_it != neighbors.indices.end();
             neighbors.indices_it++)
        {
            ofPoint neighborCenter = allPoints[*neighbors.indices_it].getPoint();
            ofLine(m, neighborCenter);
        }
        
        ofPopStyle();
    }
    
    int done = ofGetElapsedTimeMillis();
    
    ostringstream info;
    info << "Draw took " << done - start << "ms";
    info << "\npress the up arrow for more nodes, down for fewer";
    ofPushStyle();
    ofSetColor(ofColor::white);
    ofDrawBitmapString(info.str(), 10, 20);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxAnnBasicExampleApp::keyPressed(int key){
    if ( key == OF_KEY_UP ) {
        numPoints += 5;
    } else if ( key == OF_KEY_DOWN ) {
        if ( numPoints > 5 ) {
            numPoints -= 5;
        }
    }
}

//--------------------------------------------------------------
void ofxAnnBasicExampleApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofxAnnBasicExampleApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofxAnnBasicExampleApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofxAnnBasicExampleApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofxAnnBasicExampleApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofxAnnBasicExampleApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofxAnnBasicExampleApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofxAnnBasicExampleApp::dragEvent(ofDragInfo dragInfo){ 

}