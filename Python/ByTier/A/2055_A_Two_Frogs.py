# Problem: CF 2055 A - Two Frogs
# https://codeforces.com/contest/2055/problem/A

# ==============================================================================
# Problem: Two Frogs
# Purpose: Determine if Alice can guarantee a win in a turn-based game on lilypads.
# Algorithm/Technique: Mathematical analysis based on parity and distance.
#
# Time Complexity: O(1) per test case
# Space Complexity: O(1)
# ==============================================================================

for s in [*open(0)][1:]:  # Read all input lines except first (number of test cases)
    n, a, b = map(int, s.split())  # Parse n (lilypads), a (Alice's pos), b (Bob's pos)
    print("YNEOS"[b - a & 1 :: 2])  # Check if difference is odd; if so, Alice wins ("YES"), else "NO"


# https://github.com/VaHiX/codeForces/