# Problem: CF 2154 F2 - Bombing (Hard Version)
# https://codeforces.com/contest/2154/problem/F2

"""
Algorithm: Dynamic Programming with Combinatorics
Time Complexity: O(n^2) per test case, where n <= 10^6
Space Complexity: O(n^2) due to storing intermediate states and combinatorial arrays

This solution computes the number of ways to fill -1s in the permutation such that 
it forms a riffle shuffle of [1,2,...,n]. It uses dynamic programming and combinatorics:
- Precomputed factorials and inverse factorials for binomial coefficients
- State tracking for valid riffle shuffle conditions
- Modular arithmetic for large numbers
"""

import sys

input = sys.stdin.readline
MOD = 998244353

# Precompute factorials and inverse factorials up to 2 * 10^6
fac_arr = [1]
finv_arr = [1]


def enlarge_fac():
    # Extend factorial arrays when needed
    old_size = len(fac_arr)
    new_size = old_size * 2
    for i in range(old_size, new_size + 1):
        fac_arr.append((fac_arr[-1] * i) % MOD)
    # Compute inverse factorials
    ifac = [pow(fac_arr[-1], -1, MOD)]
    for i in range(new_size, old_size, -1):
        ifac.append((ifac[-1] * i) % MOD)
    ifac.reverse()
    for x in ifac:
        finv_arr.append(x)


def fac(n):
    # Return n! mod MOD
    while n >= len(fac_arr):
        enlarge_fac()
    return fac_arr[n]


def finv(n):
    # Return (n!)^(-1) mod MOD
    while n >= len(finv_arr):
        enlarge_fac()
    return finv_arr[n]


def binom(n, k):
    # Return C(n, k) mod MOD
    if k < 0 or k > n:
        return 0
    return ((fac(n) * finv(k)) % MOD * finv(n - k)) % MOD


for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split())) + [n + 1]  # Add sentinel element
    
    # Check if all positions are filled (no -1s)
    if max([0 if a[i] == -1 else abs(a[i] - i - 1) for i in range(n)]) == 0:
        # Special handling for cases where no -1s exist 
        sol = 1
        last = 0
        for i in a:
            if i >= 0:
                sol += pow(2, i - last - 1, MOD) - 1 - (i - last - 1)
                last = i
                sol %= MOD
        print(sol)
    else:
        # Initialize state tracking for riffle conditions
        S = [(0, i, 1) for i in range(1, n)]  # (left_size, right_size, count)
        last = -1
        left = 1  # Tracks which side current element belongs to
        eq = 0  # Equal condition flag
        pl = 0  # Position offset
        mult = 1  # Multiplier for combinations
        lastv = 0  # Last assigned value
        nd = 0  # New value tracking
        
        for idx in range(n + 1):
            if a[idx] == -1:
                # Skip unfilled positions
                continue
            gap = idx - last - 1  # Gap between previous and current position
            
            # Determine whether to switch sides or not
            at = 0
            if idx + 1 > a[idx] or (idx + 1 == a[idx] and eq == 0):
                if idx + 1 > a[idx]:
                    eq = 1
                at = 1
            else:
                eq = 1
                
            TMP = []
            if at ^ left:
                # Process transitions between left and right halves
                for i, j, k in S:
                    if left:
                        j += pl  # Adjust right half
                        i = nd    # Set left half
                    else:
                        i += pl  # Adjust left half
                        j = nd    # Set right half
                    if left:
                        rev = a[idx] - j - 1  # Reversal count from right
                    else:
                        rev = a[idx] - i - 1  # Reversal count from left
                    if left:
                        i += gap - rev  # Update left side accordingly
                    else:
                        j += gap - rev  # Update right side accordingly
                    if at:
                        i = a[idx]    # Set i if at=1
                    else:
                        j = a[idx]    # Set j if at=0
                    f = binom(gap, rev)  # Binomial coefficient for combinations
                    if f:
                        TMP.append((i, j, (k * f) % MOD))  # Update state
                left ^= 1  # Flip side flag
                pl = 0      # Reset offset
                lastv = a[idx]  # Update last value
                nd = a[idx]     # Update new value
                S = TMP  # Update state list
            else:
                # Same side processing
                rev = a[idx] - lastv - 1  # Calculate reversal count
                pl += gap - rev  # Adjust offset
                nd = a[idx]       # Update new value
                lastv = a[idx]    # Update last value
                mult *= binom(gap, rev)  # Multiply with binomial coefficient
                mult %= MOD  # Keep mod
            last = idx  # Update last processed index
            
        # Calculate final answer: sum of all valid states times multiplier
        print(((sum([x[-1] for x in S]) % MOD) * mult) % MOD)


# https://github.com/VaHiX/CodeForces/