# Problem: CF 1859 C - Another Permutation Problem
# https://codeforces.com/contest/1859/problem/C

"""
Algorithm: Another Permutation Problem
Purpose: Find the maximum cost among all permutations of length n, where cost is defined as:
         (sum of p[i] * i) - (max of p[j] * j)

Approach:
- For a given n, we want to find the permutation that maximizes the cost.
- The key insight is that in order to maximize the cost:
  - We should try to place the largest elements at positions with the highest weights (i.e., larger indices)
  - But we also want to maximize the sum of p[i]*i while minimizing the maximum p[j]*j

Time Complexity: O(n^3) in worst case due to nested loops.
Space Complexity: O(1), only using a few variables for computation.

The code uses a brute-force-like approach over possible permutations by iterating through
various configurations and calculating the corresponding cost, and keeping track of the maximum.

Note: This is a hand-crafted and potentially suboptimal simulation of the problem,
not necessarily following the most efficient approach, but it matches the provided code.
"""
for _ in range(int(input())):
    l = int(input())
    m = 0
    for i in range(l - 1, -1, -1):  # Iterating from n-1 down to 0
        s = 0
        for j in range(1, i):  # Summing up j*j from 1 to i-1
            s += j * j
        c = 0
        for k in range(l - i + 1):  # For a fixed i, iterate k from 0 to l-i
            k = (l - k) * (i + k)  # Compute value for current k
            if k > c:  # Track the maximum of these values
                c = k
            s += k  # Add it to the sum
        s = s - c  # Final cost calculation
        if s > m:  # Update maximum cost found so far
            m = s
        else:
            break  # Early termination condition
    print(m)


# https://github.com/VaHiX/CodeForces/