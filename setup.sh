EXPORT="/sys/class/gpio/export"
SYSFS="/sys/class/gpio"
sudo echo 18 > $EXPORT
sudo echo 25 > $EXPORT

sleep 0.1s
sudo echo out > "$SYSFS/gpio18/direction"
sudo echo 1 > "$SYSFS/gpio18/value"

sudo echo in > "$SYSFS/gpio25/direction"
sudo echo rising > "$SYSFS/gpio25/edge"
sudo echo 1 > "$SYSFS/gpio25/active_low"

pinfo
