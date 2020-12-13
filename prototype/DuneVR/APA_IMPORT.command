#!/bin/bash

UE4_Version='4.26'
CurrentDirectory="`dirname \"$0\"`"
ProjectFilePath=$CurrentDirectory"/DuneVR.uproject"

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/APA/APA-part-1/apa-composite-1.fbx \
Dune/SouthCavern/Detector/Internal/APA/part1

