# Contest 286, Problem A: Lucky Permutation
# URL: https://codeforces.com/contest/286/problem/A

import sys

input = sys.stdin.readline

n = int(input())
if n == 1:
    print(1)
    exit(0)
elif n % 4 == 2 or n % 4 == 3:
    print(-1)
    exit(0)

d = list(range(1, n + 1))
e = d.copy()

for i in range(0, n // 2, 2):
    d[i] = i + 2
    x = 0
    while x < 4:
        d[d[i] - 1] = n - i
        i = d[i] - 1
        x += 1

print(" ".join(map(str, d)))
