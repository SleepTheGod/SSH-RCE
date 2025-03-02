#!/bin/bash
gcc -o vulnerable vulnerable.c -fno-stack-protector -z execstack -g
gcc -o exploit exploit.c
echo "[+] Compilation complete. Run ./exploit to execute."
