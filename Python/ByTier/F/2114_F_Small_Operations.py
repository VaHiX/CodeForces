# Problem: CF 2114 F - Small Operations
# https://codeforces.com/contest/2114/problem/F

"""
F. Small Operations

Problem Description:
Given integers x and k, we can perform operations to multiply or divide x by a value a where 1 <= a <= k.
The goal is to transform x into y with the minimum number of operations. If impossible, return -1.

Approach:
- First reduce both x and y by their GCD to work with coprime values.
- Check if any prime factor of x or y exceeds k; if so, it's impossible.
- Use BFS from the reduced x value to reach the reduced y value,
  considering only operations using multipliers/divisors up to k.

Time Complexity: O(sqrt(max(x, y)) * log(max(x, y)) * sqrt(k)) per test case
Space Complexity: O(sqrt(max(x, y))) for BFS queue and hashmap

Algorithm:
1. For each test case, process x and y:
   - Find GCD of x and y.
   - Reduce both to coprime values.
   - Validate all prime factors are <= k.
2. Run BFS from reduced x toward reduced y, counting steps.

"""

import collections
import math

for _ in range(int(input())):
    x, y, k = map(int, input().split())
    if k == 1:
        print(0 if x == y else -1)
        continue
    g = math.gcd(x, y)
    a, b = x // g, y // g
    p = True
    for n in [a, b]:
        if not p:
            break
        m, d = n, 2
        while d * d <= m:
            if m % d == 0:
                if d > k:
                    p = False
                    break
                while m % d == 0:
                    m //= d
            d += 1
        if m > 1 and m > k:
            p = False
    if not p:
        print(-1)
        continue
    s = 0
    for n in [a, b]:
        if n == 1:
            continue
        q = collections.deque([n])
        z = {n: 0}
        while q:
            u = q.popleft()
            c = z[u]
            if u == 1:
                s += c
                break
            i = 1
            while i * i <= u:
                if u % i == 0:
                    for o, w in [(u // i, i), (i, u // i)]:
                        if 1 < o <= k and w not in z:
                            z[w] = c + 1
                            q.append(w)
                i += 1
    print(s)


# https://github.com/VaHiX/codeForces/