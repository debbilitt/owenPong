//
//  owen.h
//  OwenPong
//
//  Created by Debbi Litt on 5/3/18.
//

#ifndef owen_hp
#define owen_hp
#include "ofMain.h"
#include <stdio.h>

class Owen {
    
public:
    

    void setup(float x, float y);
    void update();
    void draw();

    void bounceHead(); //check its distance to the other vector

    bool bouncedOwen;
    
    
    /*variables*/
    float pointX;   // position
    float pointY;
    float speedY;   // speed
    float speedX;
    float prevx;   // previous location, not sure if I need this 
    float prevy;
   
    ofVec2f speed;
    ofVec2f position;
    
    /*sound files*/
    ofSoundPlayer wow1;
    ofSoundPlayer wow2;
    ofSoundPlayer wow3;
    ofSoundPlayer wow4;
    
    /*load an owen*/
    ofImage owen;
    ofImage bOwen;

    
    
    /*texture wrapping*/
    
    ofSpherePrimitive mSphere;
    ofTexture mTexture;
    ofTexture mTexture2;

    
    Owen();  //constructor
    
    
    
private:
};

#endif /* owen_h */
