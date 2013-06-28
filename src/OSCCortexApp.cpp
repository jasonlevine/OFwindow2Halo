#include "OSCCortexApp.h"

#define ANIMATION_DURATION 6.

//--------------------------------------------------------------
void OSCCortexApp::setup(){

	ofBackground(40, 100, 40);
    ofSetFrameRate(30);
    mTimer = 0.f;
	// open an outgoing connection to HOST:PORT
	sender.setup(HOST, PORT);
    
    camWidth 		= 320;	// try to grab at this size.
	camHeight 		= 240;
	
	vidGrabber.setVerbose(true);
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth,camHeight);
}

//--------------------------------------------------------------
void OSCCortexApp::update()
{
    /*
    if(mTimer > ANIMATION_DURATION)
    {
        mTimer = 0.f;
        mControlType++;
        mControlType = mControlType % CONTROL_TYPE_COUNT;
    }
    
    float coeffTimer = mTimer / ANIMATION_DURATION;
    switch(mControlType)
    {
        case CONTROL_TYPE_HALO:
            for(int y = 0; y < 6; y++)
            {
                ControlHalo(12. * ((y % 2) ? coeffTimer : 1. - coeffTimer), y, ofColor(255,0,0), .4);
                ControlHalo(12. * ((y % 2) ? coeffTimer - 0.2 : 1. - coeffTimer + 0.2), y, ofColor(0,0,0), .4);
            }
            break;
        case CONTROL_TYPE_LED:
            for(int y = 0; y < 6; y++)
            {
                for(int x = 0; x < 12; x++)
                {
                    ControlLED(x, y, (int)(coeffTimer * (x + 1) * (y + 1) * 2.) % 31, ofColor(255,0,255), .2);
                    ControlLED(x, y, (int)((coeffTimer - 0.1) * (x + 1) * (y + 1) * 2.) % 31,  ofColor(0,0,0), .2);
                }
            }
            break;
        case CONTROL_TYPE_COLUMN:
            ControlColumn((int)(sin(coeffTimer * M_PI) * 12.), ofColor(0,255,0), 1.);
            coeffTimer -= 0.2;
            ControlColumn((int)(sin(coeffTimer * M_PI) * 12.), ofColor(0,0,0), 1.);
            break;
        case CONTROL_TYPE_ROW:
            ControlRow((int)(sin(coeffTimer * M_PI) * 6.), ofColor(0,0,255), 1.);
            coeffTimer -= 0.2;
            ControlRow((int)(sin(coeffTimer * M_PI) * 6.), ofColor(0,0,0), 1.);
            break;
        case CONTROL_TYPE_AREA:
            ControlArea(0.5, 0., 1.7 * coeffTimer, ofColor(0,255,255), 0.);
            break;
        case CONTROL_TYPE_ALL_BLACK:
        case CONTROL_TYPE_ALL_BLACK_2:
        case CONTROL_TYPE_ALL_BLACK_3:
            for(int i = 0; i < 6; i++)
            {
                ControlRow(i, ofColor(0,0,0), 1.);
            }
            mTimer = mTimer < 1. ? ANIMATION_DURATION - 1. : mTimer;
            break;
    }
    mTimer += 0.03;
     */
    
    vidGrabber.update();
}

//--------------------------------------------------------------
void OSCCortexApp::draw()
{
    ofSetColor(255);
    vidGrabber.draw(0, 0, 640, 480);
    if (vidGrabber.isFrameNew()) {
        framePix.clear();
        framePix = vidGrabber.getPixelsRef();
        
        ofSetColor(0);
        ofNoFill();
        float width = 640.0 / 12.0;
        float height = 480.0 / 6.0;
        
        for (int i = 0; i < 6; i++) {
            
            for (int j = 0; j < 12; j++) {
                float x = ofMap(j, 0, 12, 0, 640);
                float y = ofMap(i, 0, 6, 0, 480);
                
                ofRect( x, y, width, height);
                
                ofVec2f haloCenter(x + width /2, y + height / 2);
                ofCircle(haloCenter, 3);
                
                ofVec2f ledZero(0,1);
                
                for (int k = 0; k < 31; k++) {
                    float angle = ofMap(k, 0, 31, 0, 360);
                    ofVec2f dir = ledZero.getRotated(angle);
                    dir.y*=2;
                    dir*=16;
                    ofLine(haloCenter, haloCenter + dir);
                    
                    ControlLED(j, i, k, framePix.getColor((haloCenter.x + dir.x)/2, (haloCenter.y + dir.y)/2), 0.0);
                }
                
                
                //            ControlHalo(j, i, framePix.getColor(x/2, y/2), 0.0);
            }
        }

    }
}

//--------------------------------------------------------------
void OSCCortexApp::keyPressed(int key){

}


void OSCCortexApp::ControlHalo(int aX, int aY, ofColor aColor, float aDuration)
{
    ofxOscMessage message;
    message.setAddress("/halo");
	message.addIntArg(aX);
    message.addIntArg(aY);
    message.addFloatArg(aColor.r / 255.);
    message.addFloatArg(aColor.g / 255.);
    message.addFloatArg(aColor.b / 255.);
    message.addFloatArg(aDuration);
	sender.sendMessage(message);
}

void OSCCortexApp::ControlLED(int aX, int aY, int aIndexLED, ofColor aColor, float aDuration)
{
    ofxOscMessage message;
    message.setAddress("/led");
	message.addIntArg(aX);
    message.addIntArg(aY);
    message.addIntArg(aIndexLED);
    message.addFloatArg(aColor.r / 255.);
    message.addFloatArg(aColor.g / 255.);
    message.addFloatArg(aColor.b / 255.);
    message.addFloatArg(aDuration);
	sender.sendMessage(message);
}

void OSCCortexApp::ControlRow(int aRow, ofColor aColor, float aDuration)
{
    ofxOscMessage message;
    message.setAddress("/row");
	message.addIntArg(aRow);
    message.addFloatArg(aColor.r / 255.);
    message.addFloatArg(aColor.g / 255.);
    message.addFloatArg(aColor.b / 255.);
    message.addFloatArg(aDuration);
	sender.sendMessage(message);
}

void OSCCortexApp::ControlColumn(int aColumn, ofColor aColor, float aDuration)
{
    ofxOscMessage message;
    message.setAddress("/column");
	message.addIntArg(aColumn);
    message.addFloatArg(aColor.r / 255.);
    message.addFloatArg(aColor.g / 255.);
    message.addFloatArg(aColor.b / 255.);
    message.addFloatArg(aDuration);
	sender.sendMessage(message);
}

void OSCCortexApp::ControlArea(float aX, float aY, float aRadius, ofColor aColor, float aDuration)
{
    ofxOscMessage message;
    message.setAddress("/area");
	message.addFloatArg(aX);
    message.addFloatArg(aY);
    message.addFloatArg(aRadius);
    message.addFloatArg(aColor.r / 255.);
    message.addFloatArg(aColor.g / 255.);
    message.addFloatArg(aColor.b / 255.);
    message.addFloatArg(aDuration);
	sender.sendMessage(message);
}

//--------------------------------------------------------------
void OSCCortexApp::keyReleased(int key){

}

//--------------------------------------------------------------
void OSCCortexApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void OSCCortexApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void OSCCortexApp::mousePressed(int x, int y, int button){
	ofxOscMessage m;
	m.setAddress("/mouse/button");
	m.addStringArg("down");
	sender.sendMessage(m);
}

//--------------------------------------------------------------
void OSCCortexApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void OSCCortexApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void OSCCortexApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void OSCCortexApp::dragEvent(ofDragInfo dragInfo){

}

