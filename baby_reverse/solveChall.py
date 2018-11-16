listA = [0x0a, 0x0d, 0x06, 0x1c, 0x22, 0x38, 0x18, 0x26, 0x36, 0x0f, 0x39, 0x2b, 0x1c, 0x59, 0x42, 0x2c, 0x36, 0x1a, 0x2c, 0x26, 0x1c, 0x17, 0x2d, 0x39, 0x57, 0x43, 0x01, 0x07, 0x2b, 0x38, 0x09, 0x07, 0x1a, 0x01, 0x17, 0x13, 0x13, 0x17, 0x2d, 0x39, 0x0a, 0x0d, 0x06, 0x46, 0x5c, 0x7d, 0x00, 0x2e]

def solve(char, listA):
   string = char+chr(32)*45
   listb = list(string)
   for i in range(0, 45):
      while ord(listb[i])^ord(listb[i+1]) != listA[i]:
         listb[i+1] =chr(ord(listb[i+1])+1)
         if(ord(listb[i+1]) > 125):
             return
   print("".join(listb))

count = 32
while(count < 125):
    solve(chr(count), listA)
    count += 1
# flag{Yay_if_th1s_is_yer_f1rst_gnisrever_flag!}
