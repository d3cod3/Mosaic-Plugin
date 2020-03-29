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

#include "AudioObject.h"

//--------------------------------------------------------------
AudioObject::AudioObject() : PatchObject(){

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

}

//--------------------------------------------------------------
void AudioObject::newObject(){
    // SET OBJECT NAME AND INLETS/OUTLETS TYPES/NAMES
    this->setName(this->objectName);
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
    this->pdspIn[0] >> this->pdspOut[0];
    this->pdspIn[0] >> this->pdspOut[1];
}

//--------------------------------------------------------------
void AudioObject::updateObjectContent(map<int,shared_ptr<PatchObject>> &patchObjects, ofxThreadedFileDialog &fd){

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
void AudioObject::drawObjectContent(ofxFontStash *font, shared_ptr<ofBaseGLRenderer>& glRenderer){

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
    mainRenderer.ofEnableAlphaBlending();
    if(this->inletsConnected[0]){
        mainRenderer.ofSetColor(255,255,120,10);
        mainRenderer.ofDrawRectangle(0,this->height,this->width,-this->height * ofClamp(static_cast<ofSoundBuffer *>(_inletParams[0])->getRMSAmplitude(),0.0,1.0));
    }
    mainRenderer.ofSetColor(255,255,120);
    mainRenderer.draw(waveform);
    mainRenderer.ofDisableAlphaBlending();
    //////////////////////////////////////////////

}

//--------------------------------------------------------------
void AudioObject::removeObjectContent(bool removeFileFromData){

}

//--------------------------------------------------------------
void AudioObject::loadAudioSettings(){
    ofxXmlSettings XML;

    if (XML.loadFile(patchFile)){
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

}

//--------------------------------------------------------------
void AudioObject::audioOutObject(ofSoundBuffer &outBuffer){
    waveform.clear();
    if(this->inletsConnected[0]){
        *static_cast<ofSoundBuffer *>(_outletParams[0]) = *static_cast<ofSoundBuffer *>(_inletParams[0]);
        *static_cast<ofSoundBuffer *>(_outletParams[1]) = *static_cast<ofSoundBuffer *>(_inletParams[0]);

        for(size_t i = 0; i < static_cast<ofSoundBuffer *>(_inletParams[0])->getNumFrames(); i++) {
            float sample = static_cast<ofSoundBuffer *>(_inletParams[0])->getSample(i,0);
            float x = ofMap(i, 0, static_cast<ofSoundBuffer *>(_inletParams[0])->getNumFrames(), 0, this->width);
            float y = ofMap(hardClip(sample), -1, 1, 0, this->height);
            waveform.addVertex(x, y);

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
