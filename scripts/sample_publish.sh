#!/bin/bash
# sample_publish.sh -- test mosquitto messaging

TOPIC=hello
MSG=world

HOSTNAME=3.17.146.14
PORT=8883

CERTDIR=/home/pi/raingauge/certs
CAFILE=$CERTDIR/ca.crt
CERT=$CERTDIR/client.crt
KEY=$CERTDIR/client.key


mosquitto_pub \
    -h $HOSTNAME \
    -p $PORT \
    --tls-version tlsv1.2 \
    --insecure \
    --cafile $CERTDIR/ca.crt \
    --cert $CERTDIR/client.crt \
    --key $CERTDIR/client.key \
    -t $TOPIC \
    -m $MSG \
    -d 
