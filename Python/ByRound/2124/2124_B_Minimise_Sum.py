# Problem: CF 2124 B - Minimise Sum
# https://codeforces.com/contest/2124/problem/B

# ==============================================================================
# Problem: B. Minimise Sum
# Algorithm/Technique: Greedy approach with prefix minimum calculation
# Time Complexity: O(n) per test case, where n is the length of the array
# Space Complexity: O(1) additional space (not counting input storage)
# ==============================================================================

for s in [*open(0)][2::2]:  # Read lines 2, 4, 6, ... from stdin (test cases)
    a, b, *_ = map(int, s.split())  # Parse first two integers as a and b
    print(a + min(a, b))  # Output the result of adding a to the smaller of a and b


# https://github.com/VaHiX/codeForces/