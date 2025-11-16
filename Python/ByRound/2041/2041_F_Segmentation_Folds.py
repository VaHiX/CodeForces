# Problem: CF 2041 F - Segmentation Folds
# https://codeforces.com/contest/2041/problem/F

"""
Code Purpose:
This solution computes the number of folding sequences that result in the shortest possible interval
when folding a segment [l, r] using two operations: LTR (fold left to right) and RTL (fold right to left).
The key idea is to use a BFS-like approach to explore all valid folding paths, tracking the minimum interval
length achievable, and counting how many paths lead to this minimum.

Algorithms/Techniques:
- Sieve of Eratosthenes for prime number generation
- BFS/DFS traversal over intervals with dynamic path tracking
- Modular arithmetic for large outputs

Time Complexity: O(R log log R + (r - l)^2), where R = max(r, l) is the range of numbers to check for primes.
Space Complexity: O(R), for storing prime information and intervals.
"""

M = 2 * 10**6
pre_is_prime = [True] * (M + 1)
pre_is_prime[0] = False
pre_is_prime[1] = False
for p in range(M + 1):
    if pre_is_prime[p]:
        for i in range(2 * p, M + 1, p):
            pre_is_prime[i] = False
primes = [p for p in range(M + 1) if pre_is_prime[p]]
mod = 998244353
T = int(input())
for t in range(T):
    L, R = map(int, input().split())
    L *= 2
    R *= 2
    is_prime = [True] * (R - L + 1)
    for p in primes:
        if pre_is_prime[p]:
            for i in range((-L) % p, R - L + 1, p):
                if i + L != p:
                    is_prime[i] = False
    LR = []
    queue = [(L, R)]
    while queue:
        l, r = queue.pop()
        end = True
        P = []
        for p in range(l + 1, (l + r) // 2 + 1):
            if is_prime[p - L]:
                P.append(p)
        if P:
            queue.append((max(P), r))
            end = False
        P = []
        for p in range((l + r + 1) // 2, r):
            if is_prime[p - L]:
                P.append(p)
        if P:
            queue.append((l, min(P)))
            end = False
        if end:
            LR.append((l, r))
    mi = min(r - l for l, r in LR)
    ans = 0
    for l, r in LR:
        if r - l == mi:
            ans += 1
    print(ans)


# https://github.com/VaHiX/CodeForces/