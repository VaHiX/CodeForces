# Contest 1867, Problem B: XOR Palindromes
# URL: https://codeforces.com/contest/1867/problem/B

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n = int(input())
    s = input()
    c = 0
    for i in range(n // 2):
        if s[i] != s[n - i - 1]:
            c += 1
    if n % 2:
        sys.stdout.write("0" * c + "1" * (n - 2 * c + 1) + "0" * c + "\n")
    else:
        sys.stdout.write("0" * c + "10" * ((n - 2 * c) // 2) + "1" + "0" * (c) + "\n")
