#!/bin/sh
find /var/log -type f -iname *.gz -print -exec rm -f {} \;
find /var/log -type f -iname *.old -print -exec rm -f {} \;
find /var/log -type f -iname *.1 -print -exec rm -f {} \;
find /var/log -type f -iname *.2 -print -exec rm -f {} \;
find /var/log -type f -iname *.log.* -print -exec rm -f {} \;
find /var/log/exim4 -type f -iname *log.* -print -exec rm -f {} \;
find /var/log -type f -exec truncate -s 0 {} \;
