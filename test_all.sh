#!/bin/bash

testSize=10000;

page_size=(512 4096)
memory_size=(1 4 32)

for ((i=0; i < 2; i++));
do 
    for ((j=0; j < 3; j++));
    do
        echo Testing 537pfsim-fifo with page:${page_size[i]} mem:${memory_size[j]}
        echo 
        echo Testing 537pfsim-lru with page:${page_size[i]} mem:${memory_size[j]}
        echo 
        echo Testing 537pfsim-clock with page:${page_size[i]} mem:${memory_size[j]}
        echo 
        echo 
        echo 

#   ./537ps -p $i
#   returnVal=$?

#   if [ $returnVal -eq  1 ];then
#     echo "error"
#     exit 1
#   fi
    done
done

