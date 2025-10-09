# Problem: CF 2104 A - Three Decks
# https://codeforces.com/contest/2104/problem/A

# Problem: Determine if it's possible to make all three decks of cards equal by moving cards from the third deck
# Algorithm: Mathematical analysis of the total card count and distribution constraints
# Time Complexity: O(1) per test case - constant time operations
# Space Complexity: O(1) - only using a fixed amount of extra space

for s in [*open(0)][1:]:  # Read all input lines, skip first line
    a, b, c = map(int, s.split())  # Parse the three deck sizes
    c += a + b  # Add total cards from first two decks to third deck count
    print("YNEOS"[0 < c % 3 or b * 3 > c :: 2])  # Output result based on condition


# https://github.com/VaHiX/codeForces/