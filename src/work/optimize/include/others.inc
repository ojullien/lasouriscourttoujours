## -----------------------------------------------------
## LaSouris.
## Other functions
##
## @package ojullien\lasouriscourttoujours\work\optimize\include
## @license MIT <https://github.com/ojullien/lasouriscourttoujours/blob/master/LICENSE>
## -----------------------------------------------------------------------------

## -----------------------------------------------------
## HOSTS
## -----------------------------------------------------

configureHosts () {
    separateLine
    notice "Configuring hosts"
    sed -i "s/127.0.0.1\tlocalhost/127.0.0.1\t`uname -n` localhost/" /etc/hosts > /dev/null
    iReturn=$?
    notice -n "Configure hosts:"
    if [ 0 -eq $iReturn ]; then
        success "OK"
    else
        error "NOK code: $iReturn"
    fi
    cat /etc/hosts
    return $iReturn
}

## -----------------------------------------------------
## BASHRC
## -----------------------------------------------------

configureBash () {
    separateLine
    notice "Configuring bash"
    m_Buffer="/root/.bash_aliases /home/lasouris/.bash_aliases"
    for sArg in ${m_Buffer}
    do
        echo alias rm=\"rm -i\" | tee $sArg
        echo alias cp=\"cp -i\" | tee -a $sArg
        echo alias mv=\"mv -i\" | tee -a $sArg
    done
    chown lasouris:lasouris /home/lasouris/.bash_aliases
    iReturn=$?
    notice -n "Configure bash:"
    if [ 0 -eq $iReturn ]; then
        success "OK"
    else
        error "NOK code: $iReturn"
    fi
    return $iReturn
}

## -----------------------------------------------------
## SWAP
## -----------------------------------------------------

configureSwap () {
    separateLine
    notice "Configuring swap"
    cat /proc/sys/vm/swappiness
    echo vm.swappiness=5 | tee /etc/sysctl.d/99-swappiness.conf
    echo vm.vfs_cache_pressure=50 | tee -a /etc/sysctl.d/99-swappiness.conf
    sysctl -p /etc/sysctl.d/99-swappiness.conf
    iReturn=$?
    notice -n "Configure swap:"
    if [ 0 -eq $iReturn ]; then
        success "OK"
    else
        error "NOK code: $iReturn"
    fi
    swapoff -av
    swapon -av
    cat /proc/sys/vm/swappiness
    return $iReturn
}

## -----------------------------------------------------
## TLP
## -----------------------------------------------------

configureTLP () {
        separateLine
        notice "Configuring tlp"
        tlp start
        iReturn=$?
        notice -n "Start tlp:"
        if [ 0 -eq $iReturn ]; then
            success "OK"
        else
            error "NOK code: $iReturn"
        fi
        systemctl enable tlp
        iReturn=$?
        notice -n "Enable tlp:"
        if [ 0 -eq $iReturn ]; then
            success "OK"
        else
            error "NOK code: $iReturn"
        fi
        systemctl enable tlp-sleep
        iReturn=$?
        notice -n "Enable tlp-sleep:"
        if [ 0 -eq $iReturn ]; then
            success "OK"
        else
            error "NOK code: $iReturn"
        fi
        return $iReturn
}

## -----------------------------------------------------
## GUFW
## -----------------------------------------------------

configureGUFW () {
        separateLine
        notice "Configuring gufw"
        ufw enable
        iReturn=$?
        notice -n "Start gufw:"
        if [ 0 -eq $iReturn ]; then
            success "OK"
        else
            error "NOK code: $iReturn"
        fi
        systemctl enable ufw
        iReturn=$?
        notice -n "Enable gufw:"
        if [ 0 -eq $iReturn ]; then
            success "OK"
        else
            error "NOK code: $iReturn"
        fi
        return $iReturn
}
