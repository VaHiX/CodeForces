# Problem: CF 2109 A - It's Time To Duel
# https://codeforces.com/contest/2109/problem/A

# ==============================================================================
# Problem: A. It's Time To Duel
# Purpose: Determine if at least one player is lying about their duel results.
# Algorithm/Techniques:
#   - Simulation-based validation of duel outcomes
#   - Check consistency: in any sequence of duels, each player's win count must align with reality
#   - Key observation: if a player reports 0 wins but is involved in a duel (i.e., not at the ends), they're lying.
#   - For sequences where multiple players report 1 win, it's impossible for all to be true unless there's a valid chain.
#
# Time Complexity: O(n) per test case due to linear scan of the array.
# Space Complexity: O(1) as only a constant amount of extra space is used.
# ==============================================================================

for s in [*open(0)][2::2]:  # Read lines from input, skip first two and take every second line (the reports)
    print("YNEOS"[("0" in s) > ("0 0" in s) :: 2])  # Check conditions to determine if there's a lie:
        # "0" in s : True if any player reported 0 wins
        # "0 0" in s : True if two consecutive players both reported 0 wins
        # If (0 in s) > (0 0 in s), then a contradiction exists, so print YES/NO accordingly via slicing


# https://github.com/VaHiX/codeForces/