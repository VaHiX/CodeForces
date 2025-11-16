# Problem: CF 1943 D1 - Counting Is Fun (Easy Version)
# https://codeforces.com/contest/1943/problem/D1

"""
Algorithm: Dynamic Programming with Prefix Sums
Techniques: 
- Rolling DP with prefix sums optimization
- Modular arithmetic to handle large numbers
Time Complexity: O(n * k)
Space Complexity: O(k)

This solution uses dynamic programming to count the number of "good" arrays of length n,
where each element is in [0, k], and the array can be reduced to all zeros using the 
allowed operation (subtract 1 from a contiguous subarray). The recurrence is optimized 
using prefix sums to avoid recalculating totals repeatedly.
"""

for _ in range(int(input())):
    n, k, p = map(int, input().split())
    # Initialize mll and ml arrays to store DP states
    mll = [1] * (k + 1)
    ml = list(range(1, k + 2))
    
    # Iterate over the remaining positions in the array (n-1 steps)
    for i in range(n - 1):
        mas = [0] * (k + 1)
        sm1 = sum(ml)  # Total sum of current state
        sm2 = 0        # Running sum from right to left
        sm3 = 0        # Cumulative sum for updates
        
        # Process from right to left to compute new state
        for j in range(k, -1, -1):
            # Compute contribution of current subarray ending at position j
            mas[j] = (sm1 - sm2) % p
            # Update sm3 and sm2 for next iteration
            sm3 += mll[k - j]
            sm2 += sm3
            
        # Move to next step
        mll = ml.copy()
        ml = mas.copy()
        
    # The answer is the first element of final state
    print(ml[0])


# https://github.com/VaHiX/CodeForces/