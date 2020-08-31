#pragma once

#include "PatchObject.h"
#include "mpGraphics.h"

#include "imgui_plot.h"

class AudioObject : public PatchObject {

public:

    // CONSTRUCTOR
  AudioObject();

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

  // ADVANCED METHODS

  // file loading objects related methods
  //void              autoloadFile(string _fp) override;
  //void              autosaveNewFile(string fromFile) override;

  // audio objects related methods
  void              setupAudioOutObjectContent(pdsp::Engine &engine) override;
  void              audioInObject(ofSoundBuffer &inputBuffer) override;
  void              audioOutObject(ofSoundBuffer &outputBuffer) override;

  // object reset methods
  //void              customReset() override;
  //void              resetSystemObject() override;
  //void              resetResolution(int fromID=-1, int newWidth=-1, int newHeight=-1) override;



  void              loadAudioSettings();


  float             plot_data[1024];

  int               bufferSize;
  int               sampleRate;


protected:
    mpGraphics                mainRenderer;

    OBJECT_FACTORY_PROPS

};


class AudioObjectDriver : public PatchObjectDriver
{
public:
    AudioObjectDriver() : PatchObjectDriver("AudioObjectDriver", AudioObject::version) {}
    PatchObject* create() {return new AudioObject();}
};
