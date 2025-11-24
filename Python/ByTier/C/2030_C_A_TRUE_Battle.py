# Problem: CF 2030 C - A TRUE Battle
# https://codeforces.com/contest/2030/problem/C

# Flowerbox:
# Problem: Determine if Alice wins a game on a boolean string where players alternate placing 'and' or 'or' 
#          operators between booleans, with Alice going first. Alice wants true, Bob wants false.
# Algorithm: Game theory / Optimal play simulation using pattern matching.
#            The key insight is that the outcome depends on whether we can make a "1" in the string
#            after applying AND/OR operations optimally (Alice tries to make it true).
# Time Complexity: O(n), where n is the length of the string, due to single pass scan and pattern matching.
# Space Complexity: O(1), constant extra space, only using fixed-size variables.

for s in [*open(0)][2::2]:  # Read test case strings from input, skipping first two lines (t, n)
    # Check if "11" appears in the modified string with '1' prepended and appended.
    # This tells us if there's an opportunity for Alice to force a win via AND operator placement.
    print("NYOE S"[  # Output based on position in string
        "11" in "1" + s[:-1] + "1"  # If pattern is found, this expression evaluates to True (1)
        :: 2  # Pick every second character starting from index 0: "NYOE S" -> "NO", i.e. True -> False
    ])


# https://github.com/VaHiX/codeForces/