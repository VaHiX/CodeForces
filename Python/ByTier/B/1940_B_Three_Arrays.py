# Problem: CF 1940 B - Three Arrays
# https://codeforces.com/contest/1940/problem/B

"""
Algorithm: Dynamic Programming with Sorting and Prefix Minimization
Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing transformed arrays and auxiliary structures

This problem involves constructing two arrays A and B from given input arrays D, L, R, and initial values a0, b0.
At each step i, we add D[i] to both A[i] and B[i], and then choose to apply either:
- A[i] = min(A[i], L[i]) 
- B[i] = min(B[i], R[i])

We want to maximize A[n] + B[n]. The approach uses dynamic programming with reversed preprocessing and greedy selection.

Key observations:
1. We process indices in reverse order (from n to 1) to compute prefix sums
2. For each index i, we transform L[i] and R[i] by adding prefix sum up to i+1 
3. After transforming, we sort pairs (L[i], R[i]) to consider optimal choices greedily
4. Finally, we calculate maximum sum by evaluating all viable combinations of min operations

The solution works by:
- Preprocessing to compute cumulative sums and transformed arrays
- Sorting by L[i] values (first element of pairs)
- Using prefix minimums to find best B values and evaluating valid transitions
"""

import math
import sys

ints, dbg, yes = (
    lambda: list(map(int, input().split())),
    lambda *args, **kwargs: print(*args, file=sys.stderr, **kwargs),
    lambda x: print("YES" if x else "NO"),
)

(tests,) = (1,)

MOD = 10**9 + 7
for test in range(tests):
    (n,) = ints()
    d, l, r = [0] + ints(), [0] + ints(), [0] + ints()  # Add dummy zero at start for 1-indexing
    a0, b0 = ints()
    csum = 0
    goida = []  # Store (L[i], R[i]) pairs after transformation
    for i in range(n, 0, -1):  # Reverse iteration through indices from n down to 1
        # Add cumulative sum of D elements to L and R for current index
        l[i] += csum
        r[i] += csum
        goida.append((l[i], r[i]))
        csum += d[i]
    a0 += csum  # Final contribution to A[0] from all D values
    b0 += csum  # Final contribution to B[0] from all D values
    ans = 0
    to_make = math.inf  # Tracks minimum B value possible so far (greedy prefix)
    goida.sort()  # Sort by first element of pairs (L[i] values)
    ans = max(ans, goida[0][0] + b0)  # Initial case when choosing first L value
    for i in range(n):
        # Update prefix minimum for B values
        to_make = min(to_make, goida[i][1], b0)
        # If next L value is different, check transition to it (greedy)
        if i != n - 1 and goida[i + 1][0] != goida[i][0]:
            ans = max(ans, min(a0, goida[i + 1][0]) + to_make)
    ans = max(ans, a0 + min(r[1:]))  # Consider final case without any L transition
    print(ans)


# https://github.com/VaHiX/CodeForces/