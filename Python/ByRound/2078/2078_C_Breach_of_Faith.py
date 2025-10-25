# Problem: CF 2078 C - Breach of Faith
# https://codeforces.com/contest/2078/problem/C

"""
C. Breach of Faith
Algorithm/Technique: Greedy, Sorting, Mathematical Reconstruction

Time Complexity: O(n log n) per test case due to sorting.
Space Complexity: O(n) for storing the array.

The problem involves reconstructing a sequence of 2n+1 integers from a shuffled
sequence of 2n integers, where one element is missing. The original sequence
satisfies a specific alternating sum condition:
a1 = a2 - a3 + a4 - a5 + ... + a_{2n} - a_{2n+1}

The approach:
1. Sort the given array.
2. Compute a value 'cur' based on the alternating difference of elements in sorted order.
3. Use this computed value to reconstruct the missing element.
4. Insert it into the array and adjust positions for output format.

This solution assumes that we can deduce which element was removed by analyzing
how the alternating sum works with the given shuffled list.
"""

t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    arr.sort()  # Sort the array to facilitate greedy reconstruction
    cur = 0
    # Compute the alternating difference of elements from index 1 onwards
    for i in range(1, 2 * n - 2, 2):
        cur += arr[i] - arr[i + 1]
    cur -= arr[-1]  # Subtract last element as per formula
    cur = arr[0] - cur  # Compute the missing value using first element
    arr.append(cur)  # Add the computed missing value to the array
    arr[-1], arr[-2] = arr[-2], arr[-1]  # Swap last two elements for correct ordering
    print(" ".join(map(str, arr)))


# https://github.com/VaHiX/codeForces/