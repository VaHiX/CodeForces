# Problem: CF 1927 E - Klever Permutation
# https://codeforces.com/contest/1927/problem/E

"""
Purpose: Construct a k-level permutation of length n.
A k-level permutation is one where the sums of all contiguous subarrays of length k differ by at most 1.

Algorithm:
- Use a two-pointer technique to fill the permutation.
- Alternate between placing small numbers (from left) and large numbers (from right) in a pattern.
- The pattern is based on the index modulo k, ensuring that segments of size k have balanced sums.

Time Complexity: O(n) - We iterate through each element of the array once.
Space Complexity: O(n) - We store the result array of size n.
"""

num_tests = int(input())


def solve():
    n, k = map(int, input().split())
    res = [0] * n
    num_left = 1
    num_right = n
    for i in range(k):
        idx = i
        while idx < n:
            if idx % 2:  # If index is odd
                res[idx] = num_right
                num_right -= 1
            else:  # If index is even
                res[idx] = num_left
                num_left += 1
            idx += k
    print(" ".join(map(str, res)))


for _ in range(num_tests):
    solve()


# https://github.com/VaHiX/CodeForces/