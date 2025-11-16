# Problem: CF 1945 E - Binary Search
# https://codeforces.com/contest/1945/problem/E

"""
Binary Search Problem with At Most 2 Swaps

Algorithm:
- The task is to make a permutation suitable for binary search such that the target number x is found.
- Binary search is performed on a sorted array, but here the array can be unsorted.
- We can perform at most 2 swaps to rearrange elements.
- The approach:
  1. Find position of x in the permutation.
  2. Run the binary search algorithm on the current permutation.
  3. If x is already found at the final position (l), no swap needed.
  4. Else, we calculate required swaps to place x in the correct position.

Time Complexity: O(n) per test case, as we do at most one pass of array and binary search.
Space Complexity: O(n) for storing the permutation array.

The key idea is to realize that in the binary search, we are essentially tracking
left and right pointers. We use the binary search logic to identify the location where
x would end up, which allows us to determine how to fix the permutation with up to 2 swaps.
"""

import sys

write = sys.stdout.write


def search(p, l, r, x):
    # Standard binary search implementation
    # l starts at 0, r starts at n
    # Loop continues until r - l == 1
    while r - l != 1:
        m = l + ((r - l) >> 1)  # Compute middle index using bit shift for division by 2
        if p[m] <= x:
            l = m  # Move left pointer to middle
        else:
            r = m  # Move right pointer to middle
    return l


with open(0) as f:
    t = int(f.readline())
    for _ in range(t):
        n, x = map(int, f.readline().split())
        p = list(map(int, f.readline().split()))
        a = p.index(x)  # Find index of x in the current permutation
        b = search(p, 0, n, x)  # Simulate binary search to find where x would be located
        # If x is already in the correct final position, no swaps are needed
        if a == b:
            write("0\n")
        else:
            # Otherwise, perform one swap to bring x to the correct position.
            # This approach works under the constraint that at most 2 swaps are sufficient.
            write(f"1\n{a + 1} {b + 1}\n")


# https://github.com/VaHiX/CodeForces/