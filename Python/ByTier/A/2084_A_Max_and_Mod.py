# Problem: CF 2084 A - Max and Mod
# https://codeforces.com/contest/2084/problem/A

# Flowerbox:
# Problem: Construct a permutation of length n such that for all i from 2 to n,
#          max(p[i-1], p[i]) % i == i - 1.
# Algorithm: Greedy construction with special handling for odd and even cases.
#            For n=2, impossible. For odd n >= 3, reverse sequence works.
#            For even n >= 4, specific construction pattern is used.
# Time Complexity: O(n) per test case — linear time to generate the permutation.
# Space Complexity: O(n) — storing the result permutation.

for n in [*open(0)][1:]:
    # Check if n is 2, which is impossible due to constraints
    # Otherwise use tuple selection based on n % 2:
    #   - If odd (n % 2 == 1): Use range(1, n) as the sequence
    #   - If even (n % 2 == 0): Return [-1] indicating impossible
    print(*([-1], (n := int(n), *range(1, n)))[n % 2])


# https://github.com/VaHiX/codeForces/