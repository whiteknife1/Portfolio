#before running enter: export team_name="bi0s" to set environment variable
#string must be typed manually or copied and pasted as an argument
start = "|#4b~W7h;Wj<5!k=on9b5?"
l = list(start)
print(l)
for a in range(0, 22):
    if a%2 == 0:
        l[a] = chr(ord(l[a])^0xc)
        l[a] = chr(ord(l[a])-0x4)
    else:
        l[a] = chr(ord(l[a])^0xc)
        l[a] = chr(ord(l[a])+0x4)
print(''.join(l))
#flag{l34rn_7h3_b451c5_f1r57}
