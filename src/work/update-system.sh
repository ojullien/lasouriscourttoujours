#!/bin/sh
aptitude update
aptitude full-upgrade -y
echo ----------------------
echo -- CLEAN -------------
echo ----------------------
aptitude clean
aptitude autoclean
apt-get autoremove --purge
echo ----------------------
echo -- SELECTIONS --------
echo ----------------------
dpkg --get-selections | grep -Ei "Linux-headers|linux-image"
echo ----------------------
echo -- ORPHAN ------------
echo ----------------------
deborphan
echo ----------------------
echo -- ORPHAN CONFIG -----
echo ----------------------
deborphan --find-config
