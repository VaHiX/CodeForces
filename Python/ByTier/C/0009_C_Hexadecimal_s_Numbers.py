# Contest 9, Problem C: Hexadecimal's Numbers
# URL: https://codeforces.com/contest/9/problem/C

cnt = 1
n = int(input())
while int(bin(cnt)[2:]) <= n:
    cnt += 1
print(cnt - 1)
