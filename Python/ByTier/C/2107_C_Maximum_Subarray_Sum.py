# Problem: CF 2107 C - Maximum Subarray Sum
# https://codeforces.com/contest/2107/problem/C

"""
C. Maximum Subarray Sum

Purpose:
This code solves a problem where we are given a partially filled array with some elements marked as "missing" (represented by '0' in string s) and others as "known" (represented by '1'). The goal is to fill the missing positions such that the maximum subarray sum of the resulting array is exactly k.

Techniques:
- Kadane's algorithm variant for calculating maximum subarray sum.
- Prefix sums calculation.
- Linear scan through the array with conditional logic to determine valid values for unknown elements.

Time Complexity: O(n)
Space Complexity: O(n)

"""

import sys

input = lambda: sys.stdin.readline()[:-1]


def II(base=10):
    return int(input(), base)


def LI():
    return list(map(int, input()))


def LII():
    return list(map(int, input().split()))


def main():
    n, k = LII()
    s = input()
    A = LII()
    B = [i for i in range(n) if s[i] == "0"]  # Positions that are missing (marked with '0')
    ma, w = 0, 0
    P = [0] * (n + 1)
    for i, a in enumerate(A):
        # If s[i] == "0", we can modify the value; else we use it directly.
        w = 0 if s[i] == "0" else max(w, 0) + a  # Kadane's algorithm update
        ma = max(ma, w)
        P[i + 1] = P[i] + a  # Prefix sum calculation
    
    # If no positions are missing, check if max subarray is exactly k
    if not B:
        return A if ma == k else []
    
    # If even with best possible setting, the max subarray exceeds k, then impossible
    if ma > k:
        return []

    # Find the first missing position and second one to adjust
    i = B[0]
    j = B[1] if len(B) > 1 else n
    
    # Calculate prefix values for adjustment
    a = min(P[:i + 1])  # Min prefix before first missing element
    b = max(P[i + 1:j + 1])  # Max prefix between missing intervals

    # Adjust the first missing value to ensure max subarray sum is exactly k
    A[i] = k - b + a
    
    # For subsequent missing positions, set them to negative k (to prevent increasing max)
    for i in B[1:]:
        A[i] = -k
            
    return A


for _ in range(II()):
    A = main()
    if A:
        print("Yes")
        print(*A)
    else:
        print("No")


# https://github.com/VaHiX/codeForces/