# Problem: CF 1738 E - Balance Addicts
# https://codeforces.com/contest/1738/problem/E

"""
Algorithm: Dynamic Programming with Combinatorics
Time Complexity: O(n) for each test case
Space Complexity: O(n) for precomputing factorials

The problem asks to count the number of ways to partition a sequence into continuous subsequences such that the sums of these subsequences form a balanced sequence.

The key insight is that we can use two pointers to find the "balanced" parts of the sequence, where the sum on the left matches the sum on the right, and then use combinatorics to count valid partitions.

For a balanced sequence:
1. We use two pointers (left, right) to traverse from both sides
2. We maintain running sums (l, r) of the left and right parts
3. When l == r, we have found a potential center point
4. We collect the number of zeros before and after the center point
5. Finally, compute combinations based on the structure of the balanced sequence

This approach is effective because:
- For each balanced segment, we can choose where to place the partition points
- Zeros can be freely placed without affecting the balance
- We use combinatorics to count valid placements
"""

import sys


def input():
    return sys.stdin.readline()[:-1]


mod = 998244353

# Precompute factorials for combination calculations
fact = [0] * (10**5 + 5)

fact[0] = 1
f = 1
for i in range(1, 10**5 + 5):
    fact[i] = (fact[i - 1] * i) % mod


# Function to compute combinations C(N, M) mod 998244353
def comb(N, M):
    ret = (fact[N] * pow(fact[M], mod - 2, mod)) % mod
    ret *= pow(fact[N - M], mod - 2, mod)
    ret %= mod
    return ret


def solve():
    N = int(input())
    A = list(map(int, input().split()))
    left = 0
    right = N - 1
    eq = []
    l = 0
    r = 0
    el = 0
    er = 0
    while right >= left:
        if l == r:
            # If sums are equal, check if current element is zero
            if A[left] == 0:
                el += 1
                left += 1
            elif A[right] == 0:
                er += 1
                right -= 1
            else:
                # Add the segment of zeros around the center
                eq.append((el, er))
                el = 0
                er = 0
                l += A[left]
                left += 1
        else:
            # Adjust the sums by moving either left or right pointer
            if l < r:
                l += A[left]
                left += 1
            else:
                r += A[right]
                right -= 1
    last_flag = False
    if l == r:
        eq.append((el, er))
        if el > 0 or er > 0:
            last_flag = True
    ans = 1
    if len(eq) == 1:
        # If there is only one balanced section
        if last_flag:
            ans = pow(2, N - 1, mod)
        else:
            el, er = eq[0]
            ans *= comb(el + er, el)
    else:
        # Calculate result for multiple balanced sections
        for i in range(len(eq)):
            if i == 0:
                el, er = eq[i]
                ans *= comb(el + er, el)
            elif i == len(eq) - 1 and last_flag:
                el, er = eq[i]
                ans *= pow(2, el + er + 1, mod)
            else:
                el, er = eq[i]
                ans *= comb(el + er + 2, el + 1)
            ans %= mod
    print(ans)


T = int(input())

for i in range(T):
    solve()

"""
def X(n,m):
    ans = 0
    for i in range(min(n+1,m+1)):
        ans += comb(n,i)*comb(m,i)
    return ans

for i in range(1,5):
    for j in range(1,5):
        print(i,j,X(i,j))
"""


# https://github.com/VaHiX/CodeForces/