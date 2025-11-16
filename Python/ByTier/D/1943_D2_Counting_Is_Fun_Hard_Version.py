# Problem: CF 1943 D2 - Counting Is Fun (Hard Version)
# https://codeforces.com/contest/1943/problem/D2

"""
Algorithm: Dynamic Programming with Prefix Sums
Approach:
- This problem asks to count the number of "good" arrays of length n, where each element is between 0 and k.
- An array is good if all elements can be reduced to 0 using a specific operation:
  - Select two indices l < r and subtract 1 from all elements between l and r (inclusive).
- The key insight is to think of how many operations are needed at each position.
- We can treat this as a dynamic programming problem where we track how many ways we can form arrays of length i such that the prefix sums follow certain constraints.

Time Complexity: O(n * k^2)
Space Complexity: O(k)

The algorithm uses dynamic programming with optimized prefix sum calculations to avoid recalculating sums each time.
"""

for _ in range(int(input())):
    n, k, p = map(int, input().split())
    # Initialize arrays for dynamic programming
    mll = [1] * (k + 1)  # previous state
    ml = list(range(1, k + 2))  # current state
    
    # Iterate from 2 to n (since base case is already handled)
    for i in range(n - 1):
        mas = [0] * (k + 1)  # new state
        sm1 = sum(ml)  # total sum of current state
        sm2 = 0
        sm3 = 0
        
        # Compute each position in the new state based on previous sums
        for j in range(k, -1, -1):
            # mas[j] = (sum of ml from index 0 to j) % p
            mas[j] = (sm1 - sm2) % p
            # Update prefix sum for next iteration
            sm3 += mll[k - j]
            sm2 += sm3
            
        # Update states for next iteration
        mll = ml.copy()
        ml = mas.copy()
        
    # Print the result for the full array
    print(ml[0])


# https://github.com/VaHiX/CodeForces/