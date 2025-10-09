# Problem: CF 2077 E - Another Folding Strip
# https://codeforces.com/contest/2077/problem/E

"""
E. Another Folding Strip

Purpose:
This code computes the sum of f(a[l:r+1]) over all subarrays of array a,
where f(b) represents the minimum number of operations required to generate
a specific darkness pattern on a strip by folding and dyeing.

Algorithms/Techniques:
- Efficient computation using stack-based approach for calculating contributions
- Prefix/suffix logic with modular arithmetic

Time Complexity: O(n)
Space Complexity: O(n)

The key insight is that f(b) can be computed using a greedy method with stacks,
and the total contribution of each element in all subarrays is tracked.

Input Format:
- Multiple test cases.
- For each test case:
  - n (length of array)
  - Array of n integers

Output:
- Sum of f(a[l:r+1]) for all subarrays modulo 998244353
"""

from sys import stdin

input = lambda: stdin.readline()[:-1]

# Function to compute f(b) using the described folding process.
def calc(a):
    B = a.copy()
    n = len(a)
    if n == 0:
        return 0
    ans = 0
    while max(a) > 0:
        idx = -1
        for i in range(n):
            if a[i] > 0:
                idx = i
                break
        ans += 1
        now = idx - 1
        for i in range(n):
            if a[i] > 0 and (i - now) % 2 == 1:
                a[i] -= 1
                now = i
    print(B, ans)
    return ans


mod = 998244353

# Main solving function using stack approach for efficient calculation.
def solve(n, a):
    ans = 0
    stc = [[] for i in range(2)]  # Two stacks for even and odd indices
    for i in range(n):
        l = i + 1           # Left contribution: number of subarrays starting at or before i
        r = n - i           # Right contribution: number of subarrays ending at or after i
        rem = a[i]          # Current element value
        ans += rem * l * r  # Add its contribution to the total
        ans %= mod
        p = (i + 1) % 2     # Parity index for stack selection
        while rem > 0 and len(stc[p]) > 0:
            sz, idx = stc[p].pop()   # Pop from relevant stack
            use = min(sz, rem)       # How much of this segment to use
            sz -= use                # Remaining size after use
            rem -= use               # Remaining elements to process
            ans -= (idx + 1) * r * use  # Subtract contribution of this use
            ans %= mod
            if sz > 0:
                stc[p].append((sz, idx))   # Push back unused portion
        stc[i & 1].append((a[i], i))       # Add current element to appropriate stack
    return ans

# Naive approach for testing correctness (not used in final submission)
def naive(n, a):
    ans = 0
    for l in range(n):
        for r in range(n):
            ans += calc(a[l : r + 1])
    return ans

# Testing section - Disabled
import random

while False:
    n = random.randint(1, 4)
    a = [random.randint(1, 3) for i in range(n)]
    ans1 = solve(n, a)
    ans2 = naive(n, a)
    if ans1 != ans2:
        print(n, a, ans1, ans2)
        exit()

# Main input processing loop
for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    print(solve(n, a) % mod)


# https://github.com/VaHiX/codeForces/