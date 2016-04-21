#!/bin/sh
echo test > test_res.txt
for i in `seq 1 20`;
do
    echo 'pingpong:' >> test_res.txt
    (time ./pingpong) &>> test_res.txt
    echo 'nopingpong:' >> test_res.txt
    (time ./nopingpong) &>> test_res.txt
done
