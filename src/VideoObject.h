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

    Name:           VideoObject

    Desc:           Mosaic Plugin Example - Video object

    Developed by:   Emanuele Mazza aka n3m3da

    Github:         https://github.com/d3cod3
    WWW:            http://www.d3cod3.org

==============================================================================*/

#pragma once

#include "PatchObject.h"
#include "mpGraphics.h"
#include "imgui_node_canvas.h"

class VideoObject : public PatchObject {

public:

    // CONSTRUCTOR
  VideoObject();

  // BASIC METHODS

  // inlets/oulets instatiation
  void              newObject() override;
  // object setup
  void              setupObjectContent(shared_ptr<ofAppGLFWWindow> &mainWindow) override;
  // object update
  void              updateObjectContent(map<int,shared_ptr<PatchObject>> &patchObjects) override;
  // object draw
  void              drawObjectContent(ofTrueTypeFont *font, shared_ptr<ofBaseGLRenderer>& glRenderer) override;
  void              drawObjectNodeGui( ImGuiEx::NodeCanvas& _nodeCanvas ) override;
  void              drawObjectNodeConfig() override;
  // call on remove object
  void              removeObjectContent(bool removeFileFromData=false) override;

  // ADVANCED METHODS

  // file loading objects related methods
  //void              autoloadFile(string _fp) override;
  //void              autosaveNewFile(string fromFile) override;

  // audio objects related methods
  //void              setupAudioOutObjectContent(pdsp::Engine &engine) override;
  //void              audioInObject(ofSoundBuffer &inputBuffer) override;
  //void              audioOutObject(ofSoundBuffer &outputBuffer) override;

  // object reset methods
  //void              customReset() override;
  //void              resetSystemObject() override;
  //void              resetResolution(int fromID=-1, int newWidth=-1, int newHeight=-1) override;

  // CUSTOM METHODS
  void              drawTexturePreview(shared_ptr<ofBaseGLRenderer>& glRenderer);

  float             posX, posY, drawW, drawH;

  float             scaledObjW, scaledObjH;
  float             objOriginX, objOriginY;
  float             canvasZoom;

  ofTexture         bridgeIn1;
  bool              isTexInited;

protected:
    mpGraphics                mainRenderer;
    size_t                      startTime;
    size_t                      wait;

    OBJECT_FACTORY_PROPS

};


class VideoObjectDriver : public PatchObjectDriver
{
public:
    VideoObjectDriver() : PatchObjectDriver("VideoObjectDriver", VideoObject::version) {}
    PatchObject* create() {return new VideoObject();}
};
