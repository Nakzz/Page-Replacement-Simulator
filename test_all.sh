#!/bin/bash

testSize=10000;

page_size=(512 4096)
memory_size=(1 4 32)
trace_files=(4000  smallmix )
# bigmix 12million
for ((i=0; i < 2; i++));
do 
    for ((j=0; j < 3; j++));
    do
        for ((k=0; k < 4; k++));
        do
            echo Testing 537pfsim-fifo with page:${page_size[i]} mem:${memory_size[j]} file:${trace_files[k]}
            echo 
            
            ./537pfsim-fifo -p ${page_size[i]} -m ${memory_size[j]} ./trace_files/${trace_files[k]}.addrtrace
            returnVal=$?

            if [ $returnVal -eq  1 ];then
            echo "error"
            exit 1
            fi
            echo 
            
            echo Testing 537pfsim-lru with page:${page_size[i]} mem:${memory_size[j]} file:${trace_files[k]}
            echo 
            
            ./537pfsim-lru -p ${page_size[i]} -m ${memory_size[j]} ./trace_files/${trace_files[k]}.addrtrace
            returnVal=$?

            if [ $returnVal -eq  1 ];then
            echo "error"
            exit 1
            fi
            
            echo 
            echo Testing 537pfsim-clock with page:${page_size[i]} mem:${memory_size[j]} file:${trace_files[k]}
            echo 
            
            ./537pfsim-clock -p ${page_size[i]} -m ${memory_size[j]} ./trace_files/${trace_files[k]}.addrtrace
            returnVal=$?

            if [ $returnVal -eq  1 ];then
            echo "error"
            exit 1
            fi
            
            echo 
            echo 
            echo 

        done

    done
done

