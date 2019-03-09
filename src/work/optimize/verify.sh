#!/bin/sh

## -----------------------------------------------------------------------------
## AutoSave.
## Verifies if binaries and files exist.
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
. "./include/service.inc"

## -----------------------------------------------------------------------------
## Loads common configuration
## -----------------------------------------------------------------------------
clearScreen
. "./config/main.cnf"
. "./config/root.cnf"

## -----------------------------------------------------------------------------
## Binaries
## -----------------------------------------------------------------------------
m_Buffer="/bin/mkdir /bin/rm /usr/bin/ftp /usr/bin/find /bin/sync /bin/tar /usr/bin/tput /usr/bin/basename /usr/bin/dirname /bin/date /usr/sbin/service"

for sArg in ${m_Buffer}
do
    if [ ! -e "$sArg" ]; then
        error "Binary file $sArg is missing."
        exit 1
    fi
done

## -----------------------------------------------------------------------------
## Scripts
## -----------------------------------------------------------------------------
m_Buffer="./include/string.inc ./include/filesystem.inc ./include/option.inc ./config/main.cnf ./include/service.inc"

for sArg in ${m_Buffer}
do
    if [ ! -e "$sArg" ]; then
        error "File $sArg is missing."
        exit 1
    fi
done

## -----------------------------------------------------------------------------
## Working directories
## -----------------------------------------------------------------------------
m_Buffer="${m_DIR_UPLOAD} ${m_DIR_CACHE}"

for sArg in ${m_Buffer}
do
    if [ ! -d "$sArg" ]; then
        createDirectory $sArg
    fi
done

## -----------------------------------------------------------------------------
## Log directory
## -----------------------------------------------------------------------------
cleanDirectory "${m_DIR_SCRIPT}/log"

## -----------------------------------------------------------------------------
## Services
## -----------------------------------------------------------------------------
for sArg in ${m_SERVICES_START}
do
    statusService $sArg
done


success "Everything looks OK."
exit 0
