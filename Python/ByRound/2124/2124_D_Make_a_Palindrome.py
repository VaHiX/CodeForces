# Problem: CF 2124 D - Make a Palindrome
# https://codeforces.com/contest/2124/problem/D

"""
D. Make a Palindrome
Algorithm: Greedy + Two Pointers
Time Complexity: O(n log n) due to sorting and linear passes
Space Complexity: O(n) for the count array and temporary arrays

The problem involves determining whether an array can be reduced to a palindrome 
by deleting elements from subarrays of length at least k, choosing the k-th smallest 
element in each such subarray. 

The solution approach:
1. Count frequencies of all elements in the array.
2. Use prefix sums to find the largest element x such that there are at least k-1 elements 
   less than or equal to x.
3. Collect elements <= x and try to build a palindrome by checking if we can match 
   pairs from both ends using two pointers, ensuring valid operations.

Key idea:
Once we know which elements we can possibly use in the final palindromic array,
we simulate matching left and right ends of the collection to validate palindrome formation.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def II(base=10):
    return int(input(), base)


def LI():
    return list(map(int, input()))


def LII():
    return list(map(int, input().split()))


def main():
    n, k = LII()
    A = LII()
    ct = [0] * (n + 1)  # Count array to store frequency of elements
    for a in A:
        ct[a] += 1  # Count occurrences of each element
    s, x = 0, 0
    while s < k - 1:  # Find the smallest x such that we have at least k-1 elements <= x
        x += 1
        s += ct[x]
    c = s - k + 1  # Number of excess elements that can be used to form palindrome

    B = [a for a in A if a <= x]  # Keep only elements <= x
    i, j = 0, len(B) - 1  # Two pointers from start and end
    while i < j:
        if B[i] == B[j]:
            i += 1
            j -= 1
        elif B[i] < x and B[j] < x:
            # Both ends are less than x, so they cannot be matched
            return "NO"
        elif c == 0:
            # No more operations allowed to resolve mismatches
            return "NO"
        else:
            # Can use one operation to delete larger element and try again
            c -= 1
            i, j = (i + 1, j) if B[i] == x else (i, j - 1)
    return "YES"


for _ in range(II()):
    print(main())


# https://github.com/VaHiX/codeForces/