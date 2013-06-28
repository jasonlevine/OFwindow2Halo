#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 1314

enum ControlType
{
    CONTROL_TYPE_HALO,
    CONTROL_TYPE_ALL_BLACK,
    CONTROL_TYPE_LED,
    CONTROL_TYPE_ROW,
    CONTROL_TYPE_COLUMN,
    CONTROL_TYPE_ALL_BLACK_2,
    CONTROL_TYPE_AREA,
    CONTROL_TYPE_ALL_BLACK_3,
    CONTROL_TYPE_COUNT,
};

//--------------------------------------------------------
class OSCCortexApp : public ofBaseApp {

	public:

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
    
        /*
         *  Send message to control a halo.
         *
         *  @param
         *  aX : x postion of the halo on the grid, from 0 to 11.
         *  aY : y postion of the halo on the grid, from 0 to 5.
         *  aColor : Color target, rgb format, values from 0. to 1.
         *  aDuration : Duration of the fading to this color in second.
         */
        void ControlHalo(int aX, int aY, ofColor aColor, float aDuration);
        
        /*
         *  Send message to control a LED.
         *
         *  @param
         *  aX : x postion of the halo on the grid, from 0 to 11.
         *  aY : y postion of the halo on the grid, from 0 to 5.
         *  aIndexLED : index of the LED on the halo, from 0 to 30.
         *  aColor : Color target, rgb format, values from 0. to 1.
         *  aDuration : Duration of the fading to this color in second.
         */
        void ControlLED(int aX, int aY, int aIndexLED, ofColor aColor, float aDuration);
        
        /*
         *  Send message to control a row.
         *
         *  @param
         *  aRow : index of the row, 0 is top, from 0 to 5.
         *  aColor : Color target, rgb format, values from 0. to 1.
         *  aDuration : Duration of the fading to this color in second.
         */
        void ControlRow(int aRow, ofColor aColor, float aDuration);
        
        /*
         *  Send message to control a column.
         *
         *  @param
         *  aColumn : index of the column, 0 is left, from 0 to 11.
         *  aIndexLED : index of the LED on the halo, from 0 to 30.
         *  aColor : Color target, rgb format, values from 0. to 1.
         *  aDuration : Duration of the fading to this color in second.
         */
        void ControlColumn(int aColumn, ofColor aColor, float aDuration);

        /*
         *  Send message to control all LEDs inside a circle area.
         *
         *  @param
         *  aX : x coordinate of the center of the circle.
         *  aY : y coordinate of the center of the circle.
         *  aRadius : radius of the circle.
         *  aColor : Color target, rgb format, values from 0. to 1.
         *  aDuration : Duration of the fading to this color in second.
         */
        void ControlArea(float aX, float aY, float aRadius, ofColor aColor, float aDuration);
    
        ofTrueTypeFont font;
        ofxOscSender sender;
        float mTimer;
        int mControlType;
    
    ofVideoGrabber vidGrabber;
    int camWidth, camHeight;
    ofPixels framePix;
    
};

