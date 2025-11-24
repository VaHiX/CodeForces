# Problem: CF 1753 A1 - Make Nonzero Sum (easy version)
# https://codeforces.com/contest/1753/problem/A1

"""
Algorithm: Nonzero Sum (easy version)

This problem requires partitioning an array of -1 and 1 values into segments such that the alternating sum of all segments equals zero.

Key insights:
1. If the length of the array is odd, it's impossible to form a valid partition because we need pairs to create alternating sums.
2. For each pair of adjacent elements, we decide how to split them:
   - If elements are the same (both 1 or both -1), we form one segment containing both elements.
   - If elements are different, we form two segments, each containing one element.

Time Complexity: O(n) where n is the length of the array
Space Complexity: O(n) for storing the partition segments

Approach:
- Process the array in pairs
- For each pair:
  - If values are equal, merge them into one segment
  - If values are different, create two separate segments
- Output the segments as required
"""

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    if n % 2 == 1:
        print(-1)
    else:
        b = []
        # Process array in pairs
        for i in range(0, len(a), 2):
            if a[i] == a[i + 1]:
                # If elements are the same, form one segment
                b += [i + 1, i + 2]
            else:
                # If elements are different, form two segments
                b += [i + 1, i + 1, i + 2, i + 2]
        print(len(b) // 2)
        for i in range(0, len(b), 2):
            print(b[i], b[i + 1])


# https://github.com/VaHiX/CodeForces/