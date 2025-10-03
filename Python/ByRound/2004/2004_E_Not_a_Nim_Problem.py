# Contest 2004, Problem E: Not a Nim Problem
# URL: https://codeforces.com/contest/2004/problem/E

import functools
import operator
import sys
input = lambda: sys.stdin.buffer.readline().decode()

N = 10 ** 7 + 1
sg = [0] * N
sg[1] = 1
primes = []
for i in range(3, N, 2):
    if sg[i] == 0:
        primes.append(i)
        sg[i] = len(primes) + 1
    for p in primes:
        if p > primes[sg[i] - 2] or i * p >= N:
            break
        sg[i * p] = sg[p]

for _ in range(int(input())):
    input()
    ans = functools.reduce(operator.xor, (sg[x] for x in map(int, input().strip().split())), 0)
    print('Bob' if ans == 0 else 'Alice')
