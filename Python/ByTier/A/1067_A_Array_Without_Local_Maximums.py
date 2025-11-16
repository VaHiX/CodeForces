# Problem: CF 1067 A - Array Without Local Maximums 
# https://codeforces.com/contest/1067/problem/A

"""
Problem: Array Without Local Maximums

This problem involves counting the number of ways to fill in -1 values in an array such that 
the resulting array satisfies the condition that every element (except first and last) is 
less than or equal to the maximum of its neighbors. The array elements are constrained to [1, 200].

Approach:
Dynamic Programming with states tracking valid configurations for each position based on
the previous element's value.

Time Complexity: O(n * 200) = O(n)
Space Complexity: O(200) = O(1)

Algorithms/Techniques:
- Dynamic Programming
- State tracking based on previous values
"""

import sys

input = sys.stdin.readline
n = int(input())
nums = [int(x) for x in input().split()]
mod = 998244353
dp0 = [0] * 201  # dp0[j]: number of ways to reach position i with value j, where current is not a local max
dp1 = [0] * 201  # dp1[j]: number of ways to reach position i with value j, where current is a local max
if nums[0] == -1:
    dp0 = [1] * 201  # Initially all values are possible as we don't know the first element yet
    dp0[0] = 0  # Value 0 is not valid
else:
    dp0[nums[0]] = 1  # If first value is known, set it as the base case

ans = 0  # Total number of ways to fill the whole array

for i in range(1, n):
    a = b = nex = 0  # a tracks prefix sum of dp0, b tracks prefix sum of dp1, nex tracks new total
    dp01 = [0] * 201  # New dp0 array for current position
    dp11 = [0] * 201  # New dp1 array for current position
    for j in range(1, 201):  # For each possible value from 1 to 200
        if nums[i] == -1 or nums[i] == j:  # If current cell is unknown or matches target value
            # Update dp01[j]: ways where this element is NOT a local maximum
            dp01[j] = (a + b) % mod
            
            # Update dp11[j]: ways where this element IS a local maximum  
            dp11[j] = (dp0[j] + ans - b + mod) % mod

            # Update total number of valid sequences ending with this value
            nex = (nex + dp11[j]) % mod
            
        # Maintain running prefix sums for efficiency
        a = (a + dp0[j]) % mod
        b = (b + dp1[j]) % mod
        
    dp0 = dp01  # Update dp0 to current state
    dp1 = dp11  # Update dp1 to current state
    ans = nex   # Update global answer

print(ans)


# https://github.com/VaHiX/codeForces/