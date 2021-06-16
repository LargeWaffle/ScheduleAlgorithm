#!/bin/bash

CURRENTDATE=$(date +"%d/%m/%Y %T")
FILE=projet

echo "IT45 Building task"
echo -e "Time - ${CURRENTDATE}\n"

if test -f "$FILE"; then
  echo "File 'project' already exists. File overwritten"
  eval rm projet
fi

echo "Generating executable..."
eval make