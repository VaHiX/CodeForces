# Problem: CF 2031 A - Penchick and Modern Monument
# https://codeforces.com/contest/2031/problem/A

# ======================================================================
# Problem: Make Pillar Heights Non-Decreasing with Minimum Operations
# Algorithm/Technique: Greedy approach with array processing
# Time Complexity: O(n^2) where n is the number of pillars
# Space Complexity: O(n) for storing the pillar heights
# ======================================================================

for s in [*open(0)][2::2]:  # Read every second line starting from index 2 (skip test case count and empty lines)
    print(len(a := s.split()) - max(map(a.count, a)))  # Count unique elements and subtract from total to find min ops


# https://github.com/VaHiX/codeForces/