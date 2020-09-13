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

#include "NumberObject.h"

//--------------------------------------------------------------
NumberObject::NumberObject() : PatchObject("number object"){

    // SET YOUR INLETS/OUTLETS
    this->numInlets  = 1;
    this->numOutlets = 1;

    _inletParams[0] = new float();  // input
    *(float *)&_inletParams[0] = 0.0f;

    _outletParams[0] = new float(); // output
    *(float *)&_outletParams[0] = 0.0f;

    this->initInletsState();

    startTime = ofGetElapsedTimeMillis();
    wait = 200;

}

//--------------------------------------------------------------
void NumberObject::newObject(){
    // SET OBJECT NAME AND INLETS/OUTLETS TYPES/NAMES
    PatchObject::setName( this->objectName );

    this->addInlet(VP_LINK_NUMERIC,"number");

    this->addOutlet(VP_LINK_NUMERIC,"number");
}

//--------------------------------------------------------------
void NumberObject::setupObjectContent(shared_ptr<ofAppGLFWWindow> &mainWindow){
    //////////////////////////////////////////////
    // LINK SHARED RENDERER
    mainRenderer.setup(mainWindow->renderer());
    //////////////////////////////////////////////

    //////////////////////////////////////////////
    // YOUR SETUP CODE


    //////////////////////////////////////////////
}

//--------------------------------------------------------------
void NumberObject::updateObjectContent(map<int,shared_ptr<PatchObject>> &patchObjects){

    //////////////////////////////////////////////
    // YOUR UPDATE CODE
    if(this->inletsConnected[0]){
        *(float *)&_outletParams[0] = *(float *)&_inletParams[0];
    }
    //////////////////////////////////////////////

}

//--------------------------------------------------------------
void NumberObject::drawObjectContent(ofxFontStash *font, shared_ptr<ofBaseGLRenderer>& glRenderer){

    /*
        Due to rendering sharing needs, use internal mpGraphics methods
        instead of starndard OF methods for drawing

        ex. ofSetColor --> mainRenderer.ofSetColor()
            or:
        ofVideoPlayer video;
        video.load("video.mp4");

        video.draw(0,0); --> mainRenderer.draw(video,0,0);
     */

    //////////////////////////////////////////////
    // YOUR DRAW CODE
    mainRenderer.ofSetColor(255,255,255);
    //////////////////////////////////////////////

}

//--------------------------------------------------------------
void NumberObject::drawObjectNodeGui( ImGuiEx::NodeCanvas& _nodeCanvas ){

    ImGui::SetCurrentContext(_nodeCanvas.getContext());

    // CONFIG GUI inside Menu
    if(_nodeCanvas.BeginNodeMenu()){

        ImGui::Separator();
        ImGui::Separator();
        ImGui::Separator();

        if (ImGui::BeginMenu("CONFIG"))
        {

            drawObjectNodeConfig();

            ImGui::EndMenu();
        }

        _nodeCanvas.EndNodeMenu();
    }

    // Visualize (Object main view)
    if( _nodeCanvas.BeginNodeContent(ImGuiExNodeView_Visualise) ){



        _nodeCanvas.EndNodeContent();
    }

}

//--------------------------------------------------------------
void NumberObject::drawObjectNodeConfig(){
    // delay needed for some strange bug related with inspector??? ( crash when creating object with inspector already open ONLY ) - Need to check why
    if(ofGetElapsedTimeMillis()-startTime > wait){
        ImGuiEx::ObjectInfo(
                    "Mosaic Plugin Example - Number object.",
                    "#", scaleFactor);
    }
}

//--------------------------------------------------------------
void NumberObject::removeObjectContent(bool removeFileFromData){

}


// REGISTER THE OBJECT
OBJECT_REGISTER( NumberObject, "number object", OFXVP_OBJECT_CAT_DATA)
