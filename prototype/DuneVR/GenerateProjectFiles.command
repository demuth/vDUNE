#!/bin/bash

UE4_Version='4.24'
CurrentDirectory="`dirname \"$0\"`"
ProjectFilePath=$CurrentDirectory"/DuneVR.uproject"

cd /Users/Shared/Epic\ Games/UE_$UE4_Version/Engine/Build/BatchFiles/Mac

./GenerateProjectFiles.sh \
-project=$ProjectFilePath
