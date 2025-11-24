# Problem: CF 2137 B - Fun Permutation
# https://codeforces.com/contest/2137/problem/B

# ==============================================================================
# Problem: B. Fun Permutation
# Purpose: Given a permutation p of size n, construct another permutation q such that 
#          GCD(p[i] + q[i], p[i+1] + q[i+1]) >= 3 for all valid i.
# Algorithm/Technique: Greedy construction with cycle handling
# Time Complexity: O(n) - linear traversal of the permutation
# Space Complexity: O(n) - to store the result and input
# ==============================================================================

# Read input lines, skip first two (n and p), then process every 2nd line starting from index 2
for s in [*open(0)][2::2]:
    a = s.split()  # Split the current line into integers
    for x in a:    # Iterate over each number in the line
        # Calculate and print the required value: len(a) + 1 - int(x)
        # This is based on pattern matching from examples to satisfy GCD condition
        print(len(a) + 1 - int(x))


# https://github.com/VaHiX/codeForces/