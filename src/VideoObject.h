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
  void              drawObjectContent(ofxFontStash *font, shared_ptr<ofBaseGLRenderer>& glRenderer) override;
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
