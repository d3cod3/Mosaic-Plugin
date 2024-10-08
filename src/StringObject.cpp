/*==============================================================================

    Mosaic: Live Visual Patching Creative-Coding Platform
    ofxVisualProgramming: A visual programming patching environment for OF

    Copyright (c) 2020 Emanuele Mazza aka n3m3da <emanuelemazza@d3cod3.org>

    Mosaic and ofxVisualProgramming is distributed under the MIT License.
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

    See https://github.com/d3cod3/Mosaic-Plugin for documentation

    Name:           StringObject

    Desc:           Mosaic Plugin Example - String object

    Developed by:   Emanuele Mazza aka n3m3da

    Github:         https://github.com/d3cod3
    WWW:            http://www.d3cod3.org

==============================================================================*/

#include "StringObject.h"

//--------------------------------------------------------------
StringObject::StringObject() : PatchObject("string object"){

    // SET YOUR INLETS/OUTLETS
    this->numInlets  = 1;
    this->numOutlets = 1;

    _inletParams[0] = new string();  // input
    *static_cast<string *>(_inletParams[0]) = "";

    _outletParams[0] = new string(); // output
    *static_cast<string *>(_outletParams[0]) = "";

    this->initInletsState();

    startTime = ofGetElapsedTimeMillis();
    wait = 200;

}

//--------------------------------------------------------------
void StringObject::newObject(){
    // SET OBJECT NAME AND INLETS/OUTLETS TYPES/NAMES
    PatchObject::setName( this->objectName );

    this->addInlet(VP_LINK_STRING,"string");

    this->addOutlet(VP_LINK_STRING,"string");
}

//--------------------------------------------------------------
void StringObject::setupObjectContent(shared_ptr<ofAppGLFWWindow> &mainWindow){
    //////////////////////////////////////////////
    // LINK SHARED RENDERER
    mainRenderer.setup(mainWindow->renderer());
    //////////////////////////////////////////////

    //////////////////////////////////////////////
    // YOUR SETUP CODE


    //////////////////////////////////////////////
}

//--------------------------------------------------------------
void StringObject::updateObjectContent(map<int,shared_ptr<PatchObject>> &patchObjects){
    unusedArgs(patchObjects);

    //////////////////////////////////////////////
    // YOUR UPDATE CODE
    if(this->inletsConnected[0]){
        *static_cast<string *>(_outletParams[0]) = *static_cast<string *>(_inletParams[0]);
    }
    //////////////////////////////////////////////

}

//--------------------------------------------------------------
void StringObject::drawObjectContent(ofTrueTypeFont *font, shared_ptr<ofBaseGLRenderer>& glRenderer){
    unusedArgs(font,glRenderer);

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
void StringObject::drawObjectNodeGui( ImGuiEx::NodeCanvas& _nodeCanvas ){

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
void StringObject::drawObjectNodeConfig(){
    // delay needed for some strange bug related with inspector??? ( crash when creating object with inspector already open ONLY ) - Need to check why
    if(ofGetElapsedTimeMillis()-startTime > wait){
        ImGuiEx::ObjectInfo(
                "Mosaic Plugin Example - String object.",
                "#", scaleFactor);
    }
}

//--------------------------------------------------------------
void StringObject::removeObjectContent(bool removeFileFromData){
    unusedArgs(removeFileFromData);
}


// REGISTER THE OBJECT
OBJECT_REGISTER( StringObject, "string object", OFXVP_OBJECT_CAT_DATA)
