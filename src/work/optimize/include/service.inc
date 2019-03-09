## -----------------------------------------------------
## Linux Scripts.
## Service functions
##
## @package ojullien\lasouriscourttoujours\work\optimize\include
## @license MIT <https://github.com/ojullien/lasouriscourttoujours/blob/master/LICENSE>
## -----------------------------------------------------------------------------

## -----------------------------------------------------
## Stops service temporarily
## -----------------------------------------------------

stopService () {
    if [ $# -lt 1 ] || [ -z "$1" ]; then
        error "Usage: stopService <name>"
        exit 1
    fi
    notice -n "Stopping $1:"
    /usr/sbin/service $1 stop > /dev/null 2>&1
    iReturn=$?
    if [ 0 -eq $iReturn ]; then
        success "OK"
    else
        error "NOK code: $iReturn"
    fi
    return $iReturn
}

## -----------------------------------------------------
## Starts service temporarily
## -----------------------------------------------------

startServiceTemporarily () {
    if [ $# -lt 1 ] || [ -z "$1" ]; then
        error "Usage: startServiceTemporarily <name>"
        exit 1
    fi
    notice -n "Starting $1:"
    /usr/sbin/service $1 start > /dev/null 2>&1
    iReturn=$?
    if [ 0 -eq $iReturn ]; then
        success "OK"
    else
        error "NOK code: $iReturn"
    fi
    return $iReturn
}

## -----------------------------------------------------
## Status service
## -----------------------------------------------------

statusService () {
    if [ $# -lt 1 ] || [ -z "$1" ]; then
        error "Usage: statusServiceTemporarily <name>"
        exit 1
    fi
    notice -n "Status $1:"
    /usr/sbin/service $1 status > /dev/null 2>&1
    iReturn=$?
    case $iReturn in
        0)
            notice "is running"
            ;;
        3)
            notice "is stopped or does not exist"
            ;;
        *)
            error "ERROR code: $iReturn"
    esac
    return $iReturn
}
