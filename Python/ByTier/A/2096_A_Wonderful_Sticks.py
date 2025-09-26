# Problem: CF 2096 A - Wonderful Sticks
# https://codeforces.com/contest/2096/problem/A

# ==============================================================================
# Problem: Wonderful Sticks
# Algorithm/Technique: Greedy approach with two pointers
# Time Complexity: O(n) per test case
# Space Complexity: O(n) for output storage
# ==============================================================================

for *s, _ in [*open(0)][2::2]:  # Read input lines in pairs: n and s
    m = M = s.count("<") + 1  # Initialize two counters: m starts at count of "<" + 1, M is same value
    print(m, *(x < ">" and (m := m - 1) or (M := M + 1) for x in s))  # Print the arrangement using greedy assignment

# Explanation:
# The algorithm works by greedily assigning values:
# - When we see "<", we assign the smallest available value (decrementing 'm')
# - When we see ">", we assign the largest available value (incrementing 'M')
# This greedy method ensures that all conditions in the string are satisfied.


# https://github.com/VaHiX/codeForces/