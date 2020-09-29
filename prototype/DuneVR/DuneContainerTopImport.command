#!/bin/bash

UE4_Version='4.24'
CurrentDirectory="`dirname \"$0\"`"
ProjectFilePath=$CurrentDirectory"/DuneVR.uproject"

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2060166_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Roof_-_ST1079321_BLEND.fbx \
Dune/SouthCavern/Detector/Container/Top
