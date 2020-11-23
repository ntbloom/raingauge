# raingauge

Turn a single board computer into a rain gauge using C and some very simple dependencies.

---

### General architecture

1. Control the GPIO pins using sysfs
1. Connect a magnetized rain gauge like [this one](http://www.argentdata.com/catalog/product_info.php?products_id=168) to be interrupted on every click
1. Trigger a write to a local SQLite file on every raingauge tick
1. Publish an MQTT message to the cloud on every tick

---

### Development dependencies

Necessary Debian packages:

    - build-essential
    - libsqlite3-dev

Additonal Dependencies:

    - [Paho MQTT C client](https://www.eclipse.org/paho/index.php?page=clients/c/index.php)

Optional dependencies packages (debian packages unless otherwise noted):

    - clang-format
    - mosquitto
    - mosquitto-clients
    - mosquitto-dev
    - valgrind (Debian package is outdated, consider [building from source](https://valgrind.org/downloads/current.html)
    - [pinfo](https://github.com/ntbloom/pinfo)
