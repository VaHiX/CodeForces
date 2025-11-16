# Problem: CF 2024 A - Profitable Interest Rate
# https://codeforces.com/contest/2024/problem/A

# ==================================================================
# Problem: Alice wants to maximize coins in "Profitable" deposit
#          by first investing some coins in "Unprofitable" deposit.
#          Each coin invested in "Unprofitable" reduces "Profitable"
#          requirement by 2 coins.
#
# Algorithm: Try all possible investments in "Unprofitable" deposit,
#            compute max coins that can be put in "Profitable".
#
# Time Complexity: O(1) - constant time due to math derivation
# Space Complexity: O(1) - only using constant extra space
# ==================================================================

for s in [*open(0)][1:]:
    j, y = map(int, s.split())  # j = total coins, y = initial min required for Profitable
    print(max(0, j - max(0, y - j)))  # Computes optimal coins for Profitable deposit


# https://github.com/VaHiX/codeForces/