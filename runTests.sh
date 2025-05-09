#!/usr/bin/bash

#set -x

set -e

FIFO=inputQs

function cleanup {
    rm ${FIFO}
    exit 1
}

trap cleanup EXIT

if [ -p "${FIFO}" ]
then
    rm ${FIFO}
fi

mkfifo ${FIFO}

function test()
{
    while read M L
    do
	/usr/bin/time -f "${M} %e %M" ./shell -n -t <<< "${L}"
    done < ${FIFO}
}

echo 'Testing Floyd-Fixed-m'
./tester <<< 'F' > ${FIFO} &
test > Floyd-Fixed-m.dat 2>&1
sed -i -e -e 'N;s/\n/ /g' Floyd-Fixed-m.dat

echo 'Testing Galois-Fixed-m'
./tester <<< 'G' >  ${FIFO} &
test > Galois-Fixed-m.dat 2>&1
sed -i -e -e 'N;s/\n/ /g' Galois-Fixed-m.dat

gnuplot -c getPlot.gp time Fm
gnuplot -c getPlot.gp space Fm

echo 'Testing Floyd-Fixed-n'
./tester -t <<< 'F' > ${FIFO} &
test > Floyd-Fixed-n.dat 2>&1
sed -i -e -e 'N;s/\n/ /g' Floyd-Fixed-n.dat

echo 'Testing Galois-Fixed-n'
./tester -t <<< 'G' > ${FIFO} &
test > Galois-Fixed-n.dat 2>&1
sed -i -e -e 'N;s/\n/ /g' Galois-Fixed-n.dat

gnuplot -c getPlot.gp time Fn
gnuplot -c getPlot.gp space Fn

# set +x

exit 0
