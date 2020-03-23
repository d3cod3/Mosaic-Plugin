#pragma once

#include "PatchObject.h"

class MosaicObjectTemplate : public PatchObject {

public:

  MosaicObjectTemplate();

  void            newObject();
  void            setupObjectContent(shared_ptr<ofAppGLFWWindow> &mainWindow);
  void            updateObjectContent(map<int,shared_ptr<PatchObject>> &patchObjects, ofxThreadedFileDialog &fd);
  void            drawObjectContent(ofxFontStash *font);
  void            removeObjectContent(bool removeFileFromData=false);

  std::shared_ptr<ofBaseRenderer> mainRenderer;


  OBJECT_FACTORY_PROPS

};


class MosaicObjectTemplateDriver : public PatchObjectDriver
{
public:
    MosaicObjectTemplateDriver() : PatchObjectDriver("MosaicObjectTemplateDriver", MosaicObjectTemplate::version) {}
    PatchObject* create() {return new MosaicObjectTemplate();}
};
