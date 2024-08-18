#! /bin/bash
gcc_version=$(gcc --version | grep ^gcc | awk '{print $1 " " $4}')
if [ $# -lt 1 ]; then
    echo "Please input the run c script name"
else
    echo "$gcc_version is compiling $1"
    output_file="${1%.*}.out"
    rm -f ./output_file
    gcc -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -fstack-protector -Wall -Wextra -O0 -g $1 -o $output_file
    echo "Output file: $output_file"
fi
