#!/bin/bash
tmp=`ps -ef | grep voice| grep -v grep | awk '{print $2}'`
echo ${tmp}
kill -9 ${tmp}

