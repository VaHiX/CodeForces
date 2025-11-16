# Problem: CF 1894 D - Neutral Tonality
# https://codeforces.com/contest/1894/problem/D

"""
Code Purpose:
This code solves the problem of inserting elements of array b into array a to minimize the length of the longest increasing subsequence (LIS) in the resulting array.

Approach:
1. Sort array b in descending order.
2. Use a two-pointer technique to interleave elements of a and b such that:
   - When an element of b is greater than the current element of a, insert it before a[i].
   - This strategy helps avoid creating longer increasing subsequences.
3. Append remaining elements of b (if any) at the end of the result.

Time Complexity: O(n log n + m log m) due to sorting b and one-pass iteration through a and b.
Space Complexity: O(n + m) for storing the input arrays and the result.

Algorithms/Techniques:
- Sorting
- Two-pointer technique
- Greedy strategy to minimize LIS
"""

import sys


def solve():
    data = sys.stdin.read().split()
    if not data:
        return
    t = int(data[0])
    index = 1
    for _ in range(t):
        n = int(data[index])
        m = int(data[index + 1])
        index += 2
        a = list(map(int, data[index : index + n]))
        index += n
        b = list(map(int, data[index : index + m]))
        index += m
        b.sort(reverse=True)  # Sort b in descending order to enable greedy insertion
        j = 0
        res = []
        for i in range(n):
            # Insert all elements of b that are greater than current a[i]
            while j < m and b[j] > a[i]:
                res.append(str(b[j]))
                j += 1
            res.append(str(a[i]))
        # Add remaining elements of b
        while j < m:
            res.append(str(b[j]))
            j += 1
        print(" ".join(res))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/