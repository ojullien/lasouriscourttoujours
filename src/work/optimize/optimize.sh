#!/bin/sh

## -----------------------------------------------------------------------------
## LaSouris.
## Optimize.
##
## @package ojullien\lasouriscourttoujours\work\optimize
## @license MIT <https://github.com/ojullien/lasouriscourttoujours/blob/master/LICENSE>
## -----------------------------------------------------------------------------

set -u;

## -----------------------------------------------------------------------------
## Includes
## -----------------------------------------------------------------------------
. "./include/string.inc"
. "./include/filesystem.inc"
. "./include/option.inc"
. "./include/apt.inc"
. "./include/others.inc"

## -----------------------------------------------------------------------------
## Load common configuration
## -----------------------------------------------------------------------------
. "./config/main.cnf"
. "./config/root.cnf"

## -----------------------------------------------------------------------------
## Start
## -----------------------------------------------------------------------------
separateLine
notice "Today is: `/bin/date -R`"
notice "The PID for `/usr/bin/basename $0` process is: $$"
waitUser

## -----------------------------------------------------------------------------
## Initial update and upgrade
## -----------------------------------------------------------------------------
separateLine
notice "Initial update and upgrade"
existsPackage "aptitude"
iAptitude=$?
if [ 0 -eq $iAptitude ]; then
    updateAndUpgrade
else
    upgradeWithAptget
    separateLine
    apt-get install -qqy aptitude
    iReturn=$?
    notice -n "Installing aptitude:"
    if [ 0 -eq $iReturn ]; then
        success "OK"
    else
        error "NOK code: $iReturn"
    fi
fi
cleanAndPurge
waitUser

## -----------------------------------------------------------------------------
## RAM
## -----------------------------------------------------------------------------
separateLine
notice "ZRam"
if [ $m_OPTION_LOG -eq 1 ]; then
    echo cat /proc/swaps >> "${m_LOGFILE}"
fi
cat /proc/swaps
installPackage "zram-config"
if [ $m_OPTION_LOG -eq 1 ]; then
    echo cat /proc/swaps >> "${m_LOGFILE}"
fi
cat /proc/swaps
waitUser

## -----------------------------------------------------------------------------
## SWAP
## -----------------------------------------------------------------------------
configureSwap
waitUser

## -----------------------------------------------------------------------------
## BASH
## -----------------------------------------------------------------------------
configureBash
waitUser

## -----------------------------------------------------------------------------
## HOSTS
## -----------------------------------------------------------------------------
configureHosts
waitUser

## -----------------------------------------------------------------------------
## UNINSTALL PACKAGES
## -----------------------------------------------------------------------------
uninstallPackage $m_PACKAGES_PURGE
waitUser

## -----------------------------------------------------------------------------
## INSTALL PACKAGES SYSTEM
## -----------------------------------------------------------------------------
installPackage $m_PACKAGES_SYSTEM
waitUser

## -----------------------------------------------------------------------------
## UNINSTALL MSCORE
## -----------------------------------------------------------------------------
#uninstallPackage "ttf-mscorefonts-installer"
#waitUser

## -----------------------------------------------------------------------------
## INSTALL PACKAGES APPS
## -----------------------------------------------------------------------------
installPackage $m_PACKAGES_APP
waitUser

## -----------------------------------------------------------------------------
## CONFIGURING TLP
## -----------------------------------------------------------------------------
configureTLP
waitUser

## -----------------------------------------------------
## GUFW
## -----------------------------------------------------
configureGUFW
waitUser

## -----------------------------------------------------------------------------
## END
## -----------------------------------------------------------------------------
updateAndUpgrade
cleanAndPurge

notice "Now is: `/bin/date -R`"
exit $iReturn
