# Contest 1765, Problem K: Torus Path
# URL: https://codeforces.com/contest/1765/problem/K

from sys import stdin

input = stdin.buffer.readline
n = int(input())
mi = 10**9
su = 0
for i in range(n):
    l = [int(x) for x in input().split()]
    su += sum(l)
    if l[n - i - 1] < mi:
        mi = l[n - i - 1]
print(su - mi)
