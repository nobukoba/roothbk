#!/bin/bash

mv minipacklib minipacklib.org
cp -r minipacklib.org minipacklib
cd minipacklib.org
for str in *.f
do
    echo $str
    ../conv.py < $str > ../minipacklib/$str
done

cd hbook
for str in *.inc
do
    echo $str
    ../../conv.py < $str > ../../minipacklib/hbook/$str
done

cd ../zebra
for str in *.inc
do
    echo $str
    ../../conv.py < $str > ../../minipacklib/zebra/$str
done

cd ../../

sed -i 's/\/4hhide,4hhid1,4hhid2,/\/4HHIDE,4HHID1,4HHID2,/'  minipacklib/hbook.f
sed -i 's/4hhco1,4hhco2\//4HHCO1,4HHCO2\//'  minipacklib/hbook.f
sed -i 's/"#""!:"/"#'\''!:""/'  minipacklib/zebra.f
