#!/bin/sh
# gsoap版本: 2.8.51

mkdir org_lib
./bin/soapcpp2 -c -L -w -x all/all.h -Iimport -Icustom -dorg_lib -n -psoap
