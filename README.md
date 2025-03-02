# SSH Remote Code Execution Exploit (Zero-Day)

## 🚀 Exploiting a Buffer Overflow in `malloc()`

### **Created By**: Taylor Christian Newsome  

## 🔥 Overview
This exploit leverages a **buffer overflow vulnerability** in a custom SSH implementation that fails to properly allocate and manage memory. The program allocates **only 28 bytes**, but **writes 29 bytes**, leading to **memory corruption, return address overwrite, and potential remote code execution**.  

This proof-of-concept (PoC) **demonstrates exploitability** by:  
✅ **Overflowing the buffer** beyond the allocated size.  
✅ **Overwriting the return address** with a controlled value.  
✅ **Injecting shellcode** for arbitrary command execution.  
✅ **Bypassing protections** (`NX`, `Stack Canaries`, `ASLR`).  

---

## 🛠 **Vulnerability Details**
- **Function: `malloc()` allocates only 28 bytes** but writes 29 bytes, corrupting adjacent memory.  
- **Return address is miscalculated**, leading to **segmentation faults or arbitrary execution**.  
- **No error checking** for `open()` and `write()`, causing silent failures.  
- **`system()` call executes commands unsafely**, allowing **command injection**.  
- **Memory leak** due to missing `free(buffer)` calls.  

---

## 📜 **Exploitation Steps**
### **1️⃣ Identifying the Buffer Overflow**
Run the vulnerable program in GDB:
```bash
gdb -q ./vulnerable_program
(gdb) run $(python3 -c 'print("A"*40)')  # Overwrite EIP
```
