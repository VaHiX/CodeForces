# Contest 2104, Problem C: Card Game
# URL: https://codeforces.com/contest/2104/problem/C

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    n = int(input())
    s = input().rstrip("\n")
    if s[0] == "A":
        if s[-1] == "A" or s.count("B") == 1:
            print("Alice")
        else:
            print("Bob")
    else:
        print("Alice" if s[-2] == s[-1] == "A" else "Bob")
