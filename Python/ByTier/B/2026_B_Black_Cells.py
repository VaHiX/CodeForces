# Problem: CF 2026 B - Black Cells
# https://codeforces.com/contest/2026/problem/B

"""
B. Black Cells

Purpose:
This code solves the problem of finding the minimum value of k such that all given cells can be painted black 
by performing operations where two white cells within distance k can be painted black. At most one additional 
cell (not in the list) can also be painted black.

Approach:
- The strategy is to use binary search on k, but due to constraints and structure of problem,
  we precompute possible values by considering gaps between adjacent elements.
- We compute prefix and suffix maximum gaps, then find minimum k that allows covering all required cells
  using at most one extra cell.
  
Time Complexity: O(n^2) per test case, where n<=2000 due to constraints sum not exceeding 2000.
Space Complexity: O(n)

Algorithms/Techniques:
- Sliding window / greedy approach with preprocessing
- Two-pass technique for prefix and suffix maximums
"""

def solve():
    gaps = [1]  # Prepend dummy gap to handle indexing
    m = 1       # Current maximum gap
    for i in range(1, n, 2):              # Iterate over odd indices (from 1)
        m = max(m, a[i] - a[i - 1])       # Update maximum gap between consecutive elements
        gaps.append(m)                    # Store this maximum so far
    
    if n % 2 == 0:                        # If even number of elements
        return m                          # Return the last computed max gap

    m = 1                                 # Reset m for second pass
    ans = int(1e18)                       # Initialize answer to large value
    
    for i in range(n - 1, -1, -2):        # Iterate backwards from last odd index to 0
        ans = min(ans, max(gaps[i // 2], m)) # Minimize over possible k values based on prefix/suffix splits
        m = max(m, a[i] - a[i - 1])       # Update current max gap
    
    return ans


for t in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    print(solve())


# https://github.com/VaHiX/codeForces/