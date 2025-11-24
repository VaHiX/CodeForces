# Problem: CF 1835 A - k-th equality
# https://codeforces.com/contest/1835/problem/A

"""
Purpose: Find the k-th lexicographically smallest equality of the form a + b = c,
         where a has A digits, b has B digits, and c has C digits.
         All numbers must be positive integers with no leading zeroes.

Algorithms/Techniques:
- Brute-force enumeration with early termination
- For each possible value of 'a' (from min to max A-digit number), calculate valid range of 'b'
- Count valid (a,b) pairs that yield valid c (C-digit number)
- Use this count to determine which a and b contribute to the k-th solution

Time Complexity: O(10^(A+B)) in worst case, but optimized with early termination
Space Complexity: O(1) - only using a few variables

Note: The function is optimized for small inputs (A,B,C <= 6), and uses the fact that
the number of valid combinations can be computed upfront to skip unnecessary iterations.
"""

import sys

input = sys.stdin.readline


def solve():
    A, B, C, k = map(int, input().split())
    # Calculate min and max values for each digit count
    al = 10 ** (A - 1)   # Min A-digit number
    ah = 10**A - 1       # Max A-digit number
    bl = 10 ** (B - 1)   # Min B-digit number
    bh = 10**B - 1       # Max B-digit number
    cl = 10 ** (C - 1)   # Min C-digit number
    ch = 10**C - 1       # Max C-digit number
    
    # Early check: if the smallest possible c is greater than the largest possible a+b or vice versa
    if ch < al + bl or cl > ah + bh:
        return -1
    
    # Iterate through all possible values of 'a' in the range [al, ah]
    for a in range(al, ah + 1):
        # For current 'a', find valid range of 'b'
        low = max(cl - a, bl)    # Minimum valid 'b' so that c = a + b is at least cl
        high = min(ch - a, bh)   # Maximum valid 'b' so that c = a + b is at most ch
        x = max(0, high - low + 1)  # Count of valid b values for this a
        
        # If k is larger than x, skip this a and reduce k
        if k - x > 0:
            k -= x
        else:
            # Found the exact a and b for the k-th equality
            b = low + k - 1
            return f"{a} + {b} = {a + b}"
    
    return -1


T = int(input())
out = [solve() for _ in range(T)]
print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/