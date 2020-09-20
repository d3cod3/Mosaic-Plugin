#!/bin/bash

SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"

PLUGINNAME="MosaicObjectTemplate"

cp $SCRIPTPATH/bin/$PLUGINNAME.framework/Versions/A/$PLUGINNAME ~/Documents/Mosaic/plugins/$PLUGINNAME.bundle
