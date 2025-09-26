# Problem: CF 2137 F - Prefix Maximum Invariance
# https://codeforces.com/contest/2137/problem/F

"""
F. Prefix Maximum Invariance
Algorithm: Monotonic stack with binary search optimization
Time Complexity: O(n log n) per test case
Space Complexity: O(n)

The problem involves computing the sum of maximum number of positions where 
z[i] = y[i] over all possible arrays z that have the same prefix maxima as x.
We use a monotonic stack to efficiently track valid candidates for optimal z.

For each subarray [l, r], we compute f(a[l:r+1], b[l:r+1]) which equals:
- For each position i in the subarray, we try to place b[i] in z[i]
- We want z[i] such that prefix maxima stay the same as in a
- The answer is the count of positions where this can be done optimally

The key insight is that for a valid array z, at each position i,
z[i] ≤ max(a[0:i]) (to maintain prefix maxima).
We use stack + binary search to efficiently compute how many such placements work.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def solve646():
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    s = []  # monotonic stack storing indices
    res = 0
    for i in range(n):
        # Pop elements from stack while current element is greater than stack top's value
        while s and a[i] > a[s[-1]]:
            s.pop()
        
        t = 0
        if a[i] ^ b[i]:  # XOR check: if a[i] != b[i]
            # If stack has elements and the max in stack is >= b[i], we find correct position using binary search
            if s and a[s[0]] >= b[i]:
                l, r = 0, len(s)
                while l + 1 < r:
                    m = l + r >> 1
                    if a[s[m]] >= b[i]:
                        l = m
                    else:
                        r = m
                t = (n - i) * (s[l] + 1)
        else:
            # If a[i] == b[i], all positions from s[0] to i could be valid with full overlap
            t = (i + 1) * (n - i)
        res += t
        s.append(i)
    return res


res_test = []
for _ in range(int(input())):
    res_test.append(solve646())
sys.stdout.write("\n".join(map(str, res_test)))


# https://github.com/VaHiX/codeForces/