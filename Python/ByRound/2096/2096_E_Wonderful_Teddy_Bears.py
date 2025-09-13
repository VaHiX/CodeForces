# Contest 2096, Problem E: Wonderful Teddy Bears
# URL: https://codeforces.com/contest/2096/problem/E

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    s = input().strip()
    num = 0
    sol = 0
    ev = 0
    od = 1
    cnt = s.count("B")
    for i in range(n):
        if s[i] == "B":
            if (ev < cnt and (i - ev) % 2 == 0 and i >= ev) or od >= cnt or i < od:
                sol += (i - ev + 1) // 2
                ev += 2
            else:
                sol += (i - od + 1) // 2
                od += 2
    print(sol)
