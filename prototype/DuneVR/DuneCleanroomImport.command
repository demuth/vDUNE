#!/bin/bash

UE4_Version='4.24'
CurrentDirectory="`dirname \"$0\"`"
ProjectFilePath=$CurrentDirectory"/DuneVR.uproject"

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/cleanroom/LBNF-Clean_Room-2020-8-14_BLEND.fbx \
Dune/SouthCavern/Cleanroom

