#!/bin/sh
LOG_FILE=hello.txt

grep "���ϸ�" $LOG_FILE || grep "����ȷ" $LOG_FILE || grep "����" $LOG_FILE || grep "ʧ��" $LOG_FILE

#echo "the output is $?"

if [ $? -eq 0 ]; then
    rm -f  $LOG_FILE
    echo "remove the hello.txt"
fi
