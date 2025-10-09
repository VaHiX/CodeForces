# Problem: CF 2043 A - Coin Transformation
# https://codeforces.com/contest/2043/problem/A

# ====================================================================
# Problem: Maximum Coins Through Transformation
# Algorithms/Techniques: Bit manipulation, binary representation analysis
# Time Complexity: O(log n) per test case - each iteration processes bits of n
# Space Complexity: O(1) - constant extra space used
# ====================================================================
for n in [*open(0)][1:]:  # Read all input lines except first (test cases count)
    print(1 << (len(bin(int(n))) - 3) // 2)  # Calculate maximum coins using bit manipulation


# https://github.com/VaHiX/codeForces/