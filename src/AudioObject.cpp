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

    Name:           AudioObject

    Desc:           Mosaic Plugin Example - Audio object

    Developed by:   Emanuele Mazza aka n3m3da

    Github:         https://github.com/d3cod3
    WWW:            http://www.d3cod3.org

==============================================================================*/

#include "AudioObject.h"

//--------------------------------------------------------------
AudioObject::AudioObject() : PatchObject("sound object"){

    // SET YOUR INLETS/OUTLETS
    this->numInlets  = 1;
    this->numOutlets = 4;

    _inletParams[0] = new ofSoundBuffer();  // signal

    _outletParams[0] = new ofSoundBuffer();     // signal
    _outletParams[1] = new ofSoundBuffer();     // signal
    _outletParams[2] = new vector<float>();     // audio buffer
    _outletParams[3] = new float();             // RMS
    *(float *)&_outletParams[3] = 0.0f;

    this->initInletsState();

    isAudioINObject         = true;
    isAudioOUTObject        = true;
    isPDSPPatchableObject   = true;

    startTime = ofGetElapsedTimeMillis();
    wait = 200;

}

//--------------------------------------------------------------
void AudioObject::newObject(){
    // SET OBJECT NAME AND INLETS/OUTLETS TYPES/NAMES
    PatchObject::setName( this->objectName );

    this->addInlet(VP_LINK_AUDIO,"signal");

    this->addOutlet(VP_LINK_AUDIO,"signal");
    this->addOutlet(VP_LINK_AUDIO,"signal");
    this->addOutlet(VP_LINK_ARRAY,"dataBuffer");
    this->addOutlet(VP_LINK_NUMERIC,"RMSAmplitude");
}

//--------------------------------------------------------------
void AudioObject::setupObjectContent(shared_ptr<ofAppGLFWWindow> &mainWindow){
    //////////////////////////////////////////////
    // LINK SHARED RENDERER
    mainRenderer.setup(mainWindow->renderer());
    //////////////////////////////////////////////

    //////////////////////////////////////////////
    // YOUR SETUP CODE
    loadAudioSettings();
    //////////////////////////////////////////////
}

//--------------------------------------------------------------
void AudioObject::setupAudioOutObjectContent(pdsp::Engine &engine){
    unusedArgs(engine);

    this->pdspIn[0] >> this->pdspOut[0];
    this->pdspIn[0] >> this->pdspOut[1];
}

//--------------------------------------------------------------
void AudioObject::updateObjectContent(map<int,shared_ptr<PatchObject>> &patchObjects){
    unusedArgs(patchObjects);

    //////////////////////////////////////////////
    // YOUR UPDATE CODE
    if(this->inletsConnected[0]){
        *(float *)&_outletParams[3] = ofClamp(static_cast<ofSoundBuffer *>(_inletParams[0])->getRMSAmplitude(),0.0,1.0);
    }else{
        *(float *)&_outletParams[3] = 0;
    }
    //////////////////////////////////////////////

}

//--------------------------------------------------------------
void AudioObject::drawObjectContent(ofTrueTypeFont *font, shared_ptr<ofBaseGLRenderer>& glRenderer){
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

    //////////////////////////////////////////////

}

//--------------------------------------------------------------
void AudioObject::drawObjectNodeGui( ImGuiEx::NodeCanvas& _nodeCanvas ){

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

        // draw waveform
        ImGuiEx::drawWaveform(_nodeCanvas.getNodeDrawList(), ImGui::GetWindowSize(), plot_data, 1024, 1.3f, IM_COL32(255,255,120,255), this->scaleFactor);

        // draw signal RMS amplitude
        _nodeCanvas.getNodeDrawList()->AddRectFilled(ImGui::GetWindowPos()+ImVec2(0,ImGui::GetWindowSize().y),ImGui::GetWindowPos()+ImVec2(ImGui::GetWindowSize().x,ImGui::GetWindowSize().y * (1.0f - ofClamp(static_cast<ofSoundBuffer *>(_inletParams[0])->getRMSAmplitude(),0.0,1.0))),IM_COL32(255,255,120,12));

        _nodeCanvas.EndNodeContent();
    }

}

//--------------------------------------------------------------
void AudioObject::drawObjectNodeConfig(){
    // delay needed for some strange bug related with inspector??? ( crash when creating object with inspector already open ONLY ) - Need to check why
    if(ofGetElapsedTimeMillis()-startTime > wait){
        ImGuiEx::ObjectInfo(
                "Mosaic Plugin Example - Audio object.",
                "#", scaleFactor);
    }
}

//--------------------------------------------------------------
void AudioObject::removeObjectContent(bool removeFileFromData){
    unusedArgs(removeFileFromData);
}

//--------------------------------------------------------------
void AudioObject::loadAudioSettings(){
    ofxXmlSettings XML;

    if (XML.load(patchFile)){
        if (XML.pushTag("settings")){
            sampleRate = XML.getValue("sample_rate_in",0);
            bufferSize = XML.getValue("buffer_size",0);

            for(int i=0;i<bufferSize;i++){
                static_cast<vector<float> *>(_outletParams[2])->push_back(0.0f);
            }

            XML.popTag();
        }
    }
}

//--------------------------------------------------------------
void AudioObject::audioInObject(ofSoundBuffer &inputBuffer){
    unusedArgs(inputBuffer);
}

//--------------------------------------------------------------
void AudioObject::audioOutObject(ofSoundBuffer &outBuffer){
    unusedArgs(outBuffer);

    if(this->inletsConnected[0]){
        *static_cast<ofSoundBuffer *>(_outletParams[0]) = *static_cast<ofSoundBuffer *>(_inletParams[0]);
        *static_cast<ofSoundBuffer *>(_outletParams[1]) = *static_cast<ofSoundBuffer *>(_inletParams[0]);

        for(size_t i = 0; i < static_cast<ofSoundBuffer *>(_inletParams[0])->getNumFrames(); i++) {
            float sample = static_cast<ofSoundBuffer *>(_inletParams[0])->getSample(i,0);
            plot_data[i] = hardClip(sample);

            // SIGNAL BUFFER DATA
            static_cast<vector<float> *>(_outletParams[2])->at(i) = sample;
        }
    }else{
        *static_cast<ofSoundBuffer *>(_outletParams[0]) *= 0.0f;
        *static_cast<ofSoundBuffer *>(_outletParams[1]) *= 0.0f;
    }

}

// REGISTER THE OBJECT
OBJECT_REGISTER( AudioObject, "sound object", OFXVP_OBJECT_CAT_SOUND)
