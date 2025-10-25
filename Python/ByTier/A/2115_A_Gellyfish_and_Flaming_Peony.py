# Problem: CF 2115 A - Gellyfish and Flaming Peony
# https://codeforces.com/contest/2115/problem/A

"""
Problem: Gellyfish and Flaming Peony

Purpose:
This code solves the problem of finding the minimum number of operations to make all elements of an array equal,
where each operation involves replacing one element with the GCD of itself and another element in the array.

Algorithms/Techniques:
- Greedy approach with GCD properties
- Dynamic programming-like set construction to simulate possible GCD values
- Preprocessing: Compute total GCD of all numbers to understand target final value

Time Complexity: O(n^3) in worst case due to nested loops and set operations, but optimized with early stopping.
Space Complexity: O(n^2) for the sets stored in dp list in worst case scenario.

Input Format:
- t test cases
- For each test case:
  - n (length of array)
  - Array of n integers

Output Format:
- Minimum number of operations to make all elements equal
"""

testcasenumber = int(input())
import math

for counter in range(testcasenumber):
    n = input()
    seg = list(map(int, input().split()))
    u = seg[0]
    dp = [set()]
    dp[-1].add(seg[0])
    for i in range(1, len(seg)):
        u = math.gcd(u, seg[i])  # Compute overall GCD of all elements
        dp[-1].add(seg[i])
    
    # Continue building sets of GCDs until we find the global GCD (u)
    while u not in dp[-1]:
        dp.append(set())
        for j in dp[0]:  # Take first set (originally from input array)
            for k in dp[len(dp) - 2]:  # Take previous set
                p = math.gcd(j, k)  # Compute new GCD
                if len(dp) == 1 or p not in dp[-2]:  # Avoid duplicates
                    dp[-1].add(p)
                if p == u:  # Early termination if we already have the target
                    break
    
    # If global gcd is already present in initial set, count how many elements are not equal to it
    if u in dp[0]:
        print(len(seg) - seg.count(u))
    else:
        # Otherwise, return number of steps (sets processed) plus operations needed to reduce array to one element
        print(len(dp) + len(seg) - 2)


# https://github.com/VaHiX/codeForces/