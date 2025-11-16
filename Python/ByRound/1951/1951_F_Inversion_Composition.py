# Problem: CF 1951 F - Inversion Composition
# https://codeforces.com/contest/1951/problem/F

"""
Algorithm/Technique:
This solution is based on computing inversions in permutations and trying to construct
a valid permutation q such that inv(q) + inv(q·p) = k.

Key Concepts:
- Inversion count in a permutation can be computed using a Fenwick tree (binary indexed tree).
- We compute the inversion count of the inverse permutation p^-1.
- The problem becomes finding how to split the allowed inversions (k - x) between inv(q) and inv(q·p).
- The idea is to build q such that we can adjust inv(q) to match the desired target by swapping elements.

Time Complexity:
- For each test case: O(n log n) due to Fenwick tree operations and permutation handling.
- Overall for all test cases: O(n log n) per test case, with total n up to 3 * 10^5.

Space Complexity:
- O(n) for storing arrays, Fenwick tree structure and intermediate results.
"""

import sys

R = sys.stdin.readline
S = lambda: map(int, R().split())


def inv(a):
    # Computes inversion counts using Fenwick tree
    n = len(a)
    M = 1 << (n - 1).bit_length()
    t = [0] * 2 * M
    r = []
    for c in a:
        y, z, p = M + c, 2 * M - 1, 0
        while y < z:
            if y & 1:
                p += t[y]
                y += 1
            y //= 2
            z //= 2
        p += t[z]
        r += (p,)
        y = M + c - 1
        while y:
            t[y] += 1
            y //= 2
    return r


for _ in range(int(R())):
    n, k = S()
    p = [*S()]
    r = [0] * n
    # Construct permutation r such that r[p[i]-1] = i+1
    for i in range(n):
        r[p[i] - 1] = i + 1
    
    y = inv(r)  # Get inversion counts of r
    x = sum(y)  # Total inversions in r
    
    # Check feasibility conditions
    if (k + x) & 1 or k < x or k + x > n * (n - 1):
        print("NO")
        continue
    
    print("YES")
    g = (k - x) // 2  # Extra inversions to assign to q
    
    if not g:
        print(*r)
        continue
    
    c = 0
    y += (0,)  # Add one extra element for indexing convenience
    for i in range(n):
        c += i - y[i]
        if c == g:
            # Construct q as reversed prefix followed by suffix
            q = list(range(i + 1, 0, -1)) + list(range(i + 2, n + 1))
            print(*q)
            break
        if c > g:
            # Adjust q to meet the required inversion count
            h = i - y[i] + g - c
            q = list(range(i, 0, -1)) + list(range(i + 1, n + 1))
            j = 0
            while h:
                q[j], q[i] = q[i], q[j]
                if r[j] < r[i]:
                    h -= 1
                j += 1
            print(*q)
            break


# https://github.com/VaHiX/CodeForces/