#include "ofxAnnBasicExampleApp.h"
#include <iostream>


//--------------------------------------------------------------
ofxAnnBasicExampleApp::ofxAnnBasicExampleApp( )
:
numParameters(100),
allParameters(parameters(numParameters)),
ann_allParameters(ann_parameters(allParameters))
{}

//--------------------------------------------------------------
void ofxAnnBasicExampleApp::setup(){
    
    ofSetFrameRate(60);

    //--train parameters
    parameters::iterator parit;
    for (parit = allParameters.begin(); parit != allParameters.end(); parit++) {
        cout << "setup parameter list: " << parit - allParameters.begin() << endl;
        parit->addValue(parit - allParameters.begin());
        parit->addValue(parit - allParameters.begin());
        parit->addValue(parit - allParameters.begin());
        parit->addValue(parit - allParameters.begin());
        parit->addValue(parit - allParameters.begin());
        parit->addValue(parit - allParameters.begin());
        parit->addValue(parit - allParameters.begin());
        parit->addValue(parit - allParameters.begin());
        parit->addValue(parit - allParameters.begin());
        parit->addValue(parit - allParameters.begin());
        parit->addValue(parit - allParameters.begin());
        parit->addValue(parit - allParameters.begin());
        parit->addValue(parit - allParameters.begin());
        parit->addValue(parit - allParameters.begin());
        parit->addValue(parit - allParameters.begin());
    }
}

//--------------------------------------------------------------
void ofxAnnBasicExampleApp::update(){
 
    //-para
    if(numParameters != allParameters.size()) {
        allParameters.resize(numParameters);
    }
    
    ann_allParameters.buildIndex();
    
}

//--------------------------------------------------------------
void ofxAnnBasicExampleApp::draw(){
    ofBackground(3, 43, 55);

}

//--------------------------------------------------------------
void ofxAnnBasicExampleApp::keyPressed(int key){
    
    
    if (key == ' ') {
        //--test parameter
        vector<float> newValue;
        newValue.push_back(11);
        newValue.push_back(11);
        newValue.push_back(11);
        newValue.push_back(11);
        newValue.push_back(11);
        newValue.push_back(11);
        newValue.push_back(11);
        newValue.push_back(11);
        newValue.push_back(11);
        newValue.push_back(11);
        newValue.push_back(11);
        newValue.push_back(11);
        newValue.push_back(11);
        newValue.push_back(11);
        newValue.push_back(11);
        
        //--neighbor search: new value again trained values
        ann_parameters::result_knn neighbors = ann_allParameters.findNeighbors(newValue, 3);
        
        //--for num neighbors specified and found
        for (neighbors.indices_it = neighbors.indices.begin();
             neighbors.indices_it != neighbors.indices.end();
             neighbors.indices_it++)
        {
            cout << "parameter id: " << *neighbors.indices_it << endl;
            vector<float> values = allParameters[*neighbors.indices_it].getValues();
            cout << "[0] " << values[0]
            << " \t[1] " << values[1]
            << " \t[2] " << values[2]
            << " \t[3] " << values[3]
            << " \t[4] " << values[4]
            << " \t[5] " << values[5]
            << " \t[6] " << values[6]
            << " \t[7] " << values[7]
            << " \t[8] " << values[8]
            << " \t[9] " << values[9]
            << " \t[10] " << values[10]
            << " \t[11] " << values[11]
            << " \t[12] " << values[12]
            << " \t[13] " << values[13]
            << " \t[14] " << values[14]
            << endl;
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