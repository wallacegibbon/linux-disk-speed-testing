#! /bin/sh

ELF=test-program.out

gcc main.c -lcmd_argument_parser -o $ELF

if test "$1" = "sync"; then
	SYNC="--sync"
fi

for s in 8 64 128 1024 2048 4096 8192 16384 32768 65536 131072 262144; do
	./$ELF $SYNC --line_size $s --lines 10000
	echo
done

rm $ELF

