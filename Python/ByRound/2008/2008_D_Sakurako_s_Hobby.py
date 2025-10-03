# Contest 2008, Problem D: Sakurako's Hobby
# URL: https://codeforces.com/contest/2008/problem/D

t = int(input())
for _ in range(t):
    n = int(input())
    b = [0] * (n + 1)
    us = [0] * (n + 1)
    p = [k-1 for k in map(int, input().split())]
    s = input()
    for i in range(0, n):
        if us[i]:
            continue
        sz = 0
        while not us[i]:
            us[i] = 1
            sz += s[i] == '0'
            i = p[i]
        while us[i] != 2:
            b[i] = sz
            us[i] = 2
            i = p[i]
    print(" ".join(map(str, b[:-1])))