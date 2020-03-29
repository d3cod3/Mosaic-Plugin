#pragma once

#include "PatchObject.h"
#include "mpGraphics.h"

class AudioObject : public PatchObject {

public:

    // CONSTRUCTOR
  AudioObject();

  // BASIC METHODS

  // inlets/oulets instatiation
  void              newObject();
  // object setup
  void              setupObjectContent(shared_ptr<ofAppGLFWWindow> &mainWindow);
  // object update
  void              updateObjectContent(map<int,shared_ptr<PatchObject>> &patchObjects, ofxThreadedFileDialog &fd);
  // object draw
  void              drawObjectContent(ofxFontStash *font, shared_ptr<ofBaseGLRenderer>& glRenderer);
  // call on remove object
  void              removeObjectContent(bool removeFileFromData=false);

  // ADVANCED METHODS

  // file loading objects related methods
  //void              autoloadFile(string _fp);
  //void              autosaveNewFile(string fromFile);
  //void              fileDialogResponse(ofxThreadedFileDialogResponse &response);

  // audio objects related methods
  void              setupAudioOutObjectContent(pdsp::Engine &engine);
  void              audioInObject(ofSoundBuffer &inputBuffer);
  void              audioOutObject(ofSoundBuffer &outputBuffer);

  // embed GUI objects related methods (mouse, keyboard interaction)
  //void              mouseMovedObjectContent(ofVec3f _m);
  //void              mousePressedObjectContent(ofVec3f _m);
  //void              mouseReleasedObjectContent(ofVec3f _m);
  //void              keyPressedObjectContent(int key);
  //void              dragGUIObject(ofVec3f _m);

  // object reset methods
  //void              customReset();
  //void              resetSystemObject();
  //void              resetResolution(int fromID=-1, int newWidth=-1, int newHeight=-1);


  void            loadAudioSettings();


  ofPolyline        waveform;

  int               bufferSize;
  int               sampleRate;


protected:
  mpGraphics        mainRenderer;


  OBJECT_FACTORY_PROPS

};


class AudioObjectDriver : public PatchObjectDriver
{
public:
    AudioObjectDriver() : PatchObjectDriver("AudioObjectDriver", AudioObject::version) {}
    PatchObject* create() {return new AudioObject();}
};
