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

#include "VideoObject.h"

//--------------------------------------------------------------
VideoObject::VideoObject() : PatchObject("texture object"){

    // SET YOUR INLETS/OUTLETS
    this->numInlets  = 1;
    this->numOutlets = 1;

    _inletParams[0] = new ofTexture();  // input

    _outletParams[0] = new ofTexture(); // output

    this->initInletsState();
    this->setIsTextureObj(true);

    posX = posY = drawW = drawH = 0.0f;

    isTexInited = false;

    startTime = ofGetElapsedTimeMillis();
    wait = 200;

    this->setIsResizable(true);

}

//--------------------------------------------------------------
void VideoObject::newObject(){
    // SET OBJECT NAME AND INLETS/OUTLETS TYPES/NAMES
    PatchObject::setName( this->objectName );

    this->addInlet(VP_LINK_TEXTURE,"texture");

    this->addOutlet(VP_LINK_TEXTURE,"texture");
}

//--------------------------------------------------------------
void VideoObject::setupObjectContent(shared_ptr<ofAppGLFWWindow> &mainWindow){
    //////////////////////////////////////////////
    // LINK SHARED RENDERER
    mainRenderer.setup(mainWindow->renderer());
    //////////////////////////////////////////////

    //////////////////////////////////////////////
    // YOUR SETUP CODE

    //////////////////////////////////////////////
}

//--------------------------------------------------------------
void VideoObject::updateObjectContent(map<int,shared_ptr<PatchObject>> &patchObjects){
    unusedArgs(patchObjects);

    //////////////////////////////////////////////
    // YOUR UPDATE CODE
    if(this->inletsConnected[0] && static_cast<ofTexture *>(_inletParams[0])->isAllocated()){
        if(!isTexInited){
            isTexInited = true;
            bridgeIn1.allocate(static_cast<ofTexture *>(_inletParams[0])->getWidth(),static_cast<ofTexture *>(_inletParams[0])->getHeight(),static_cast<ofTexture *>(_inletParams[0])->getTextureData().glInternalFormat);
        }
        bridgeIn1 = *static_cast<ofTexture *>(_inletParams[0]);
        *static_cast<ofTexture *>(_outletParams[0]) = bridgeIn1;
    }else{
        isTexInited = false;
    }
    //////////////////////////////////////////////

}

//--------------------------------------------------------------
void VideoObject::drawObjectContent(ofTrueTypeFont *font, shared_ptr<ofBaseGLRenderer>& glRenderer){
    unusedArgs(font,glRenderer);

    /*
        Due to renderer sharing needs, use internal mpGraphics methods
        instead of starndard OF methods for drawing

        ex. ofSetColor --> mainRenderer.ofSetColor()
     */

    //////////////////////////////////////////////
    // YOUR DRAW CODE

    mainRenderer.ofSetColor(255,255,255);

    // draw node texture preview with OF
    //drawTexturePreview(glRenderer);
    //////////////////////////////////////////////

}

//--------------------------------------------------------------
void VideoObject::drawObjectNodeGui( ImGuiEx::NodeCanvas& _nodeCanvas ){

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

        // draw node texture preview with imGui
        ImVec2 window_pos = ImGui::GetWindowPos()+ImVec2(IMGUI_EX_NODE_PINS_WIDTH_NORMAL, IMGUI_EX_NODE_HEADER_HEIGHT);

        if(this->inletsConnected[0] && bridgeIn1.isAllocated()){
            calcTextureDims(bridgeIn1, posX, posY, drawW, drawH, objOriginX, objOriginY, scaledObjW, scaledObjH, canvasZoom, this->scaleFactor);
            _nodeCanvas.getNodeDrawList()->AddRectFilled(window_pos,window_pos+ImVec2(scaledObjW*this->scaleFactor*_nodeCanvas.GetCanvasScale(), scaledObjH*this->scaleFactor*_nodeCanvas.GetCanvasScale()),ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)));
            ImGui::SetCursorPos(ImVec2(posX+(IMGUI_EX_NODE_PINS_WIDTH_NORMAL*this->scaleFactor), posY+(IMGUI_EX_NODE_HEADER_HEIGHT*this->scaleFactor)));
            ImGui::Image((ImTextureID)(uintptr_t)bridgeIn1.getTextureData().textureID, ImVec2(drawW, drawH));
        }else{
            _nodeCanvas.getNodeDrawList()->AddRectFilled(window_pos,window_pos+ImVec2(scaledObjW*this->scaleFactor*_nodeCanvas.GetCanvasScale(), scaledObjH*this->scaleFactor*_nodeCanvas.GetCanvasScale()),ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)));
        }

        // get imgui node translated/scaled position/dimension for drawing textures in OF
        //objOriginX = (ImGui::GetWindowPos().x + ((IMGUI_EX_NODE_PINS_WIDTH_NORMAL - 1)*this->scaleFactor) - _nodeCanvas.GetCanvasTranslation().x)/_nodeCanvas.GetCanvasScale();
        //objOriginY = (ImGui::GetWindowPos().y - _nodeCanvas.GetCanvasTranslation().y)/_nodeCanvas.GetCanvasScale();
        scaledObjW = this->width - (IMGUI_EX_NODE_PINS_WIDTH_NORMAL+IMGUI_EX_NODE_PINS_WIDTH_SMALL)*this->scaleFactor/_nodeCanvas.GetCanvasScale();
        scaledObjH = this->height - (IMGUI_EX_NODE_HEADER_HEIGHT+IMGUI_EX_NODE_FOOTER_HEIGHT)*this->scaleFactor/_nodeCanvas.GetCanvasScale();

        _nodeCanvas.EndNodeContent();
    }

    // get imgui canvas zoom
    canvasZoom = _nodeCanvas.GetCanvasScale();

}

//--------------------------------------------------------------
void VideoObject::drawObjectNodeConfig(){
    // delay needed for some strange bug related with inspector??? ( crash when creating object with inspector already open ONLY ) - Need to check why
    if(ofGetElapsedTimeMillis()-startTime > wait){
        ImGuiEx::ObjectInfo(
                "Mosaic Plugin Example - Texture object.",
                "#", scaleFactor);
    }
}

//--------------------------------------------------------------
void VideoObject::removeObjectContent(bool removeFileFromData){
    unusedArgs(removeFileFromData);
}

//--------------------------------------------------------------
void VideoObject::drawTexturePreview(shared_ptr<ofBaseGLRenderer>& glRenderer){
    if(scaledObjW*canvasZoom > 90.0f){
        if(bridgeIn1.isAllocated()){
            if(bridgeIn1.getWidth()/bridgeIn1.getHeight() >= scaledObjW/scaledObjH){
                if(bridgeIn1.getWidth() > bridgeIn1.getHeight()){   // horizontal texture
                    drawW           = scaledObjW;
                    drawH           = (scaledObjW/bridgeIn1.getWidth())*bridgeIn1.getHeight();
                    posX            = 0;
                    posY            = (scaledObjH-drawH)/2.0f;
                }else{ // vertical texture
                    drawW           = (bridgeIn1.getWidth()*scaledObjH)/bridgeIn1.getHeight();
                    drawH           = scaledObjH;
                    posX            = (scaledObjW-drawW)/2.0f;
                    posY            = 0;
                }
            }else{ // always considered vertical texture
                drawW               = (bridgeIn1.getWidth()*scaledObjH)/bridgeIn1.getHeight();
                drawH               = scaledObjH;
                posX                = (scaledObjW-drawW)/2.0f;
                posY                = 0;
            }

            // background
            mainRenderer.ofSetColor(34,34,34);
            if(this->numInlets > 0){
                mainRenderer.ofDrawRectangle(objOriginX-(IMGUI_EX_NODE_PINS_WIDTH_NORMAL*this->scaleFactor/canvasZoom),objOriginY-(IMGUI_EX_NODE_HEADER_HEIGHT*this->scaleFactor/canvasZoom),scaledObjW + (IMGUI_EX_NODE_PINS_WIDTH_NORMAL*this->scaleFactor/canvasZoom),scaledObjH + ((IMGUI_EX_NODE_HEADER_HEIGHT+IMGUI_EX_NODE_FOOTER_HEIGHT)*this->scaleFactor/canvasZoom) );
            }else{
                mainRenderer.ofDrawRectangle(objOriginX,objOriginY-(IMGUI_EX_NODE_HEADER_HEIGHT*this->scaleFactor/canvasZoom),scaledObjW,scaledObjH + ((IMGUI_EX_NODE_HEADER_HEIGHT+IMGUI_EX_NODE_FOOTER_HEIGHT)*this->scaleFactor/canvasZoom) );
            }

            // texture
            mainRenderer.ofSetColor(255);
            glRenderer->draw(bridgeIn1,posX+objOriginX,posY+objOriginY,0,drawW-(2*this->scaleFactor),drawH,0,0,static_cast<ofTexture *>(_inletParams[0])->getWidth(),static_cast<ofTexture *>(_inletParams[0])->getHeight());
        }else{
            // background
            mainRenderer.ofSetColor(34,34,34);
            if(this->numInlets > 0){
                mainRenderer.ofDrawRectangle(objOriginX-(IMGUI_EX_NODE_PINS_WIDTH_NORMAL*this->scaleFactor/canvasZoom),objOriginY-(IMGUI_EX_NODE_HEADER_HEIGHT*this->scaleFactor/canvasZoom),scaledObjW + (IMGUI_EX_NODE_PINS_WIDTH_NORMAL*this->scaleFactor/canvasZoom),scaledObjH + ((IMGUI_EX_NODE_HEADER_HEIGHT+IMGUI_EX_NODE_FOOTER_HEIGHT)*this->scaleFactor/canvasZoom) );
            }else{
                mainRenderer.ofDrawRectangle(objOriginX,objOriginY-(IMGUI_EX_NODE_HEADER_HEIGHT*this->scaleFactor/canvasZoom),scaledObjW,scaledObjH + ((IMGUI_EX_NODE_HEADER_HEIGHT+IMGUI_EX_NODE_FOOTER_HEIGHT)*this->scaleFactor/canvasZoom) );
            }
        }
    }
}


// REGISTER THE OBJECT
OBJECT_REGISTER( VideoObject, "texture object", OFXVP_OBJECT_CAT_TEXTURE)
