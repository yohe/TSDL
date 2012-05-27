#!/bin/sh

./server &

PID=$!
echo $PID > server_pid
echo start server $PID

sleep 1
