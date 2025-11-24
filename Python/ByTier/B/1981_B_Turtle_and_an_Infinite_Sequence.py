# Problem: CF 1981 B - Turtle and an Infinite Sequence
# https://codeforces.com/contest/1981/problem/B

"""
Code Purpose:
This solution computes the value of a_n after m seconds in a modified sequence where each element is updated based on bitwise OR of its neighbors. 
The key insight is that after sufficient iterations, the sequence stabilizes into a pattern where values are determined by a mask derived from the number of steps.

Algorithms/Techniques:
- Bit manipulation and simulation optimization
- Observation of sequence behavior and stabilization patterns
- Efficient mask construction using bit operations

Time Complexity: O(log(max(n, m))) - due to the while loop that processes bits
Space Complexity: O(1) - only using a few variables for computation
"""

for s in [*open(0)][1:]:
    n, m = map(int, s.split())
    k = 0
    # Construct a mask k such that (n + m) & k < m + min(n, m)
    # This determines how many bits we need to consider for the final OR operation
    while (n + m) & k < m + min(n, m):
        k = k * 2 + 1  # Build a bitmask of all 1s (e.g., 1, 11, 111, ...)
    print(n | k)  # Apply the bitwise OR with the constructed mask


# https://github.com/VaHiX/CodeForces/