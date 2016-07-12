#!/bin/sh
LOG_FILE=hello.txt

grep "不合格" $LOG_FILE || grep "不正确" $LOG_FILE || grep "有误" $LOG_FILE || grep "失败" $LOG_FILE

#echo "the output is $?"

if [ $? -eq 0 ]; then
    rm -f  $LOG_FILE
    echo "remove the hello.txt"
fi
