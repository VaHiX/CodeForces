# Problem: CF 1613 D - MEX Sequences
# https://codeforces.com/contest/1613/problem/D

"""
Code Purpose:
This solution counts the number of non-empty MEX-correct subsequences in a given array.
A sequence is MEX-correct if at each step, the absolute difference between the current element and the MEX of all previous elements is at most 1.

Algorithms/Techniques:
- Dynamic Programming (DP) with two states:
    - dp1[i]: Number of ways to form a subsequence ending with a value that makes MEX = i
    - dp2[i]: Number of ways to form a subsequence that can extend to a subsequence where MEX = i
- For each element in the array, update DP arrays based on transitions that maintain the MEX-correct property.
- The final answer is sum of all valid subsequences, adjusted for overcounting.

Time Complexity: O(n), where n is the length of the input array.
Space Complexity: O(n), for storing the DP arrays.

"""

mod = 998244353
for _ in range(int(input())):
    n = int(input())
    # dp1[i] represents number of subsequences ending at some index with MEX = i
    # dp2[i] represents number of subsequences that can potentially be extended to have MEX = i
    dp1, dp2 = [0] * (n + 2), [0] * (n + 2)
    dp1[0] = 1  # Base case: one empty subsequence with MEX = 0
    
    lit = list(map(int, input().split()))
    
    for i in lit:
        # Add current element to dp1[i+1] by extending subsequences ending at i or i+1
        dp1[i + 1] += dp1[i + 1] + dp1[i]
        
        # If i > 0, we can also extend subsequences ending at i-1
        if i > 0:
            dp2[i - 1] += dp2[i - 1] + dp1[i - 1]
        
        # Update dp2 for i+1
        dp2[i + 1] += dp2[i + 1]
        
        # Apply modulo to keep values within bounds
        dp1[i + 1] %= mod
        dp2[i + 1] %= mod
        dp2[i - 1] %= mod
    
    # Compute total valid subsequences
    v = 0
    x = 0
    for i in dp1:
        v += i
        v %= mod
    for i in dp2:
        x += i
        x %= mod
    
    # Output final result modulo 998244353
    print(((v + x - 1) + mod) % mod)


# https://github.com/VaHiX/CodeForces/