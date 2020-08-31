#pragma once

#include "PatchObject.h"
#include "mpGraphics.h"

class NumberObject : public PatchObject {

public:

    // CONSTRUCTOR
  NumberObject();

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


protected:
    mpGraphics                mainRenderer;

    OBJECT_FACTORY_PROPS

};


class NumberObjectDriver : public PatchObjectDriver
{
public:
    NumberObjectDriver() : PatchObjectDriver("NumberObjectDriver", NumberObject::version) {}
    PatchObject* create() {return new NumberObject();}
};
