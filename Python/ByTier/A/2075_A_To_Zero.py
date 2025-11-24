# Problem: CF 2075 A - To Zero
# https://codeforces.com/contest/2075/problem/A

# ==============================================================================
# Problem: Minimum Operations to Reduce n to 0
# ==============================================================================
# Algorithm/Technique:
#   Greedy approach with mathematical observation:
#   - If n is divisible by k, answer is n // k.
#   - Otherwise, we need one extra operation due to parity constraints.
#   - Since k is odd, the optimal strategy minimizes operations using
#     largest valid x values based on current parity of n.
#
# Time Complexity: O(1) per test case
# Space Complexity: O(1)
# ==============================================================================

for s in [*open(0)][1:]:  # Read all lines except first (number of test cases)
    n, k = map(int, s.split())  # Parse n and k from current line
    print(1 - (k - n) // ~-k)  # Compute minimum operations using formula


# https://github.com/VaHiX/codeForces/