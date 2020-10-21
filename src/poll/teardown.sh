echo "Unexporting pins..."

UNEXPORT="/sys/class/gpio/unexport"
sudo echo 18 > $UNEXPORT
sudo echo 25 > $UNEXPORT
