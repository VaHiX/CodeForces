# Problem: CF 2053 A - Tender Carpenter
# https://codeforces.com/contest/2053/problem/A

# Flowerbox:
# Purpose: Determine if an array can be partitioned into at least two different ways such that each subsegment forms a "stable" set of integers.
# Algorithm: 
#   - For a set to be stable, any three elements from it must form a non-degenerate triangle.
#     This occurs iff for any three values a, b, c in the set (sorted), a + b > c.
#   - We check all pairs of consecutive elements to see if the condition holds for adjacent subsegments.
#   - If for each such pair we have 2 * min(a,b) <= max(a,b), then they form valid triangles pairwise.
#   - The main loop checks if the entire array can be split into valid subsegments. 
# Time Complexity: O(n^2) where n is the length of the input array (nested logic in one loop).
# Space Complexity: O(1) — no extra space used beyond input reading and processing.

for s in [*open(0)][2::2]:  # Read lines starting from index 2, step by 2 (skip line numbering)
    a = (*map(int, s.split()),)  # Convert current input line to tuple of integers
    print("YNEOS"[all(2 * min(x) <= max(x) for x in zip(a, a[1:])) :: 2])  # Evaluate condition and output YES or NO


# https://github.com/VaHiX/codeForces/