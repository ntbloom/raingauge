
UNEXPORT="/sys/class/gpio/unexport"
SYSFS="/sys/class/gpio"
if [ -d "$SYSFS/gpio18" ]; then
    echo "Unexporting pin 18..."
    sudo echo 18 > $UNEXPORT
fi
if [ -d "$SYSFS/gpio25" ]; then
    echo "Unexporting pin 25..."
    sudo echo 25 > $UNEXPORT
fi
