## -----------------------------------------------------------------------------
## LaSouris.
## File System functions
##
## @package ojullien\lasouriscourttoujours\work\optimize\include
## @license MIT <https://github.com/ojullien/lasouriscourttoujours/blob/master/LICENSE>
## -----------------------------------------------------------------------------

## -----------------------------------------------------------------------------
## Checks whether a directory exists
## -----------------------------------------------------------------------------

checkDir () {
    if [ $# -lt 2 ] || [ -z "$1" ] || [ -z "$2" ]; then
        error "Usage: checkDir <label> <path>"
        exit 1
    fi
    if [ -d $2 ]; then
        success $1
        iReturn=0
    else
        error $1
        iReturn=1
    fi
    return $iReturn
}

## -----------------------------------------------------------------------------
## Checks whether a file exists
## -----------------------------------------------------------------------------

checkFile () {
    if [ $# -lt 2 ] || [ -z "$1" ] || [ -z "$2" ]; then
        error "Usage: checkFile <label> <path>"
        exit 1
    fi
    if [ -f $2 ]; then
        success $1
        iReturn=0
    else
        error $1
        iReturn=1
    fi
    return $iReturn
}

## -----------------------------------------------------------------------------
## Flush file system buffers
## -----------------------------------------------------------------------------

syncFile () {
    notice -n "flush file system buffers:"
    /bin/sync
    iReturn=$?
    if [ 0 -eq $iReturn ]; then
        success "OK"
    else
        error "NOK code: $iReturn"
    fi
    return $iReturn
}

## -----------------------------------------------------------------------------
## Directories
## -----------------------------------------------------------------------------

removeDirectory () {
    if [ $# -lt 1 ] || [ -z "$1" ]; then
        error "Usage: removeDirectory <path>"
        exit 1
    fi
    notice -n "Removing $1:"
    /bin/rm -Rf "$1"
    iReturn=$?
    if [ 0 -eq $iReturn ]; then
        success "OK"
    else
        error "NOK code: $iReturn"
    fi
    return $iReturn
}

cleanDirectory () {
    if [ $# -lt 1 ] || [ -z "$1" ]; then
        error "Usage: cleanDirectory <path>"
        exit 1
    fi
    notice -n "Cleaning $1:"
    /bin/rm -f "$1"//*
    iReturn=$?
    if [ 0 -eq $iReturn ]; then
        success "OK"
    else
        error "NOK code: $iReturn"
    fi
    return $iReturn
}

createDirectory () {
    if [ $# -lt 1 ] || [ -z "$1" ]; then
        error "Usage: createDirectory <top directory>"
        exit 1
    fi
    notice -n "Creating $1:"
    /bin/mkdir -p "$1"
    iReturn=$?
    if [ 0 -eq $iReturn ]; then
        success "OK"
    else
        error "NOK code: $iReturn"
    fi
    return $iReturn
}

## -----------------------------------------------------------------------------
## Compress
## -----------------------------------------------------------------------------

compressFile () {
    if [ $# -lt 2 ] || [ -z "$1" ] || [ -z "$2" ]; then
        error "Usage: compressFile <DESTINATION> <SOURCE>"
        exit 1
    fi
    notice -n "Compress '$2':"
    /bin/tar -cjf "$1.tar.bz2" "$2" > /dev/null 2>&1
    iReturn=$?
    if [ 0 -eq $iReturn ]; then
        success "OK"
    else
        error "NOK code: $iReturn"
    fi
    return $iReturn
}

## -----------------------------------------------------------------------------
## Find and remove files
## -----------------------------------------------------------------------------

findToRemove () {
    if [ $# -lt 2 ] || [ -z "$1" ] || [ -z "$2" ]; then
        error "Usage: findToRemove <PATH> <NAME>"
        exit 1
    fi
    notice -n "Remove all '$2' in '$1':"
    /usr/bin/find $1 -type f -name "$2" -exec /bin/rm -f '{}' \;
    iReturn=$?
    if [ 0 -eq $iReturn ]; then
        success "OK"
    else
        error "NOK code: $iReturn"
    fi
    return $iReturn
}
