# Problem: CF 1927 D - Find the Different Ones!
# https://codeforces.com/contest/1927/problem/D

"""
Algorithm: Preprocessing with next different element
Techniques: Dynamic Programming, Prefix/Suffix Processing

Time Complexity: O(n + q) where n is the length of the array and q is the number of queries.
Space Complexity: O(n) for storing the next_diff array.

The algorithm preprocesses the array to quickly answer queries about whether there exists a pair of different elements in a given range.
It uses a reverse pass to compute for each position the next index where the value differs.
This allows answering each query in O(1) time.
"""

import sys


def solution():
    n = int(sys.stdin.readline())
    a = list(map(int, sys.stdin.readline().split()))
    q = int(sys.stdin.readline())

    # next_diff[i] stores the index of the next element after i that is different from a[i]
    next_diff = [0] * n

    # Base case: last element has no next element, so set to n (out of bounds)
    next_diff[n - 1] = n

    # Traverse from right to left to fill next_diff array
    for i in range(n - 2, -1, -1):
        if a[i] == a[i + 1]:
            # If current element equals the next one, inherit the next_diff value
            next_diff[i] = next_diff[i + 1]
        else:
            # If different, the next different element is just the next index
            next_diff[i] = i + 1

    res = []

    # Process each query
    for _ in range(q):
        l_1based, r_1based = map(int, sys.stdin.readline().split())

        l_0based = l_1based - 1
        r_0based = r_1based - 1

        # Check if there's a different element within the range [l_0based, r_0based]
        if next_diff[l_0based] <= r_0based:
            # A different element exists, output the indices (1-based)
            res.append(f"{l_0based + 1} {next_diff[l_0based] + 1}")
        else:
            # No different element in the range, output -1 -1
            res.append("-1 -1")

    # Write all results at once
    sys.stdout.write("\n".join(res) + "\n")


num_test_cases = int(sys.stdin.readline())
for _ in range(num_test_cases):
    solution()


# https://github.com/VaHiX/CodeForces/