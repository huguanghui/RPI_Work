#!/bin/sh
# gSoap版本: 2.8.51

mkdir all
strall="devicemgmt.wsdl event.wsdl imaging.wsdl media.wsdl media2.wsdl deviceio.wsdl ptz.wsdl search.wsdl recording.wsdl receiver.wsdl replay.wsdl display.wsdl thermal.wsdl schedule.wsdl provisioning.wsdl doorcontrol.wsdl credential.wsdl analyticsdevice.wsdl analytics.wsdl advancedsecurity.wsdl actionengine.wsdl accessrules.wsdl accesscontrol.wsdl metadatastream.xsd radiometry.xsd"
echo $strall
echo start wsdl2h ..
#cd dir
./bin/wsdl2h -sckd -o ./all/all.h -Nabc -t./typemap.dat $strall
cp onvif-header.h all/
cd all
cat all.h >> ./onvif-header.h
mv onvif-header.h all.h
cd ..
