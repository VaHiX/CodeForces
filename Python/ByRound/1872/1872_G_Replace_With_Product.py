# Problem: CF 1872 G - Replace With Product
# https://codeforces.com/contest/1872/problem/G

"""
Algorithm: Replace With Product
Purpose: Maximize the sum of array after replacing one subarray with its product.
Approach:
- Preprocess prefix sums for quick range sum calculation.
- Identify positions of 1s and non-1s.
- Special cases:
  - If no 1s: replace entire array.
  - If only one non-1: replace that element.
  - If many non-1s (>20): replace first to last non-1.
- For small number of non-1s, check all combinations of subarrays formed by non-1s to find maximum sum.

Time Complexity: O(n^2) in worst case due to nested loops over non-1 indices, but optimized with pruning.
Space Complexity: O(n) for prefix sum array and storing non-1 indices.
"""

import sys


def solve():
    n = int(sys.stdin.readline())
    a = list(map(int, sys.stdin.readline().split()))

    first_1 = -1
    p = [0 for i in range(n + 1)]
    not_1_inds = []

    # Build prefix sum array and collect indices of non-1 elements
    for i in range(n):
        p[i + 1] = p[i] + a[i]

        if a[i] == 1:
            if first_1 == -1:
                first_1 = i
        else:
            not_1_inds.append(i)

    # If there are no 1s, replace entire array
    if first_1 == -1:
        sys.stdout.write("1 " + str(n) + "\n")
        return

    # If there's only one non-1 element, replace it with itself
    if len(not_1_inds) == 1:
        sys.stdout.write("1 1\n")
        return

    # If there are too many non-1s, replace the whole range from first to last non-1
    if len(not_1_inds) > 20:
        sys.stdout.write(str(not_1_inds[0] + 1) + " " + str(not_1_inds[-1] + 1) + "\n")
        return

    # Compute product of all non-1 elements, early exit if too large
    res = 1
    for i in not_1_inds:
        res = res * a[i]
        if res > 10**6:
            sys.stdout.write(
                str(not_1_inds[0] + 1) + " " + str(not_1_inds[-1] + 1) + "\n"
            )
            return

    # Initialize max sum and best pair
    mx_res = p[-1]
    pair = [1, 1]

    # Try all combinations of subarray of non-1 indices
    for l in range(len(not_1_inds)):
        cur_p = a[not_1_inds[l]]
        for r in range(l + 1, len(not_1_inds)):
            cur_p *= a[not_1_inds[r]]
            # Calculate new sum with replaced subarray
            s = cur_p + p[-1] + p[not_1_inds[l]] - p[not_1_inds[r] + 1]
            if s > mx_res:
                mx_res = s
                pair = [not_1_inds[l] + 1, not_1_inds[r] + 1]

    sys.stdout.write(str(pair[0]) + " " + str(pair[1]) + "\n")

    return


if __name__ == "__main__":
    multitest = 1
    if multitest:
        t = int(sys.stdin.readline())
        for _ in range(t):
            solve()
    else:
        solve()


# https://github.com/VaHiX/CodeForces/