# Problem: CF 2037 A - Twice
# https://codeforces.com/contest/2037/problem/A

# ================================================================================
# Problem: Maximum Score from Pairing Equal Elements
#
# Algorithm/Techniques:
#   - Frequency counting using set and count()
#   - Greedy approach: For each unique element, we can form pairs equal to floor(count/2)
#
# Time Complexity: O(n^2) per test case
#   - Loop over lines: O(n)
#   - For each line, split and count occurrences: O(n^2)
# Space Complexity: O(n)
#   - Storing the input array and set of unique elements
#
# ================================================================================

for s in [*open(0)][2::2]:  # Read every second line starting from index 2 (skip n and empty lines)
    a = s.split()           # Split the string into list of integers
    print(sum(a.count(x) // 2 for x in {*a}))  # Count pairs for each unique element


# https://github.com/VaHiX/codeForces/