//
//  owen.cpp
//  OwenPong
//
//  Created by Debbi Litt on 5/3/18.
//

#include "owen.h"

Owen::Owen(){

};


void Owen::setup(float x, float y){
 
    pointX = x;
    pointY = y;
    
    position = ofVec2f(pointX,pointY);
    
    speedX 	= ofRandom(-1,1);
    speedY 	= ofRandom(-1,1);

    /*image loading*/
    
    owen.load("ow.png");
    bOwen.load("ow2.png");
    
    
    /*load sounds*/
    wow1.load("16.mp3");
    wow1.setMultiPlay(true);
    
    wow2.load("1.mp3");
    wow2.setMultiPlay(true);
    
    wow3.load("2.mp3");
    wow3.setMultiPlay(true);
    
    wow4.load("4.mp3");
    wow4.setMultiPlay(true);

    
    
    
    /*sphere owen*/
    
        ofLoadImage(mTexture, "owen-wrap1.png");
        ofLoadImage(mTexture2, "owen-wrap2.png");

        mSphere.setRadius(45);
    
        mTexture.setTextureWrap(GL_NEAREST,GL_NEAREST);
        mTexture.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    
        mTexture2.setTextureWrap(GL_NEAREST,GL_NEAREST);
        mTexture2.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    
        mSphere.mapTexCoordsFromTexture(mTexture);
    
        mSphere.mapTexCoordsFromTexture(mTexture2);
    
        ofEnableDepthTest();
    
    
    
}

void Owen::update(){
    

    /* increase x and y by adding speedX and speedY*/
    pointX += speedX;
    pointY += speedY;

    /*  check for collision, and trigger sounds: */

    if (pointX <= 0){
        speedX *= -1.0f;
        wow1.play();
            ofLog() << pointX << endl;
    } else if (pointX >= ofGetWidth()){
        speedX *= -1.0f;
        wow2.play();
            ofLog() << pointX << endl;
    }

    if (pointY <= 0 ){
        speedY *= -1.0f;
        wow3.play();
            ofLog() << pointY << endl;
    } else if (pointY >= ofGetHeight()){
        speedY *= -1.0f;
        wow4.play();
        ofLog() << pointY << endl;
    }




}

void Owen::draw(){
    
    
    /*draw owen img only using this for debug*/
    
//    ofPushMatrix();
//
//    ofTranslate(pointX, pointY);
//    
//        if(bouncedOwen){
//      bOwen.draw(0,0);
//        } else {
//      owen.draw(0,0);
//            
//        }
//    ofPopMatrix();
    
    /*texture binding on sphere*/
    
    ofPushMatrix();
            float spinX = sin(ofGetElapsedTimef()*.35f);
            float spinY = cos(ofGetElapsedTimef()*.075f);
    
    
            ofTranslate(pointX, pointY);
    
    
    if(!bouncedOwen){
            mTexture.bind();
    
            mSphere.draw(ofPolyRenderMode::OF_MESH_FILL);
    
            mSphere.rotate(spinX,1.0,0.0,0.0);
            mSphere.rotate(spinY,0,1.0,0.0);
        
            mTexture.unbind();
    
    } else {
    
        mTexture2.bind();
        
        mSphere.draw(ofPolyRenderMode::OF_MESH_FILL);
        
        mSphere.rotate(spinX,1.0,0.0,0.0);
        mSphere.rotate(spinY,0,1.0,0.0);
        
        mTexture2.unbind();
    
    }
    
    
    

    ofPopMatrix();
    
}

/*this is working yay!*/

void Owen::bounceHead(){

    bouncedOwen = true;
    
    speedX ++;
    speedY ++;
    
    
    //control the speed if Owen gets too fast
    
    speedX *= 0.96f;
    speedY *= 0.96f;
    

    
    
    
}


