# Problem: CF 2108 A - Permutation Warm-Up
# https://codeforces.com/contest/2108/problem/A

# ==================================================================
# Problem: Count distinct values of f(p) = sum(|p[i] - i|) for all permutations of 1..n
# Algorithm: Mathematical pattern recognition
# Time Complexity: O(1) per test case
# Space Complexity: O(1)
# ==================================================================

for _ in range(int(input())):  # Read number of test cases
    n = int(input())           # Read the value of n
    # The formula derived from observing patterns is: (n^2 // 4) + 1
    print((n ** 2) // 4 + 1)


# https://github.com/VaHiX/codeForces/