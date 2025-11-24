# Problem: CF 2144 E2 - Looking at Towers (difficult version)
# https://codeforces.com/contest/2144/problem/E2

"""
E2. Looking at Towers (difficult version)

Purpose:
This code solves the problem of counting subsequences where the left and right visible tower heights (L(a) and R(a)) remain unchanged from the original array.

Algorithm:
1. Precompute powers of 2 modulo 998244353 for efficiency.
2. Compute prefix arrays to determine visible elements from both directions.
3. Use dynamic programming with bit manipulation to count valid subsequences efficiently.

Time Complexity: O(n * log(n)) per test case due to bisect operations and nested loops.
Space Complexity: O(n) for storing intermediate arrays and results.

Approach:
- The algorithm uses a two-pass approach:
  - First, track visible elements from left to right (prav) and right to left (lev).
  - Then, calculate combinations using dynamic programming with modular arithmetic.
"""

import bisect

step = [1]
st = 1
for i in range(500000):
    st *= 2
    st %= 998244353
    step.append(st)

for test in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    ma = 0
    prav = []
    lev = []
    # Build prefix arrays of visible elements from left and right
    for x in a:
        if x > ma:
            prav.append(x)
            ma = x
    ma = 0
    for i in range(n):
        if a[n - i - 1] > ma:
            lev.append(a[n - i - 1])
            ma = a[n - i - 1]
    
    # Dynamic programming arrays for left pass
    poslev = [0] * (len(lev) + 1)
    poslev[0] = 1
    koldv = [0] * len(lev)
    otm = []
    sm = 0
    
    # Process elements from right to left for computing contribution values
    for i in range(n - 1, -1, -1):
        el = a[i]
        if el == ma:
            otm.append(poslev[-1] * step[sm] + poslev[-2] * step[sm - koldv[-1]])
        ind = bisect.bisect_left(lev, el)
        sm += 1
        koldv[ind] += 1
        if lev[ind] == el:
            poslev[ind + 1] *= step[koldv[ind]]
            if ind == len(lev) - 1:
                sm -= koldv[ind]
            else:
                koldv[ind + 1] += koldv[ind]
            koldv[ind] = 0
            poslev[ind + 1] += poslev[ind]
            poslev[ind + 1] %= 998244353
            
    # Dynamic programming arrays for right pass  
    posprav = [0] * (len(prav) + 1)
    posprav[0] = 1
    ans = 0
    koldv = [0] * len(prav)
    sm = 0
    
    # Process elements from left to right, calculate final answer using previously computed values
    for i in range(n):
        el = a[i]
        if el == ma:
            ans += posprav[-2] * otm.pop() * step[sm - koldv[-1]]
            ans %= 998244353
            posprav[-1] = 0
        else:
            ind = bisect.bisect_left(prav, el)
            sm += 1
            koldv[ind] += 1
            if prav[ind] == el:
                posprav[ind + 1] *= step[koldv[ind]]
                if ind == len(prav) - 2:
                    sm -= koldv[ind]
                else:
                    koldv[ind + 1] += koldv[ind]
                koldv[ind] = 0
                posprav[ind + 1] += posprav[ind]
                posprav[ind + 1] %= 998244353
    print(ans)


# https://github.com/VaHiX/codeForces/