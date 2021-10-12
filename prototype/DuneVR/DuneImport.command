#!/bin/bash

UE4_Version='4.26'
CurrentDirectory="`dirname \"$0\"`"
ProjectFilePath=$CurrentDirectory"/DuneVR.uproject"

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2060165_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Containment_System_-_ST1090485_BLEND.fbx \
Dune/SouthCavern/Detector \
ContainmentSystem

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2060165_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Side_Stairs_-_ST1086341_BLEND.fbx \
Dune/SouthCavern/Detector/Container/SideStairs

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2060166_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Roof_-_ST1079321_BLEND.fbx \
Dune/SouthCavern/Detector/Container/Top

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2060166_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Roof_Handrails_and_Wooden_floor_-_ST1087376_BLEND.fbx \
Dune/SouthCavern/Detector/Mezzanine/Floor

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2060167_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_TCO_-_ST1083026_BLEND.fbx \
Dune/SouthCavern/Detector/TCO

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2065465_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_CPA_-_ST1327997_BLEND.fbx \
Dune/SouthCavern/Detector/Internal/CPA

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2065465_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_End_Wall_-_ST1328105_BLEND.fbx \
Dune/SouthCavern/Detector/Internal/EndWall

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2065465_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Field_Cage_-_ST1327999_BLEND.fbx \
Dune/SouthCavern/Detector/Internal/FieldCage

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2065465_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_HV_and_Supports_-_ST1328121_BLEND.fbx \
Dune/SouthCavern/Detector/Internal/HV

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2066325_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Mezzanine_Structure_and_Supports_-_ST1083036_BLEND.fbx \
Dune/SouthCavern/Detector/Mezzanine/StructureAndSupports

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2066661_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Mezzanine_Platform_and_Access_-_ST1083732_BLEND.fbx \
Dune/SouthCavern/Detector/Mezzanine/PlatformAndAccess

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2066948_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Mezzanine_Proximity_Cryogenics_-_ST1083767_BLEND.fbx \
Dune/SouthCavern/Detector/Mezzanine/ProximityCryogenics

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2067822_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Detector_Mezzanine_Structure_and_Supports_-_ST1085480_BLEND.fbx \
Dune/SouthCavern/Detector/Mezzanine/DetectorStructureAndSupports

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2067825_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Internal_Cryogenics_-_ST1085449_BLEND.fbx \
Dune/SouthCavern/Detector/Internal/Cryogenics

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2173180_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Primary_Membrane_-_Bottom_BLEND.fbx \
Dune/SouthCavern/Detector/Internal/PrimaryMembrane/Bottom

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2173180_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Primary_Membrane_-_East_BLEND.fbx \
Dune/SouthCavern/Detector/Internal/PrimaryMembrane/East

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2173180_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Primary_Membrane_-_North_BLEND.fbx \
Dune/SouthCavern/Detector/Internal/PrimaryMembrane/North

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2173180_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Primary_Membrane_-_South_BLEND.fbx \
Dune/SouthCavern/Detector/Internal/PrimaryMembrane/South

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2173180_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Primary_Membrane_-_Top_BLEND.fbx \
Dune/SouthCavern/Detector/Internal/PrimaryMembrane/Top

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2173180_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Primary_Membrane_-_West_BLEND.fbx \
Dune/SouthCavern/Detector/Internal/PrimaryMembrane/West

$CurrentDirectory/ImportAsset.sh \
$CurrentDirectory/../../assets/SouthCavern/2060165_6/Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Floor_and_Walls_-_ST1079325_BLEND.fbx \
Dune/SouthCavern/Detector/Container/FloorAndWalls