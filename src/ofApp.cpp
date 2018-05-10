#include "ofApp.h"
#include "owen.h"

//--------------------------------------------------------------
void ofApp::setup(){

    /*setup video*/
    myVideoGrabber.setup(ofGetWidth(),ofGetHeight());
    
    myColorImage.allocate(myVideoGrabber.getWidth(),myVideoGrabber.getHeight());
    myGrayscaleImage.allocate(myVideoGrabber.getWidth(),myVideoGrabber.getHeight());
    myBackground.allocate(myVideoGrabber.getWidth(),myVideoGrabber.getHeight());
    grayDifference.allocate(myVideoGrabber.getWidth(),myVideoGrabber.getHeight());
    
    
    bLearnBackground = true;
    threshold = 20;
    ofSetBackgroundAuto(false);
 
    
   /*owen object setup*/
    
    for(int i=0; i<multiOwens.size(); i++){
        
        int randomX = ofRandom(0, ofGetWidth() );
        int randomY = ofRandom(0, ofGetHeight() );
        
        multiOwens[i].setup(randomX, randomY);
    }
    


}

//--------------------------------------------------------------
void ofApp::update(){

    
    /*webcam updating*/
    
    bool bNewFrame = false;
    
    myVideoGrabber.update();
    
    bNewFrame = myVideoGrabber.isFrameNew();
    
    
    if(bNewFrame){
        
        myColorImage.setFromPixels(myVideoGrabber.getPixels());
        myColorImage.mirror(false, true);
        
        myGrayscaleImage = myColorImage; //operator overloading
        
        if (bLearnBackground == true) {
            myBackground = myGrayscaleImage;
            bLearnBackground = false;
            
        }
        
        grayDifference.absDiff(myBackground, myGrayscaleImage);
        grayDifference.threshold(threshold);
        
    }
    
    
    myContourFinder.findContours(grayDifference, 10, (myVideoGrabber.getWidth()*myVideoGrabber.getHeight())/3, 2, true);

    /*end webcam*/
    
   /*update owen object*/
       for(int i=0; i<multiOwens.size(); i++){
            multiOwens[i].update();
       }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(ofColor::dimGray);
    
    ofSetColor(ofColor::white);
    
    ofPushMatrix();
    
    if (bShowVideo) {
        
        myColorImage.draw(0,0);
        //   grayDifference.draw(myColorImage.getWidth()+100,0);

        
    }


    /*draw bounding rectangle of blobs for debugging*/

//        myContourFinder.draw(0, 0, ofGetWidth(), ofGetHeight());
//        for(int i = 0; i < myContourFinder.nBlobs; i++) {
//            ofRectangle r = myContourFinder.blobs.at(i).boundingRect;
//    
//        }

    
 /*full contour detection seems to work best*/
    
    
//  ofNoFill();
//  ofSetColor(ofColor::orange);
//  ofBeginShape();
//
    /* loop through each of the detected blobs*/
    /*contourFinder.nBlobs gives us the number of detected blobs*/
    for (int i = 0; i < myContourFinder.nBlobs; i++){
       
    	for(auto &blob : myContourFinder.blobs){
            
    		vector<ofPoint> pts = blob.pts;
    		for(auto pt : pts){
//               ofVertex(pt.x, pt.y);
    
                ofVec2f temp_contour;
                temp_contour.set(pt.x,pt.y);
    
    /* check distance to owen's head: */

                for (int i =0; i < multiOwens.size(); i++) {
                                        
                  ofVec2f owenPos;
                  owenPos.set(multiOwens[i].pointX, multiOwens[i].pointY);

                  float distance = owenPos.distance(temp_contour);
                    
                    /*if owen is close to body, bounce owen's head*/

                    if (distance < 20) {
                        multiOwens[i].bounceHead();
                    }
                }

    		}
    	}

    }

//ofEndShape();
    


ofPopMatrix();
 
    
    ofPushMatrix();
    ofSetColor(ofColor::blueSteel); /*the obvious choice*/
    ofDrawBitmapString("Click to add an owen", 5, 10);
    ofDrawBitmapString("Press w to toggle video and s to reset video background", 5, 30);
    ofDrawBitmapString("Press d to remove one Owen or r to reset to 0", 5, 50);
    ofPopMatrix();
    
    
    ofSetColor(ofColor::white);
    for(int i=0; i<multiOwens.size(); i++){
        multiOwens[i].draw();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){


    /*toggle background, remove owens, adjust threshold*/
    switch (key){
        case 'w':
            ofBackground(ofColor::white);
            bShowVideo = !bShowVideo;
            break;
        case 's':
            bLearnBackground = true;
            //also clears your owens
        case 'd':
            for (int i =0; i < multiOwens.size(); i++) {
            multiOwens.erase(multiOwens.begin()+i);
            }
            break;
        case 'r':
            for (int i =0; i < multiOwens.size(); i++) {
                multiOwens.clear();
            }
            break;
        case '+':
            threshold ++;
            if (threshold > 255) threshold = 255;
            break;
        case '-':
            threshold --;
            if (threshold < 0) threshold = 0;
            break;
            
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){


}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    


}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    Owen tempOwen;
    tempOwen.setup(x,y);	// setup its initial state
    multiOwens.push_back(tempOwen);


}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
