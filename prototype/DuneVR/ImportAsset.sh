#!/bin/bash

UE4_Version='4.26'
CurrentDirectory="`dirname \"$0\"`"
FilePath=$1
AssetDump=/Game/$2/$3

/Users/Shared/Epic\ Games/UE_$UE4_Version/Engine/Binaries/Mac/UE4Editor-Cmd \
-project=DuneVR.uproject \
-run=ImportAssets \
-source=$FilePath \
-dest=$AssetDump \
-importsettings="" \
-AllowCommandletRendering

#This is where the files are dumped
#open /Users/lucassorenson/Library/Application\ Support/Epic/UnrealEngine/$UE4_Version"/Content/"$2/$3

mkdir -p $CurrentDirectory/Content/$2

cp -a /Users/lucassorenson/Library/Application\ Support/Epic/UnrealEngine/$UE4_Version"/Content/"$2/$3 $CurrentDirectory/Content/$2
