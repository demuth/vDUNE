#!/bin/bash

cern="https://edms.cern.ch/file/"
path=$(dirname $(dirname "$0"))/assets/files/
asset=$1/$2/

echo "Reading config: $(dirname "$0")/Config/$1"

# Read a config file in.
files=()
while IFS= read -r line; do
   files+=("$line")
done <$(dirname "$0")/Config/$1

for filename in ${files[@]}; do
  echo "Read: ${filename}"
done

# Create an array of desired formats.
extensions=(.png .nwd)

# Make sure the asset directory exists before writing to it.
mkdir -p ${path}${asset}

# Walk through each combination of file stem and extension.
# Retrieving those files from CERN
for filename in ${files[@]}; do
  for extension in ${extensions[@]}; do
    r=$(wget \
    -O ${path}${asset}${filename}${extension} \
    ${cern}${asset}${filename}${extension})
  done
done