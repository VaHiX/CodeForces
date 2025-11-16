# Problem: CF 2040 D - Non Prime Tree
# https://codeforces.com/contest/2040/problem/D

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    n = int(input())
    G = [[] for _ in range(n + 1)]
    for i in range(n - 1):
        u, v = map(int, input().split())
        G[u].append(v)
        G[v].append(u)
    arr = [0] * (n + 1)
    val = 2

    arr[1] = 1
    stack = [1]
    while stack:
        x = stack.pop()
        a = arr[x]
        for i in G[x]:
            if arr[i] == 0:
                # Check if (val - a) is not a prime number
                # We avoid primes by ensuring the difference is either:
                # - 1 (which is not prime), or
                # - Even and not 2 (since even numbers > 2 are not prime)
                while not (((val - a) % 2 == 0 or (val - a) == 1) and (val - a) != 2):
                    val += 1
                arr[i] = val
                val += 1
                stack.append(i)
    print(*arr[1:])

# https://github.com/VaHiX/CodeForces/