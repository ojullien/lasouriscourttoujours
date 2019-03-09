## -----------------------------------------------------
## LaSouris.
## Options
##
## @package ojullien\lasouriscourttoujours\work\optimize\include
## @license MIT <https://github.com/ojullien/lasouriscourttoujours/blob/master/LICENSE>
## -----------------------------------------------------------------------------

m_OPTION_DISPLAY=1
m_OPTION_LOG=0
m_OPTION_WAIT=0

while getopts "dlw?" m_OPTION; do
    case $m_OPTION in
    d)
        m_OPTION_DISPLAY=0
        ;;
    l)
        m_OPTION_LOG=1
        ;;
    w)
        m_OPTION_WAIT=1
        ;;
    \?)
        echo "Usage: `/usr/bin/basename $0` [option]"
        echo "\t-d\tdisplay mode. Contents are not displayed."
        echo "\t-l\tlog mode. Contents are logged."
        echo "\t-w\twait user. Wait for user input between actions."
        exit 1
        ;;
    esac
done

if [ $m_OPTION_DISPLAY -eq 1 ]; then

    display "Display mode is ON. Contents will be displayed."

    if [ $m_OPTION_LOG -eq 1 ]; then
        display "Log mode is ON. Contents will be logged."
    else
        display "Log mode is OFF. Contents will not be logged."
    fi

    if [ $m_OPTION_WAIT -eq 1 ]; then
        display "Wait mode is ON. Wait for user input between actions."
    else
        display "Wait mode is OFF. Do not wait for user input between actions."
    fi

fi
