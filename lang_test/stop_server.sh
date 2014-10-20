#!/bin/sh

if [ -e server_pid ]; then
    PID=`cat server_pid`
    kill $PID
    echo stop server $PID
    rm server_pid
    exit
fi

