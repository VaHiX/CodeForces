# Problem: CF 1764 G2 - Doremy's Perfect DS Class (Medium Version)
# https://codeforces.com/contest/1764/problem/G2

"""
Algorithm: Binary Search on the position of 1 in the permutation
Techniques: 
- Use of floor division queries to deduce information about the permutation
- Binary search to locate the index where p[y] = 1
- The function `unpaired` helps in comparing counts from two subarrays
- Uses the property that for a specific k, the number of distinct values in a range can help identify 1's position

Time Complexity: O(log n * queries) where each query is O(1), so effectively O(log n)
Space Complexity: O(1) - only using a few variables for state management

The solution uses binary search to find index of 1 by evaluating how many distinct elements exist in specific subranges,
using floor division with k=2 to gather information about the structure of the permutation.
"""

def query(l, r, k):
    print("?", l + 1, r, k)
    return int(input())


def submit(y):
    print("!", y + 1)


n = int(input())
big = -1


def unpaired(l, r):
    # This function evaluates a specific query based on the idea of floor division
    # It uses the formula: 2 * Q(l,r,2) - (r - l) - (l <= big < r)
    # which helps to determine the "unpairedness" of a range with respect to a fixed value 'big'
    return 2 * query(l, r, 2) - (r - l) - (l <= big < r)


L = 0
R = n
while R - L > 1:
    M = (L + R) // 2
    left = unpaired(0, M)
    right = unpaired(M, n)

    if left == right:
        # If both sides have same "unpairedness", check for special cases
        if (M == 1 and query(M, n, n) == 2) or (M > 1 and query(0, M, n) == 1):
            # Special case handling for boundary conditions
            big = n - 1
            R = M
        else:
            # Otherwise continue binary search
            big = 0
            L = M
    elif left < right:
        # If the left side is less unpaired, search right
        L = M
    else:
        # Otherwise search left
        R = M
submit(L)


# https://github.com/VaHiX/CodeForces/