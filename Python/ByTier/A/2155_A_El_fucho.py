# Problem: CF 2155 A - El fucho
# https://codeforces.com/contest/2155/problem/A

# ==============================================================================
# Problem: Double-Elimination Tournament Matches
# Purpose: Calculate total number of matches in a double-elimination tournament
# Algorithm/Techniques: Mathematical reasoning, simulation pattern recognition
#
# Time Complexity: O(1) - constant time per test case
# Space Complexity: O(1) - only using a few variables regardless of input size
# ==============================================================================

for _ in range(int(input())):  # Read number of test cases and loop through them
    n = int(input())           # Read the number of teams for current test case
    print(2 * n - 2)           # Output the total number of matches (formula derived from pattern)


# https://github.com/VaHiX/CodeForces/