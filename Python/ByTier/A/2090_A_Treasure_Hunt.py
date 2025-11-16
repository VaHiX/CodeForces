# Problem: CF 2090 A - Treasure Hunt
# https://codeforces.com/contest/2090/problem/A

"""
Code Purpose:
This code determines whether Little B or Little K will dig up the treasure first based on their digging speeds and the total depth required.
The algorithm simulates the digging process in a cycle (B, K, B, K, ...) and checks who reaches or exceeds the required depth 'a' during their turn.

Algorithms/Techniques: 
- Mathematical simulation with modular arithmetic to avoid full iteration
- Optimization using cycle detection (every 2 days, the pattern repeats)
- Efficient logic using Python slicing for output

Time Complexity: O(1) - constant time due to mathematical approach and no loop
Space Complexity: O(1) - only a fixed number of variables used
"""

for s in [*open(0)][1:]:  # Read all lines except the first (number of test cases)
    x, y, a = map(int, s.split())  # Parse x (B's digging speed), y (K's digging speed), a (target depth)
    print("YNEOS"[a % (x + y) < x :: 2])  # Efficient check using modular arithmetic and slicing


# https://github.com/VaHiX/CodeForces/