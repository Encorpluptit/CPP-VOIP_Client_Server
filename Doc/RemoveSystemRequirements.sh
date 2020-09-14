#!/bin/bash

APT="xorg-dev libx11-xcb-dev libxcb-render0-dev libxcb-render-util0-dev libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-xinerama0-dev"
DNF=""

if [ -f /etc/os-release ]; then
    # freedesktop.org and systemd
    . /etc/os-release
    OS=$NAME
    echo $OS
    if [ $OS == "Pop!_OS" ]; then
        sudo apt remove "$APT"
    elif [ $OS == "Fedora" ]; then
        sudo dnf remove "$DNF"
    fi
#    if [[ "$OS" == "Pop!_OS"]]; then
#      sudo apt remove "$APT"
#    elif [ $OS == "Fedora" ]; then
#      sudo dnf remove
#    fi
fi
