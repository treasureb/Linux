#! /bin/bash

echo "Please Enter File!"
read file
if [ -f $file ]
then
    if [ -s $file ]
    then
        echo "0"
    else
        echo "1"

    fi
else
    echo "1"

fi
