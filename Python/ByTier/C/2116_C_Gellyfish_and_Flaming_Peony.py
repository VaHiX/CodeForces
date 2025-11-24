# Problem: CF 2116 C - Gellyfish and Flaming Peony
# https://codeforces.com/contest/2116/problem/C

"""
C. Gellyfish and Flaming Peony

Purpose:
This code solves the problem of finding the minimum number of operations needed to make all elements in an array equal by repeatedly replacing one element with the GCD of two elements.

Algorithm:
1. First, compute the overall GCD of all elements.
2. If any element already equals this GCD, we only need to convert the rest of the elements (n - count of GCD elements).
3. Otherwise, we build a BFS-based graph where nodes are unique values in the array and edges represent possible GCD operations.
4. The minimum number of operations is determined by the shortest path from any element to the overall GCD in this graph, plus the size of the array minus one.

Time Complexity:
O(n^2 * log(max_val) + max_val), where n is the size of the array and max_val is the maximum value in the array. This accounts for building the BFS graph and traversing it.

Space Complexity:
O(max_val), for storing the DP table (used in BFS) and deque storage.
"""

from collections import deque
from math import gcd

for _ in range(int(input())):
    n = int(input())
    arr = [*map(int, input().split())]
    g = gcd(*arr)
    x = arr.count(g)
    if x > 0:
        print(n - x)
        continue
    
    # Convert array to set of unique values
    new = [*map(int, set(map(str, arr)))]
    
    # Initialize dp array to track minimum steps from each number to GCD
    dp = [-1] * (max(arr) + 1)
    
    # Mark all unique numbers as reachable with 0 steps initially
    for i in new:
        dp[i] = 0
    
    # BFS queue initialized with unique values
    q = deque(new)
    
    # BFS to find the minimum operations needed to reach GCD
    while q:
        cur = q.popleft()  # Current number being processed
        
        # Try all other numbers to compute new GCDs
        for i in new:
            if cur != i:
                x = gcd(cur, i)  # Compute GCD
                
                # If this GCD hasn't been seen before, mark it with step count + 1
                if dp[x] == -1:
                    dp[x] = dp[cur] + 1
                    q.append(x)
                
                # Early termination if we reach the overall GCD
                if x == g:
                    break
                    
    # Final result: total elements minus step count to reach GCD plus one
    print(n + dp[g] - 1)


# https://github.com/VaHiX/codeForces/