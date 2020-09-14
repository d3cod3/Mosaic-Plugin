# Mosaic-Plugin
Mosaic plugin template

## Code Details

Writing a Mosaic plugin is relatively easy, just clone this repo and open the qtcreator project to take a look at the 4 included objects/nodes templates.

You can write plugins with a single object, or you can pack multiple objects in the same plugin ( a plugin pack ). You will have access at all the openFrameworks code/libraries, ImGui and all the ofxAddons already comes as dependencies of ofxVisualProgramming addon, the core code of the Mosaic objects/nodes implementation. Lots of possibilities, indeed!

Let's analize the _NumberObject_ Mosaic plugin template, included in the repo, a simple objects receiving a number cable and returning another number cable with the same value received ( a bypass object/node, not really useful, but perfect for understanding the plugin code structure ):

The header of the plugin is NumberObject.h :

```c

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

    Name:           NumberObject

    Desc:           Mosaic Plugin Example - Number object

    Developed by:   Emanuele Mazza aka n3m3da

    Github:         https://github.com/d3cod3
    WWW:            http://www.d3cod3.org

==============================================================================*/

#pragma once

#include "PatchObject.h"
#include "mpGraphics.h"

class NumberObject : public PatchObject {

public:

    // CONSTRUCTOR
    NumberObject();

    // inherit virtual methods from base class PatchObject
    // this are all methods available, you can use it all
    // or just the one you need.
    // for this simple object i'm going to leave commented
    // the ones i don't need

    // BASIC METHODS

    // inlets/oulets instatiation
    void              newObject() override;
    // object setup
    void              setupObjectContent(shared_ptr<ofAppGLFWWindow> &mainWindow) override;
    // object update
    void              updateObjectContent(map<int,shared_ptr<PatchObject>> &patchObjects);
    // object draw
    void              drawObjectContent(ofxFontStash *font, shared_ptr<ofBaseGLRenderer>& glRenderer) override;
    void              drawObjectNodeGui( ImGuiEx::NodeCanvas& _nodeCanvas ) override;
    void              drawObjectNodeConfig() override;
    // call on remove object
    void              removeObjectContent(bool removeFileFromData=false) override;

    // ADVANCED METHODS

    // file loading objects related methods (video file, audio file, script file, etc)
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
      mpGraphics                  mainRenderer; // reference to the main renderer ( avoid problems with openGL single thread resources access )
      size_t                      startTime;
      size_t                      wait;

      // initialize object in factory
      OBJECT_FACTORY_PROPS

};

// this is the necessary code to transform the object/node into a Mosaic plugin
// ( check the names and change accordingly, two objects with the same name or driver name cannot co-exists )
class NumberObjectDriver : public PatchObjectDriver
{
public:
    NumberObjectDriver() : PatchObjectDriver("NumberObjectDriver", NumberObject::version) {}
    PatchObject* create() {return new NumberObject();}
};

```

And the source NumberObject.cpp :

```c

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

    Name:           NumberObject

    Desc:           Mosaic Plugin Example - Number object

    Developed by:   Emanuele Mazza aka n3m3da

    Github:         https://github.com/d3cod3
    WWW:            http://www.d3cod3.org

==============================================================================*/

#include "NumberObject.h"

//--------------------------------------------------------------
NumberObject::NumberObject() : PatchObject("number object"){

    // SET YOUR INLETS/OUTLETS
    this->numInlets  = 1;
    this->numOutlets = 1;

    // then init the pointers
    // i have used here void* pointers
    // and established 6 fixed type of data plus a variable
    // one (a special purpose cable for special cases) to cast
    // and create proper connections

    // VP_LINK_NUMERIC --> float
    // VP_LINK_STRING  --> string
    // VP_LINK_ARRAY   --> vector<float>
    // VP_LINK_TEXTURE --> ofTexture
    // VP_LINK_PIXELS  --> ofPixels
    // VP_LINK_AUDIO   --> ofSoundBuffer
    // VP_LINK_SPECIAL --> anything

    // We'll use here simple VP_LINK_NUMERIC connections, due to the nature of the objects ( a float number bypass )

    // we create/cast the inlet then as float
    _inletParams[0] = new float();  // input
    *(float *)&_inletParams[0] = 0.0f;

    // and the same for the outlet
    _outletParams[0] = new float(); // output
    *(float *)&_outletParams[0] = 0.0f;

    // we call this to init internal stuff
    this->initInletsState();

    // delay ImGui render due to unresolved bug
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

    // SETUP your object here, as any ofApp example

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

    // UPDATE your object here, as any ofApp example

    //////////////////////////////////////////////
    // YOUR UPDATE CODE
    if(this->inletsConnected[0]){
        *(float *)&_outletParams[0] = *(float *)&_inletParams[0];
    }
    //////////////////////////////////////////////

}

//--------------------------------------------------------------
void NumberObject::drawObjectContent(ofxFontStash *font, shared_ptr<ofBaseGLRenderer>& glRenderer){

    // DRAW your OF code here, as any ofApp example ( check differences below )

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

    // DRAW your ImGui object CONFIG menu and and the object main view here

    ImGui::SetCurrentContext(_nodeCanvas.getContext());

    // CONFIG GUI custom Menu
    if(_nodeCanvas.BeginNodeMenu()){

        ImGui::Separator();
        ImGui::Separator();
        ImGui::Separator();

        if (ImGui::BeginMenu("CONFIG"))
        {

            // the callback to the custom menu content
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
    // DRAW your ImGui object custom CONFIG menu

    // delay ImGui render due to unresolved bug
    if(ofGetElapsedTimeMillis()-startTime > wait){

        // ObjectInfo(description, reference url, retinaScaleFactor)
        ImGuiEx::ObjectInfo(
                    "Mosaic Plugin Example - Number object.",
                    "#", scaleFactor);
    }
}

//--------------------------------------------------------------
void NumberObject::removeObjectContent(bool removeFileFromData){
  // anything you need to remove or stop when deleting the object
}


// REGISTER THE OBJECT to factory OBJECT_REGISTER(class, object name, category)
OBJECT_REGISTER( NumberObject, "number object", OFXVP_OBJECT_CAT_MATH)

// available categories
// OFXVP_OBJECT_CAT_AUDIOANALYSIS
// OFXVP_OBJECT_CAT_COMMUNICATIONS
// OFXVP_OBJECT_CAT_CV
// OFXVP_OBJECT_CAT_DATA
// OFXVP_OBJECT_CAT_GUI
// OFXVP_OBJECT_CAT_LOGIC
// OFXVP_OBJECT_CAT_MATH
// OFXVP_OBJECT_CAT_SCRIPTING
// OFXVP_OBJECT_CAT_SOUND
// OFXVP_OBJECT_CAT_TEXTURE
// OFXVP_OBJECT_CAT_WINDOWING

```

So, this is a basic Mosaic plugin structure, the last thing we need to create the plugin, is edit the plugin.cpp file ( included in the repo )

```c

// necessary include from Pugg plugin system
#include "Kernel.h"

// her we include our new Mosaic plugin ( multiple includes in case of multiple plugins in the same plugin package )
#include "NumberObject.h"

#ifdef _WIN32
#  define EXPORTIT __declspec( dllexport )
#else
#  define EXPORTIT
#endif

extern "C" EXPORTIT void register_pugg_plugin(pugg::Kernel* kernel)
{
    // here we'll just need to add a line for every plugin in the package ( just one in this case)
    kernel->add_driver(new NumberObjectDriver());
}

```

Then last, but not less important, we'll need to edit the name of the plugin ( or the plugin package ), and for that we'll just have to edit a line inside the .qbs qtcreator project file ( line 12 in the one from the repo) :

```c

  name: "MosaicObjectTemplate"

```

Just change the default **MosaicObjectTemplate** name with the one you need for your plugin/plugin package.

Compile, and if everything went fine, a dynamic library will appear in the project bin/ folder (.framework for OSX, .so for linux, .dll for windows).
Just For OSX, you'll need to get the .framework internal library and rename it to .bundle, just check the included copyPluginToMosaic.sh file:

```bash

#!/bin/bash

SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"

PLUGINNAME="MosaicObjectTemplate"

cp $SCRIPTPATH/bin/$PLUGINNAME.framework/Versions/A/$PLUGINNAME ~/Documents/Mosaic/Data/plugins/$PLUGINNAME.bundle

```

The script will rename and copy the plugin in the plugins/ Mosaic folder ( remember to have Mosaic installed and at least opened one first time, in order to have the Mosaic/ folder inside your user Documents/ folder )

That's it, you have just created your first Mosaic plugin, you can now add your custom objects/nodes to the Mosaic platform, use them for your personal works or distribute them, to share your code/knowledge and help others to learn new stuff.
