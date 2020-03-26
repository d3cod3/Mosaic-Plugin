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

    _inletParams[0] = new ofTexture();  // input

    _outletParams[0] = new ofTexture(); // output

    this->initInletsState();

    posX = posY = drawW = drawH = 0.0f;

    isTexInited = false;
}

//--------------------------------------------------------------
void VideoObject::newObject(){
    // SET OBJECT NAME AND INLETS/OUTLETS TYPES/NAMES
    this->setName(this->objectName);
    this->addInlet(VP_LINK_TEXTURE,"texture");
    this->addOutlet(VP_LINK_TEXTURE,"texture");
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
    if(this->inletsConnected[0] && static_cast<ofTexture *>(_inletParams[0])->isAllocated()){
        if(!isTexInited){
            isTexInited = true;
            bridgeIn1.allocate(static_cast<ofTexture *>(_inletParams[0])->getWidth(),static_cast<ofTexture *>(_inletParams[0])->getHeight(),static_cast<ofTexture *>(_inletParams[0])->getTextureData().glInternalFormat);
        }
        bridgeIn1 = *static_cast<ofTexture *>(_inletParams[0]);
        *static_cast<ofTexture *>(_outletParams[0]) = bridgeIn1;
    }else{
        isTexInited = false;
    }
    //////////////////////////////////////////////

}

//--------------------------------------------------------------
void VideoObject::drawObjectContent(ofxFontStash *font, shared_ptr<ofBaseGLRenderer>& glRenderer){

    /*
        Due to renderer sharing needs, use internal mpGraphics methods
        instead of starndard OF methods for drawing

        ex. ofSetColor --> mainRenderer.ofSetColor()
     */

    //////////////////////////////////////////////
    // YOUR DRAW CODE

    mainRenderer.ofSetColor(255,255,255);

    mainRenderer.ofEnableAlphaBlending();

    if(this->inletsConnected[0] && static_cast<ofTexture *>(_inletParams[0])->isAllocated()){
        if(static_cast<ofTexture *>(_inletParams[0])->getWidth()/static_cast<ofTexture *>(_inletParams[0])->getHeight() >= this->width/this->height){
            if(static_cast<ofTexture *>(_inletParams[0])->getWidth() > static_cast<ofTexture *>(_inletParams[0])->getHeight()){   // horizontal texture
                drawW           = this->width;
                drawH           = (this->width/static_cast<ofTexture *>(_inletParams[0])->getWidth())*static_cast<ofTexture *>(_inletParams[0])->getHeight();
                posX            = 0;
                posY            = (this->height-drawH)/2.0f;
            }else{ // vertical texture
                drawW           = (static_cast<ofTexture *>(_inletParams[0])->getWidth()*this->height)/static_cast<ofTexture *>(_inletParams[0])->getHeight();
                drawH           = this->height;
                posX            = (this->width-drawW)/2.0f;
                posY            = 0;
            }
        }else{ // always considered vertical texture
            drawW           = (static_cast<ofTexture *>(_inletParams[0])->getWidth()*this->height)/static_cast<ofTexture *>(_inletParams[0])->getHeight();
            drawH           = this->height;
            posX            = (this->width-drawW)/2.0f;
            posY            = 0;
        }
        glRenderer->draw(bridgeIn1,posX,posY,0,drawW,drawH,0,0,static_cast<ofTexture *>(_inletParams[0])->getWidth(),static_cast<ofTexture *>(_inletParams[0])->getHeight());
    }

    mainRenderer.ofDisableAlphaBlending();
    //////////////////////////////////////////////

}

//--------------------------------------------------------------
void VideoObject::removeObjectContent(bool removeFileFromData){

}


// REGISTER THE OBJECT
OBJECT_REGISTER( VideoObject, "video object", OFXVP_OBJECT_CAT_VIDEO)
