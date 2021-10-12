#!/bin/bash

UE4_Version='4.24'
CurrentDirectory="`dirname \"$0\"`"
ProjectFilePath=$CurrentDirectory"/DuneVR.uproject"

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2060165_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Floor_and_Walls_-_ST1079325_RED_BLEND.fbx \
Dune/SouthCavern/Detector/Container/FloorAndWalls/RedComponents