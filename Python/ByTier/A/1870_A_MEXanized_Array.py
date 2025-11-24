# Problem: CF 1870 A - MEXanized Array
# https://codeforces.com/contest/1870/problem/A

"""
Problem: MEXanized Array
Purpose: Given n, k, x, find the maximum possible sum of an array of n non-negative integers,
         with MEX = k and all elements <= x. Return -1 if impossible.

Algorithms/Techniques: 
- Greedy approach to maximize sum
- Mathematical formula for sum of first k-1 natural numbers
- Check feasibility based on constraints

Time Complexity: O(1) per test case - constant time operations
Space Complexity: O(1) - only using a fixed-size list for results

Approach:
1. Check if array can be formed based on n and k
2. Compute sum of elements from 0 to k-2 (which contributes to MEX being k)
3. Fill remaining positions with x (max possible value)
"""

R = []
for i in range(int(input())):
    n, k, x = map(int, input().split())
    # If n < k, we can't have k distinct elements (0 to k-1), so impossible
    # If k-1 > x, then we can't include k-1 in the array, also impossible
    if n < k or k - 1 > x:
        R.append(-1)
        continue
    else:
        # Sum of elements 0 to k-2 using arithmetic progression formula
        p = k - 1
        # If k equals x, we cannot use x in the array (since MEX is k)
        # So we adjust x to k-1 to satisfy constraint
        if k == x:
            x = k - 1
        # Sum of first k-1 integers + (n-k) copies of x
        R.append(int((p * (p + 1)) / 2 + ((n - k) * x)))
for i in R:
    print(i)


# https://github.com/VaHiX/CodeForces/