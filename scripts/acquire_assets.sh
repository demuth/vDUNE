#!/bin/bash

cern="https://edms.cern.ch/file/"
path=/Users/lucassorenson/Code/dune/Subversion/trunk/assets/files/
asset=2173180/6/

files=(Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Primary_Membrane_-_FULL \
Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Primary_Membrane_-_Bottom \
Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Primary_Membrane_-_Top \
Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Primary_Membrane_-_North \
Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Primary_Membrane_-_South \
Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Primary_Membrane_-_East \
Cavern_S_-_Chamber_ES_-_Warm_Cryostat_SP_-_Primary_Membrane_-_West)

extensions=(.png .nwd)

mkdir -p ${path}${asset}

for filename in ${files[@]}; do
  for extension in ${extensions[@]}; do
    wget \
    -O ${path}${asset}${filename}${extension} \
    ${cern}${asset}${filename}${extension}
  done
done