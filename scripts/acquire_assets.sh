#!/bin/bash

cern="https://edms.cern.ch/file/"
path=$(dirname $(dirname "$0"))/assets/files/
asset=2173180/6/

files=()
while IFS= read -r line; do
   files+=("$line")
done <$(dirname "$0")/Config/2173180.7

extensions=(.png .nwd)

mkdir -p ${path}${asset}

for filename in ${files[@]}; do
  for extension in ${extensions[@]}; do
    wget \
    -O ${path}${asset}${filename}${extension} \
    ${cern}${asset}${filename}${extension}
  done
done