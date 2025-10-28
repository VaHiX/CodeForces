# Problem: CF 1373 B - 01 Game
# https://codeforces.com/contest/1373/problem/B

# B. 01 Game
# Time complexity: O(n) where n is the length of the string
# Space complexity: O(1)
# Algorithm:
#   - The game is about removing adjacent different characters (01 or 10).
#   - Each move reduces the string by 2 characters.
#   - If total number of such pairs is odd, Alice wins; if even, Bob wins.
#   - The key insight is to count minimum of '0' and '1', because each pair removes one of each.
#   - The result depends on whether this minimum count is even or odd.

for s in [*open(0)][1:]:  # Read all lines except first (which is test case count)
    print("NDEAT"[min(s.count("0"), s.count("1")) % 2 :: 2])  # Determine winner based on parity of min count


# https://github.com/VaHiX/codeForces/