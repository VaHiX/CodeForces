# Problem: CF 1931 C - Make Equal Again
# https://codeforces.com/contest/1931/problem/C

"""
Algorithm: Make Equal Again
Approach:
- Check if all elements in the array are already equal; if so, return 0.
- Otherwise, calculate the minimum cost to make all elements equal by:
  1. Finding the minimum cost to change the array to match the first element.
  2. Finding the minimum cost to change the array to match the last element.
  3. Taking the minimum of these two costs.

Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(1), as we use only a constant amount of extra space.
"""

import sys


def get_cost(a, n, stdval):
    # Find the first index where value is not equal to stdval
    start = n - 1
    for i in range(n):
        if stdval != a[i]:
            start = i
            break
    # Find the last index where value is not equal to stdval
    end = n - 1
    for j in range(n - 1, -1, -1):
        if stdval != a[j]:
            end = j
            break
    # Return the length of the subarray that needs to be changed
    return max(end - start + 1, 0)


def main():
    n = int(sys.stdin.readline())
    (*a,) = map(int, sys.stdin.readline().split())
    # Check if all elements are the same
    sameAll = True
    for ai in a:
        if ai != a[0]:
            sameAll = False
            break
    if sameAll:
        print(0)
        return
    # Calculate the minimum cost to make all elements equal to first or last element
    val1 = get_cost(a, n, a[0])
    val2 = get_cost(a, n, a[-1])
    print(min(val1, val2))
    return


T = int(sys.stdin.readline())
for _ in range(T):
    main()


# https://github.com/VaHiX/CodeForces/