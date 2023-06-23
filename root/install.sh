#!/bin/bash

# download the binary file
curl -#fL -o text-dungeon https://github.com/Masbender/text-dungeon/releases/download/v0.01/text-dungeon

# allow binary to launch
sudo chmod +x text-dungeon

# generate desktop entry
touch text-dungeon.desktop
echo "" > text-dungeon.desktop
echo [Desktop Entry] >> text-dungeon.desktop
echo Name=Text Dungeon >> text-dungeon.desktop
echo Type=Application >> text-dungeon.desktop
echo Comment=A cool text dungeon game in your terminal! >> text-dungeon.desktop
echo Icon=$(pwd)/logo.jpg >> text-dungeon.desktop
echo Exec=$(pwd)/text-dungeon >> text-dungeon.desktop
