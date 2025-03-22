#!/bin/bash
make clean
make
scp ./cegle-server openhd@192.168.3.1:~
