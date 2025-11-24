# Problem: CF 2125 E - Sets of Complementary Sums
# https://codeforces.com/contest/2125/problem/E

"""
E. Sets of Complementary Sums

Problem Description:
Given n and x, count the number of distinct sets of complementary sums such that:
- The set contains exactly n elements.
- Each element is an integer from 1 to x.

A set Q is a set of complementary sums if it can be derived by taking an array a of m positive integers,
computing s = sum(a), and adding (s - a_i) for each i to the set. This implies that:
- If we take any element from the set, its complement with respect to s is also in the set.
- The number of elements in such a set can be odd or even.

Key Insight:
- For n = 1, there are exactly x valid sets (each single element set {i} for i in [1,x]).
- For larger n, we must enumerate over possible sums s and generate the valid subsets.
- Each set corresponds to a subset of integers from 1 to x with specific properties.

Algorithms Used:
- Dynamic Programming (DP) - used to compute how many combinations sum up to certain values.
- Modular arithmetic - for handling large numbers and maintaining modulo 998244353.

Time Complexity: O(n * x)
Space Complexity: O(x)

"""

import sys

le = sys.__stdin__.read().split("\n")[::-1]  # Read all input lines in reverse
af = []                                      # Result list to store answers
mo = 998244353                                # Modulo value for large numbers

for _ in range(int(le.pop())):               # Process each test case
    n, x = map(int, le.pop().split())        # Read n and x
    
    if n == 1:                               # Special case: only one element
        af.append(x)                         # Any single element from 1 to x forms a valid set
        continue
    
    dp = [0] * (x + 2)                       # DP array initialized to zero, size is x+2 for safety
    t = (n * (n + 1)) // 2                   # Compute total sum of first n integers
    if t > x + 1:                            # If the minimal sum exceeds x+1, no valid set exists
        af.append(0)
        continue
    
    dp[t] = 1                                # Initialize base case for DP
    
    # Dynamic programming step to count ways to form sums
    for v in range(1, n):                    # For each element from 1 to n-1
        for k in range(t + v, x + 2):        # Update dp values forward
            dp[k] = (dp[k] + dp[k - v]) % mo # Accumulate combinations

    # Sum the weighted combinations to get final result
    af.append(sum((x + 2 - i) * v for i, v in enumerate(dp)) % mo)
    
print("\n".join(map(str, af)))


# https://github.com/VaHiX/codeForces/