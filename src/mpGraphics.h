#pragma once

#include "ofConstants.h"
#include "ofGLProgrammableRenderer.h"
#include "ofGraphicsConstants.h"
#include "ofGraphicsBaseTypes.h"
#include "ofRectangle.h"
#include "ofRendererCollection.h"
#include "ofCairoRenderer.h"
#include "ofGLUtils.h"
#include "ofGLRenderer.h"
#include "ofImage.h"
#include "ofPath.h"
#include "ofTrueTypeFont.h"
#include "ofVideoGrabber.h"
#include "ofVideoPlayer.h"
#include "ofVideoBaseTypes.h"

// bridge class to use OF renderer calls with shared renderer (Mosaic plugin system)


class mpGraphics{

public:

  //------------------------------------------------------------------------------
  //------------------------------------------------------------------------------
  //------------------------------------------------------------------------------
  mpGraphics() {}

  void setup(std::shared_ptr<ofBaseRenderer> _r) {
      mainRenderer = _r;
  }
  //------------------------------------------------------------------------------
  //------------------------------------------------------------------------------
  //------------------------------------------------------------------------------

  // of3dUtils
  void ofDrawAxis(float size) { mainRenderer->drawAxis(size); }
  void ofDrawGrid(float stepSize, size_t numberOfSteps, bool labels, bool x, bool y, bool z) { mainRenderer->drawGrid(stepSize,numberOfSteps,labels,x,y,z); }
  void ofDrawGridPlane(float stepSize, size_t numberOfSteps, bool labels) { mainRenderer->drawGridPlane(stepSize,numberOfSteps,labels); }
  void ofDrawArrow(const glm::vec3& start, const glm::vec3& end, float headSize) { mainRenderer->drawArrow(start,end,headSize); }
  void ofDrawRotationAxes(float radius, float stripWidth, int circleRes){ mainRenderer->drawRotationAxes(radius,stripWidth,circleRes); }

  // ofCamera
  void begin(ofCamera &_c, const ofRectangle & viewport) { mainRenderer->bind(_c,viewport); }
  void end(ofCamera &_c) { mainRenderer->unbind(_c); }

  // ofNode
  void draw(ofNode &_n) { mainRenderer->draw(_n); }

  // of3dGraphics
  void ofSetPlaneResolution( int columns, int rows ){	mainRenderer->setPlaneResolution(columns,rows); }
  glm::vec2 ofGetPlaneResolution(){	return mainRenderer->getPlaneResolution(); }
  void ofDrawPlane(float x, float y, float width, float height){	mainRenderer->drawPlane(x,y,width,height); }
  void ofDrawPlane(float x, float y, float z, float width, float height){	mainRenderer->drawPlane(x,y,z,width,height); }
  void ofDrawPlane(glm::vec3& position, float width, float height){	mainRenderer->drawPlane(position,width,height); }
  void ofDrawPlane( float width, float height ){	mainRenderer->drawPlane(width,height); }
  void ofSetSphereResolution(int res){	mainRenderer->setSphereResolution(res); }
  int ofGetSphereResolution(){	return mainRenderer->getSphereResolution(); }
  void ofDrawSphere(float x, float y, float radius){	mainRenderer->drawSphere(x,y,radius); }
  void ofDrawSphere(float x, float y, float z, float radius){	mainRenderer->drawSphere(x,y,z,radius); }
  void ofDrawSphere(const glm::vec3& position, float radius){	mainRenderer->drawSphere(position,radius); }
  void ofDrawSphere(float radius){	mainRenderer->drawSphere(radius); }
  void ofSetIcoSphereResolution( int res ){	mainRenderer->setIcoSphereResolution(res); }
  int ofGetIcoSphereResolution(){	return mainRenderer->getIcoSphereResolution(); }
  void ofDrawIcoSphere(float x, float y, float z, float radius){	mainRenderer->drawIcoSphere(x,y,z,radius); }
  void ofDrawIcoSphere(float x, float y, float radius){	mainRenderer->drawIcoSphere(x,y,radius); }
  void ofDrawIcoSphere(const glm::vec3& position, float radius){	mainRenderer->drawIcoSphere(position,radius); }
  void ofDrawIcoSphere(float radius){	mainRenderer->drawIcoSphere(radius); }
  void ofSetCylinderResolution( int radiusSegments, int heightSegments, int capSegments ){	mainRenderer->setCylinderResolution(radiusSegments,heightSegments,capSegments); }
  glm::vec3 ofGetCylinderResolution(){	return mainRenderer->getCylinderResolution(); }
  void ofDrawCylinder(float x, float y, float radius, float height){	mainRenderer->drawCylinder(x,y,radius,height); }
  void ofDrawCylinder(float x, float y, float z, float radius, float height){	mainRenderer->drawCylinder(x,y,z,radius,height); }
  void ofDrawCylinder(const glm::vec3& position, float radius, float height){	mainRenderer->drawCylinder(position,radius,height); }
  void ofDrawCylinder(float radius, float height){	mainRenderer->drawCylinder(radius,height); }
  void ofSetConeResolution( int radiusSegments, int heightSegments, int capSegments){	mainRenderer->setConeResolution(radiusSegments,heightSegments,capSegments); }
  glm::vec3 ofGetConeResolution(){	return mainRenderer->getConeResolution(); }
  void ofDrawCone(float x, float y, float z, float radius, float height){	mainRenderer->drawCone(x,y,z,radius,height); }
  void ofDrawCone(float x, float y, float radius, float height){	mainRenderer->drawCone(x,y,radius,height); }
  void ofDrawCone(const glm::vec3& position, float radius, float height){	mainRenderer->drawCone(position,radius,height); }
  void ofDrawCone(float radius, float height){	mainRenderer->drawCone(radius,height); }
  void ofSetBoxResolution( int res ){	mainRenderer->setBoxResolution(res); }
  void ofSetBoxResolution( int resWidth, int resHeight, int resDepth ){	mainRenderer->setBoxResolution(resWidth,resHeight,resDepth); }
  glm::vec3 ofGetBoxResolution(){	return mainRenderer->getBoxResolution(); }
  void ofDrawBox( float x, float y, float z, float width, float height, float depth){	mainRenderer->drawBox(x,y,z,width,height,depth); }
  void ofDrawBox(float x, float y, float z, float size){	mainRenderer->drawBox(x,y,z,size); }
  void ofDrawBox(const glm::vec3& position, float width, float height, float depth){	mainRenderer->drawBox(position,width,height,depth); }
  void ofDrawBox(const glm::vec3& position, float size){	mainRenderer->drawBox(position,size); }
  void ofDrawBox(float size){	mainRenderer->drawBox(size); }
  void ofDrawBox( float width, float height, float depth ){	mainRenderer->drawBox(width,height,depth); }

  // ofGraphics
  void ofPushView(){	mainRenderer->pushView(); }
  void ofPopView(){	mainRenderer->popView(); }
  void ofViewport(ofRectangle viewport){	mainRenderer->viewport(viewport.x, viewport.y, viewport.width, viewport.height); }
  void ofViewport(float x, float y, float width, float height, bool invertY){	mainRenderer->viewport(x,y,width,height,invertY); }
  ofRectangle ofGetCurrentViewport(){	return mainRenderer->getCurrentViewport(); }
  ofRectangle ofGetNativeViewport(){	return mainRenderer->getNativeViewport(); }
  int ofGetViewportWidth(){	return mainRenderer->getViewportWidth(); }
  int ofGetViewportHeight(){	return mainRenderer->getViewportHeight(); }
  bool ofIsVFlipped(){	return mainRenderer->isVFlipped(); }
  void ofSetCoordHandedness(ofHandednessType handedness){	mainRenderer->setCoordHandedness(handedness); }
  ofHandednessType ofGetCoordHandedness(){	return mainRenderer->getCoordHandedness(); }
  void ofSetupScreenPerspective(float width, float height, float fov, float nearDist, float farDist){	mainRenderer->setupScreenPerspective(width,height, fov,nearDist,farDist); }
  void ofSetupScreenOrtho(float width, float height, float nearDist, float farDist){	mainRenderer->setupScreenOrtho(width,height,nearDist,farDist); }
  void ofSetupGraphicDefaults(){ mainRenderer->setupGraphicDefaults(); }
  void ofSetupScreen(){	mainRenderer->setupScreen(); }
  void ofPushMatrix(){	mainRenderer->pushMatrix(); }
  void ofPopMatrix(){	mainRenderer->popMatrix(); }
  glm::mat4 ofGetCurrentOrientationMatrix(){	return mainRenderer->getCurrentOrientationMatrix(); }
  glm::mat4 ofGetCurrentNormalMatrix(){	return mainRenderer->getCurrentNormalMatrix(); }
  void ofTranslate(const glm::vec3& p){	mainRenderer->translate(p); }
  void ofTranslate(const glm::vec2& p){	mainRenderer->translate(glm::vec3(p, 0.0)); }
  void ofTranslate(float x, float y, float z){	mainRenderer->translate(x, y, z); }
  void ofScale(float xAmnt, float yAmnt, float zAmnt){	mainRenderer->scale(xAmnt, yAmnt, zAmnt); }
  void ofScale(float amount){	ofScale(amount, amount, amount); }
  void ofScale(const glm::vec3 & p) {	ofScale(p.x, p.y, p.z); }
  void ofRotate(float degrees){	mainRenderer->rotateDeg(degrees); }
  void ofRotate(float degrees, float vecX, float vecY, float vecZ){	mainRenderer->rotateDeg(degrees, vecX, vecY, vecZ); }
  void ofRotateX(float degrees){	mainRenderer->rotateXDeg(degrees); }
  void ofRotateY(float degrees){	mainRenderer->rotateYDeg(degrees); }
  void ofRotateZ(float degrees){	mainRenderer->rotateZDeg(degrees); }
  void ofRotateDeg(float degrees){	mainRenderer->rotateDeg(degrees); }
  void ofRotateDeg(float degrees, float vecX, float vecY, float vecZ){	mainRenderer->rotateDeg(degrees, vecX, vecY, vecZ); }
  void ofRotateXDeg(float degrees){	mainRenderer->rotateXDeg(degrees); }
  void ofRotateYDeg(float degrees){	mainRenderer->rotateYDeg(degrees); }
  void ofRotateZDeg(float degrees){	mainRenderer->rotateZDeg(degrees); }
  void ofRotateRad(float degrees){	mainRenderer->rotateRad(degrees); }
  void ofRotateRad(float degrees, float vecX, float vecY, float vecZ){	mainRenderer->rotateRad(degrees, vecX, vecY, vecZ); }
  void ofRotateXRad(float degrees){	mainRenderer->rotateXRad(degrees); }
  void ofRotateYRad(float degrees){	mainRenderer->rotateYRad(degrees); }
  void ofRotateZRad(float degrees){	mainRenderer->rotateZRad(degrees); }
  void ofLoadIdentityMatrix (void){	mainRenderer->loadIdentityMatrix(); }
  void ofLoadMatrix (const glm::mat4 & m){	mainRenderer->loadMatrix(m); }
  void ofLoadMatrix (const float *m){	mainRenderer->loadMatrix(m); }
  void ofMultMatrix (const glm::mat4 & m){	mainRenderer->multMatrix(m); }
  void ofMultMatrix (const float *m){	mainRenderer->multMatrix(m); }
  void ofSetMatrixMode(ofMatrixMode matrixMode){	mainRenderer->matrixMode(matrixMode); }
  void ofLoadViewMatrix(const glm::mat4 & m){	mainRenderer->loadViewMatrix(m); }
  void ofMultViewMatrix(const glm::mat4 & m){	mainRenderer->multViewMatrix(m); }
  glm::mat4 ofGetCurrentViewMatrix(){	return mainRenderer->getCurrentViewMatrix(); }
  void ofClear(float r, float g, float b, float a){	mainRenderer->clear(r,g,b,a); }
  void ofClear(float brightness, float a){	mainRenderer->clear(brightness, brightness, brightness, a); }
  void ofClear(const ofColor & c){	mainRenderer->clear(c.r, c.g, c.b, c.a); }
  void ofClearAlpha(){	mainRenderer->clearAlpha(); }
  void ofSetBackgroundAuto(bool bAuto){	mainRenderer->setBackgroundAuto(bAuto); }
  bool ofGetBackgroundAuto(){	return mainRenderer->getBackgroundAuto(); }
  bool ofbClearBg(){	return ofGetBackgroundAuto(); }
  ofColor ofGetBackground(){	return mainRenderer->getBackgroundColor(); }
  ofColor ofGetBackgroundColor(){	return mainRenderer->getBackgroundColor(); }
  void ofBackground(int brightness, int alpha){	ofBackground(brightness, brightness, brightness, alpha); }
  void ofBackground(const ofColor & c){	ofBackground ( c.r, c.g, c.b, c.a); }
  void ofBackgroundHex(int hexColor, int alpha){	ofBackground ( (hexColor >> 16) & 0xff, (hexColor >> 8) & 0xff, (hexColor >> 0) & 0xff, alpha); }
  void ofBackground(int r, int g, int b, int a){	mainRenderer->background(r,g,b,a); }
  void ofSetBackgroundColor(int brightness, int alpha){	ofSetBackgroundColor(brightness, brightness, brightness, alpha); }
  void ofSetBackgroundColorHex(int hexColor, int alpha){	ofSetBackgroundColor ( (hexColor >> 16) & 0xff, (hexColor >> 8) & 0xff, (hexColor >> 0) & 0xff, alpha); }
  void ofSetBackgroundColor(int r, int g, int b, int a){	ofSetBackgroundColor (ofColor(r,g,b,a)); }
  void ofSetBackgroundColor(const ofColor & c){	mainRenderer->setBackgroundColor(c); }
  void  ofSetRectMode(ofRectMode mode){	mainRenderer->setRectMode(mode); }
  ofRectMode ofGetRectMode(){    return mainRenderer->getRectMode(); }
  void ofNoFill(){	mainRenderer->setFillMode(OF_OUTLINE); }
  void ofFill(){	mainRenderer->setFillMode(OF_FILLED); }
  ofFillFlag ofGetFill(){    return mainRenderer->getFillMode(); }
  void ofSetLineWidth(float lineWidth){	mainRenderer->setLineWidth(lineWidth); }
  void ofSetDepthTest(bool depthTest){	mainRenderer->setDepthTest(depthTest); }
  void ofSetCurveResolution(int res){	mainRenderer->setCurveResolution(res); }
  void ofSetCircleResolution(int res){	mainRenderer->setCircleResolution(res); }
  void ofSetColor(const ofColor & color){	ofSetColor(color.r,color.g,color.b,color.a); }
  void ofSetColor(const ofColor & color, int _a){	ofSetColor(color.r,color.g,color.b,_a); }
  void ofSetColor(int r, int g, int b){	ofSetColor(r,g,b,255); }
  void ofSetColor(int r, int g, int b, int a){	mainRenderer->setColor(r,g,b,a); }
  void ofSetColor(int gray){ ofSetColor(gray, gray, gray); }
  void ofSetHexColor(int hexColor){	int r = (hexColor >> 16) & 0xff;
      int g = (hexColor >> 8) & 0xff;
      int b = (hexColor >> 0) & 0xff;
      ofSetColor(r,g,b);
  }void ofEnableBlendMode(ofBlendMode blendMode){	mainRenderer->setBlendMode(blendMode); }
  void ofEnablePointSprites(){
    if(mainRenderer->getType()=="GL" || mainRenderer->getType()=="ProgrammableGL"){
      static_cast<ofBaseGLRenderer*>(mainRenderer.get())->enablePointSprites();
      }
  }
  void ofDisablePointSprites(){
    if(mainRenderer->getType()=="GL" || mainRenderer->getType()=="ProgrammableGL"){
      static_cast<ofBaseGLRenderer*>(mainRenderer.get())->disablePointSprites();
      }
  }
  void ofDisableBlendMode(){ ofEnableBlendMode(OF_BLENDMODE_DISABLED); }
  void ofEnableAlphaBlending(){	ofEnableBlendMode(OF_BLENDMODE_ALPHA); }
  void ofDisableAlphaBlending(){ ofDisableBlendMode(); }
  void ofEnableSmoothing(){	mainRenderer->setLineSmoothing(true); }
  void ofDisableSmoothing(){	mainRenderer->setLineSmoothing(false); }
  void ofSetPolyMode(ofPolyWindingMode mode){	mainRenderer->setPolyMode(mode); }
  void ofEnableAntiAliasing(){	mainRenderer->enableAntiAliasing(); }
  void ofDisableAntiAliasing(){	mainRenderer->disableAntiAliasing(); }
  void ofSetDrawBitmapMode(ofDrawBitmapMode mode){	mainRenderer->setBitmapTextMode(mode); }
  void ofSetStyle(ofStyle style){	mainRenderer->setStyle(style); }
  ofStyle ofGetStyle(){	return mainRenderer->getStyle(); }
  void ofPushStyle(){	mainRenderer->pushStyle(); }
  void ofPopStyle(){	mainRenderer->popStyle(); }
  void ofDrawTriangle(const glm::vec3 & p1, const glm::vec3 & p2, const glm::vec3 & p3){	ofDrawTriangle(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z); }
  void ofDrawTriangle(const glm::vec2 & p1, const glm::vec2 & p2, const glm::vec2 & p3){	ofDrawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y); }
  void ofDrawTriangle(float x1,float y1,float x2,float y2,float x3, float y3){	ofDrawTriangle(x1, y1, 0.0f, x2, y2, 0.0f, x3, y3, 0.0f); }
  void ofDrawTriangle(float x1,float y1,float z1,float x2,float y2,float z2,float x3, float y3,float z3){	mainRenderer->drawTriangle(x1,y1,z1,x2,y2,z2,x3,y3,z3); }
  void ofDrawCircle(const glm::vec3 & p, float radius){	ofDrawCircle(p.x, p.y, p.z, radius); }
  void ofDrawCircle(const glm::vec2 & p, float radius){	ofDrawCircle(p.x, p.y, 0.0, radius); }
  void ofDrawCircle(float x, float y, float radius){	ofDrawCircle(x,y,0,radius); }
  void ofDrawCircle(float x, float y, float z, float radius){	mainRenderer->drawCircle(x,y,z,radius); }
  void ofDrawEllipse(const glm::vec3 & p, float width, float height){	ofDrawEllipse(p.x, p.y, p.z, width, height); }
  void ofDrawEllipse(const glm::vec2 & p, float width, float height){	ofDrawEllipse(p.x, p.y, width, height); }
  void ofDrawEllipse(float x, float y, float width, float height){	ofDrawEllipse(x,y,0,width,height); }
  void ofDrawEllipse(float x, float y, float z, float width, float height){	mainRenderer->drawEllipse(x,y,z,width,height); }
  void ofDrawLine(const glm::vec3 & p1, const glm::vec3 & p2){	ofDrawLine(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z); }
  void ofDrawLine(const glm::vec2 & p1, const glm::vec2 & p2){	ofDrawLine(p1.x, p1.y, p2.x, p2.y); }
  void ofDrawLine(float x1,float y1,float x2,float y2){	ofDrawLine(x1, y1, 0.0f, x2, y2, 0.0f); }
  void ofDrawLine(float x1,float y1,float z1,float x2,float y2,float z2){	mainRenderer->drawLine(x1,y1,z1,x2,y2,z2); }
  void ofDrawRectangle(const ofRectangle & r){	ofDrawRectangle(r.x,r.y,0.0f,r.width, r.height); }
  void ofDrawRectangle(const glm::vec3 & p,float w,float h){	ofDrawRectangle(p.x, p.y, p.z, w, h); }
  void ofDrawRectangle(const glm::vec2 & p,float w,float h){	ofDrawRectangle(p.x, p.y, w, h); }
  void ofDrawRectangle(float x,float y,float w,float h){	ofDrawRectangle(x, y, 0.0f, w, h); }
  void ofDrawRectangle(float x,float y,float z,float w,float h){	mainRenderer->drawRectangle(x,y,z,w,h); }
  void ofDrawRectRounded(const ofRectangle & b, float r){	ofDrawRectRounded(b,r,r,r,r); }
  void ofDrawRectRounded(const glm::vec3 & p, float w, float h, float r){	ofDrawRectRounded(p.x, p.y, p.z, w, h, r,r,r,r); }
  void ofDrawRectRounded(const glm::vec2 & p, float w, float h, float r){	ofDrawRectRounded(p.x, p.y, 0.0, w, h, r,r,r,r); }
  void ofDrawRectRounded(float x, float y, float w, float h, float r){	ofDrawRectRounded(x,y,0.0f,w,h,r,r,r,r); }
  void ofDrawRectRounded(float x, float y, float z, float w, float h, float r){	ofDrawRectRounded(x,y,z,w,h,r,r,r,r); }
  void ofDrawRectRounded(const glm::vec3 & p, float w, float h, float topLeftRadius,float topRightRadius,float bottomRightRadius,float bottomLeftRadius){	ofDrawRectRounded(p.x,p.y,p.z,w,h,topLeftRadius,topRightRadius,bottomRightRadius,bottomLeftRadius); }
  void ofDrawRectRounded(const glm::vec2 & p, float w, float h, float topLeftRadius,float topRightRadius,float bottomRightRadius,float bottomLeftRadius){	ofDrawRectRounded(p.x,p.y,0.0,w,h,topLeftRadius,topRightRadius,bottomRightRadius,bottomLeftRadius); }
  void ofDrawRectRounded(const ofRectangle & b, float topLeftRadius,float topRightRadius,float bottomRightRadius,float bottomLeftRadius) { ofDrawRectRounded(b.x,b.y,0.0f,b.width,b.height,topLeftRadius,topRightRadius,bottomRightRadius,bottomLeftRadius); }
  void ofDrawRectRounded(float x, float y, float z, float w, float h, float topLeftRadius,float topRightRadius,float bottomRightRadius,float bottomLeftRadius) {
      switch (ofGetRectMode()) {
      case OF_RECTMODE_CENTER:
          x -= w / 2.0f;
          y -= h / 2.0f;
          break;
      default:
          break;
      }
      mainRenderer->getPath().clear();
      mainRenderer->getPath().rectRounded(x,y,z,w,h,topLeftRadius,topRightRadius,bottomRightRadius,bottomLeftRadius);
      mainRenderer->draw(mainRenderer->getPath());
  }
  void ofDrawCurve(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3){
      mainRenderer->getPath().clear();
      mainRenderer->getPath().curveTo(x0,y0);
      mainRenderer->getPath().curveTo(x1,y1);
      mainRenderer->getPath().curveTo(x2,y2);
      mainRenderer->getPath().curveTo(x3,y3);
      mainRenderer->draw(mainRenderer->getPath());
  }
  void ofDrawCurve(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3){
      mainRenderer->getPath().clear();
      mainRenderer->getPath().curveTo(x0,y0,z0);
      mainRenderer->getPath().curveTo(x1,y1,z1);
      mainRenderer->getPath().curveTo(x2,y2,z2);
      mainRenderer->getPath().curveTo(x3,y3,z3);
      mainRenderer->draw(mainRenderer->getPath());
  }void ofDrawBezier(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3){
      mainRenderer->getPath().clear();
      mainRenderer->getPath().moveTo(x0,y0);
      mainRenderer->getPath().bezierTo(x1,y1,x2,y2,x3,y3);
      mainRenderer->draw(mainRenderer->getPath());
  }
  void ofDrawBezier(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3){
      mainRenderer->getPath().clear();
      mainRenderer->getPath().moveTo(x0,y0,z0);
      mainRenderer->getPath().bezierTo(x1,y1,z1,x2,y2,z2,x3,y3,z3);
      mainRenderer->draw(mainRenderer->getPath());
  }
  void ofBeginShape(){ mainRenderer->getPath().clear(); }
  void ofVertex(float x, float y){ mainRenderer->getPath().lineTo(x,y); }
  void ofVertex(float x, float y, float z){	mainRenderer->getPath().lineTo(x,y,z); }
  void ofVertex(const glm::vec3 & p){ mainRenderer->getPath().lineTo(p); }
  void ofVertex(const glm::vec2 & p){ mainRenderer->getPath().lineTo(glm::vec3(p, 0.0)); }
  void ofVertices( const vector <glm::vec3> & polyPoints ){	for( const auto & p: polyPoints ){ mainRenderer->getPath().lineTo(p); } }
  void ofVertices( const vector <glm::vec2> & polyPoints ){	for( const auto & p: polyPoints ){ mainRenderer->getPath().lineTo(glm::vec3(p, 0.0)); } }
  void ofVertices( const vector <ofVec3f> & polyPoints ){ for( const auto & p: polyPoints ){ mainRenderer->getPath().lineTo(p); } }
  void ofVertices( const vector <ofVec2f> & polyPoints ){ for( const auto & p: polyPoints ){ mainRenderer->getPath().lineTo(p); } }
  void ofCurveVertex(float x, float y){	mainRenderer->getPath().curveTo(x,y); }
  void ofCurveVertex(float x, float y, float z){ mainRenderer->getPath().curveTo(x,y,z); }
  void ofCurveVertices( const vector <glm::vec3> & curvePoints){ for( const auto & p: curvePoints ){	mainRenderer->getPath().curveTo(p); } }
  void ofCurveVertices( const vector <glm::vec2> & curvePoints){ for( const auto & p: curvePoints ){	mainRenderer->getPath().curveTo(glm::vec3(p, 0.0)); } }
  void ofCurveVertices( const vector <ofVec3f> & curvePoints){ for( const auto & p: curvePoints ){	mainRenderer->getPath().curveTo(p); } }
  void ofCurveVertices( const vector <ofVec2f> & curvePoints){ for( const auto & p: curvePoints ){	mainRenderer->getPath().curveTo(p); } }
  void ofCurveVertex(const glm::vec3 & p){	mainRenderer->getPath().curveTo(p); }
  void ofCurveVertex(const glm::vec2 & p){	mainRenderer->getPath().curveTo(glm::vec3(p, 0.0)); }
  void ofBezierVertex(float x1, float y1, float x2, float y2, float x3, float y3){	mainRenderer->getPath().bezierTo(x1,y1,x2,y2,x3,y3); }
  void ofBezierVertex(const glm::vec3 & p1, const glm::vec3 & p2, const glm::vec3 & p3){	mainRenderer->getPath().bezierTo(p1, p2, p3); }
  void ofBezierVertex(const glm::vec2 & p1, const glm::vec2 & p2, const glm::vec2 & p3){	mainRenderer->getPath().bezierTo(glm::vec3(p1, 0.0), glm::vec3(p2,0.0), glm::vec3(p3,0.0)); }
  void ofBezierVertex(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3){	mainRenderer->getPath().bezierTo(x1,y1,z1,x2,y2,z2,x3,y3,z3); }
  void ofNextContour(bool bClose){ if (bClose){	mainRenderer->getPath().close(); } mainRenderer->getPath().newSubPath(); }
  void ofEndShape(bool bClose){ if (bClose){ mainRenderer->getPath().close(); } mainRenderer->draw(mainRenderer->getPath()); }

  // ofImage
  void draw(ofImage & _i, float x, float y) { draw(_i,x,y,0,_i.getWidth(),_i.getHeight()); }
  void draw(ofImage & _i, float x, float y, float z) { draw(_i,x,y,z,_i.getWidth(),_i.getHeight()); }
  void draw(ofImage & _i, glm::vec3 & pos) { draw(_i,pos.x,pos.y,pos.z,_i.getWidth(),_i.getHeight()); }
  void draw(ofImage & _i,float x, float y, float w, float h) { draw(_i,x,y,0,_i.getWidth(),_i.getHeight()); }
  void draw(ofImage & _i, float x, float y, float z, float w, float h) { drawSubsection(_i,x,y,z,w,h,0,0,_i.getWidth(),_i.getHeight()); }
  void draw(ofImage & _i, glm::vec3 & pos, float w, float h) { draw(_i,pos.x,pos.y,pos.z,w,h); }
  void drawSubsection(ofImage & _i, float x, float y, float w, float h, float sx, float sy) { drawSubsection(_i,x,y,0,w,h,sx,sy,w,h); }
  void drawSubsection(ofImage & _i, float x, float y, float w, float h, float sx, float sy, float _sw, float _sh) { drawSubsection(_i,x,y,0,w,h,sx,sy,_sw,_sh); }
  void drawSubsection(ofImage & _i, float x, float y, float z, float w, float h, float sx, float sy) { drawSubsection(_i,x,y,z,w,h,sx,sy,w,h); }
  void drawSubsection(ofImage & _i, float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh) { mainRenderer->draw(_i,x,y,z,w,h,sx,sy,sw,sh); }

  // ofPath
  void draw(ofPath & _p){ mainRenderer->draw(_p); }
  void draw(ofPath & _p, float x, float y){ mainRenderer->draw(_p,x,y); }

  // ofPolyline
  void draw(ofPolyline & _p){ mainRenderer->draw(_p); }

  // ofTrueTypeFont
  void drawString(ofTrueTypeFont &_t, std::string &  c, float x, float y) { mainRenderer->drawString(_t,c,x,y); }

  // ofVideoGrabber
  void draw(ofVideoGrabber & _v, float _x, float _y){ mainRenderer->draw(_v,_x,_y,_v.getWidth(),_v.getHeight()); }
  void draw(ofVideoGrabber & _v, float _x, float _y, float _w, float _h){ mainRenderer->draw(_v,_x,_y,_w,_h); }

  // ofVideoPlayer
  void draw(ofVideoPlayer & _v, float _x, float _y){ mainRenderer->draw(_v,_x,_y,_v.getWidth(),_v.getHeight()); }
  void draw(ofVideoPlayer & _v, float _x, float _y, float _w, float _h){ mainRenderer->draw(_v,_x,_y,_w,_h); }

  // MAIN RENDERER
  std::shared_ptr<ofBaseRenderer>   mainRenderer;

};
