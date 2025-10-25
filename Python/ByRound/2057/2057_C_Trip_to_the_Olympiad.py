# Contest 2057, Problem C: Trip to the Olympiad
# URL: https://codeforces.com/contest/2057/problem/C

from sys import stdin, stdout

input = stdin.readline

for _ in range(int(input())):
    l, r = map(int, input().split())
    k = (l ^ r).bit_length() - 1
    a = l | ((1 << k) - 1)
    b = a + 1
    c = l if a == r or b == r else r
    stdout.write(f"{a} {b} {c} \n")
