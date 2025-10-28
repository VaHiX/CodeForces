# Problem: CF 2049 B - pspspsps
# https://codeforces.com/contest/2049/problem/B

# Flowerbox:
# Problem: Determine if a permutation of 1..n exists such that:
# - If s[i] == 'p', then [p[0], ..., p[i]] is a permutation of 1..(i+1)
# - If s[i] == 's', then [p[i], ..., p[n-1]] is a permutation of 1..(n-i)
# - If s[i] == '.', no restriction.
# Algorithm: For each position, check if there's sufficient "space" to satisfy both prefix and suffix constraints.
# Time Complexity: O(n) per test case
# Space Complexity: O(1)

for s in [*open(0)][2::2]:  # Read input lines, skip first two lines and take every 2nd
    print("YNEOS"["p" in s[:-2] and "s" in s[1:] :: 2])  # Check if all prefix and suffix constraints can be satisfied


# https://github.com/VaHiX/codeForces/