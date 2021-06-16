#!/bin/bash

CURRENTDATE=$(date +"%d/%m/%Y %T")
FILE=projet

echo "IT45 Running task"
echo -e "Time - ${CURRENTDATE}\n"

if [ ! -f "$FILE" ]; then
  echo -e "File 'project' does not exits\nRun the building task beforehand !"
else
  eval ./projet
fi

