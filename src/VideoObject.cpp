/*==============================================================================

    ofxVisualProgramming: A visual programming patching environment for OF

    Copyright (c) 2020 Emanuele Mazza aka n3m3da <emanuelemazza@d3cod3.org>

    ofxVisualProgramming is distributed under the MIT License.
    This gives everyone the freedoms to use ofxVisualProgramming in any context:
    commercial or non-commercial, public or private, open or closed source.

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.

    See https://github.com/d3cod3/ofxVisualProgramming for documentation

==============================================================================*/

#include "VideoObject.h"

//--------------------------------------------------------------
VideoObject::VideoObject() : PatchObject(){

    // SET YOUR INLETS/OUTLETS
    this->numInlets  = 1;
    this->numOutlets = 1;

    _inletParams[0] = new ofPixels();  // input

    _outletParams[0] = new ofPixels(); // output

    this->initInletsState();

    isTexInited = false;

}

//--------------------------------------------------------------
void VideoObject::newObject(){
    // SET OBJECT NAME AND INLETS/OUTLETS TYPES/NAMES
    this->setName(this->objectName);
    this->addInlet(VP_LINK_PIXELS,"pixels");
    this->addOutlet(VP_LINK_PIXELS,"pixels");
}

//--------------------------------------------------------------
void VideoObject::setupObjectContent(shared_ptr<ofAppGLFWWindow> &mainWindow){
    //////////////////////////////////////////////
    // LINK SHARED RENDERER
    mainRenderer.setup(mainWindow->renderer());
    //////////////////////////////////////////////

    //////////////////////////////////////////////
    // YOUR SETUP CODE

    //////////////////////////////////////////////
}

//--------------------------------------------------------------
void VideoObject::updateObjectContent(map<int,shared_ptr<PatchObject>> &patchObjects, ofxThreadedFileDialog &fd){

    //////////////////////////////////////////////
    // YOUR UPDATE CODE
    if(this->inletsConnected[0]){
        if(!isTexInited){
            isTexInited = true;
            if(static_cast<ofPixels *>(_inletParams[0])->getBitsPerPixel() == 8){
                test.allocate(static_cast<ofPixels *>(_inletParams[0])->getWidth(),static_cast<ofPixels *>(_inletParams[0])->getHeight(),GL_LUMINANCE);
            }else if(static_cast<ofPixels *>(_inletParams[0])->getBitsPerPixel() == 24){
                test.allocate(static_cast<ofPixels *>(_inletParams[0])->getWidth(),static_cast<ofPixels *>(_inletParams[0])->getHeight(),GL_RGB);
            }else if(static_cast<ofPixels *>(_inletParams[0])->getBitsPerPixel() == 32){
                test.allocate(static_cast<ofPixels *>(_inletParams[0])->getWidth(),static_cast<ofPixels *>(_inletParams[0])->getHeight(),GL_RGBA);
            }

        }
        // get data from ofPixels inlet
        test.loadData(*static_cast<ofPixels *>(_inletParams[0]));

        // do some work on your internal ofTexture
        // ...........

        // copy back ofTexture data to ofPixels outlet
        test.readToPixels(*static_cast<ofPixels *>(_outletParams[0]));
    }else{
        isTexInited = false;
    }
    //////////////////////////////////////////////

}

//--------------------------------------------------------------
void VideoObject::drawObjectContent(ofxFontStash *font){

    /*
        Due to renderer sharing needs, use internal mpGraphics methods
        instead of starndard OF methods for drawing

        ex. ofSetColor --> mainRenderer.ofSetColor()
     */

    //////////////////////////////////////////////
    // YOUR DRAW CODE

    mainRenderer.ofSetColor(255,255,255);

    mainRenderer.ofEnableAlphaBlending();

    mainRenderer.ofDisableAlphaBlending();
    //////////////////////////////////////////////

}

//--------------------------------------------------------------
void VideoObject::removeObjectContent(bool removeFileFromData){

}


// REGISTER THE OBJECT
OBJECT_REGISTER( VideoObject, "video object", OFXVP_OBJECT_CAT_VIDEO)
