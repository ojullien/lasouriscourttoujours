#!/bin/sh

## -----------------------------------------------------------------------------
## LaSouris.
## Install.
##
## @package ojullien\lasouriscourttoujours
## @license MIT <https://github.com/ojullien/lasouriscourttoujours/blob/master/LICENSE>
## -----------------------------------------------------------------------------

set -u;

## -----------------------------------------------------
## Variables
## -----------------------------------------------------

# Working directory
m_DIR=`pwd`

# Work directory
m_DIR_WORK="work"
m_DIR_WORK_SRC=$m_DIR/$m_DIR_WORK
m_DIR_WORK_DEST=/root

# Clean script
m_FILE_CLEAN_SRC=$m_DIR/var/clean.sh
m_FILE_CLEAN_DEST=/var

# Include directory
m_DIR_INCLUDE=$m_DIR_WORK/optimize/include

# Options
m_LOGFILE=$m_DIR/install.log
m_OPTION_DISPLAY=1
m_OPTION_LOG=0

## -----------------------------------------------------------------------------
## Includes
## -----------------------------------------------------------------------------
. "./${m_DIR_INCLUDE}/string.inc"
. "./${m_DIR_INCLUDE}/filesystem.inc"

## -----------------------------------------------------
## Trace
## -----------------------------------------------------

display "-----------------------------------------------------"
notice " Main Configuration:"
checkDir "\tWorking directory:\t\t${m_DIR}" $m_DIR
checkDir "\tWork directory source:\t\t${m_DIR_WORK_SRC}" $m_DIR_WORK_SRC
checkDir "\tWork directory destination:\t${m_DIR_WORK_DEST}" $m_DIR_WORK_DEST
checkFile "\tClean file source:\t\t${m_FILE_CLEAN_SRC}" $m_FILE_CLEAN_SRC
checkDir "\tClean file destination:\t\t${m_FILE_CLEAN_DEST}" $m_FILE_CLEAN_DEST
display "-----------------------------------------------------"

## -----------------------------------------------------
## Usefull functions
## -----------------------------------------------------

copyFile () {
    if [ $# -lt 2 ] || [ -z "$1" ] || [ -z "$2" ]; then
        error "Usage: copyFile <source> <destination>"
        exit 1
    fi
    notice -n "Copying $1 to $2:"
    cp --recursive $1 $2
    iReturn=$?
    if [ 0 -eq $iReturn ]; then
        success "OK"
    else
        error "NOK code: $iReturn"
    fi
    return $iReturn
}

## -----------------------------------------------------
## Work directory
## -----------------------------------------------------
createDirectory $m_DIR_WORK
copyFile $m_FILE_CLEAN_SRC $m_FILE_CLEAN_DEST
copyFile $m_DIR_WORK_SRC $m_DIR_WORK_DEST
