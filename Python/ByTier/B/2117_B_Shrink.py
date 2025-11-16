# Problem: CF 2117 B - Shrink
# https://codeforces.com/contest/2117/problem/B

# Flowerbox
"""
Code Purpose:
This code constructs a permutation of length n that maximizes the number of shrink operations.
A shrink operation removes an element at index i (where a[i] > a[i-1] and a[i] > a[i+1]) from the array.
The goal is to build a permutation such that we can perform as many shrink operations as possible.

Algorithms/Techniques:
- Greedy construction strategy
- The pattern involves placing elements in a way that allows maximum number of valid peaks to be formed

Time Complexity: O(n) for each test case, since we're just printing a pre-defined sequence.
Space Complexity: O(n) for the output array (not counting input/output storage).

"""

for _ in range(int(input())):  # Read number of test cases
    n = int(input())  # Read size of permutation
    # Generate the sequence: from 2 to n, then append 1
    # This pattern ensures maximum shrink operations by forming multiple peaks
    print(" ".join(map(str, range(2, n + 1))) + " 1")


# https://github.com/VaHiX/codeForces/