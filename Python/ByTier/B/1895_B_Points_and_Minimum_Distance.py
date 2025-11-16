# Problem: CF 1895 B - Points and Minimum Distance
# https://codeforces.com/contest/1895/problem/B

"""
Algorithm: Points and Minimum Distance
Purpose: Given a sequence of 2n integers, split them into n pairs to form n points on a 2D plane.
         Then find a path visiting all points such that the total Manhattan distance is minimized.
Techniques:
- Greedy approach
- Sorting to minimize distance between consecutive points

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the arrays

Approach:
1. Sort the input array 'a'
2. Split the sorted array into two halves
3. Pair elements from the first half with elements from the second half
4. Calculate the Manhattan distance between the extremes of each half
5. The sum of these distances gives the minimum path length
"""

for _ in range(int(input())):
    n = int(input())
    arr = sorted(list(map(int, input().split())))  # Sort the array to facilitate pairing
    arr1 = arr[:n]                                 # First n elements
    arr2 = arr[n:]                                 # Last n elements

    x = arr1[-1] - arr1[0]                         # Max - Min of first half
    y = arr2[-1] - arr2[0]                         # Max - Min of second half

    print(x + y)                                   # Total minimum path length
    for a, b in zip(arr1, arr2):                   # Print the pairs
        print(a, b)


# https://github.com/VaHiX/CodeForces/