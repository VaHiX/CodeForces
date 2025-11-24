# Problem: CF 1859 B - Olya and Game with Arrays
# https://codeforces.com/contest/1859/problem/B

"""
Algorithm: Greedy approach to maximize the beauty of arrays
Techniques: Sorting, Greedy selection of minimum elements

Time Complexity: O(sum of m_i * log(m_i)) where m_i is the size of each array
Space Complexity: O(sum of m_i) to store all elements

The approach:
1. Sort each array to easily access the minimum and second minimum elements.
2. For n=1, the beauty is simply the minimum element.
3. For n>1:
   - Find the array with the smallest second smallest element.
   - This array's first element is added to the final answer.
   - For other arrays, add their second smallest elements.
   - The first element of the array with the smallest second element is subtracted from the total
     because it's moved from that array (if not moved, it would be included as min of that array).
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    arr = []
    n = int(input())
    for i in range(n):
        m = int(input())
        arr.append(list(map(int, input().split())))
        arr[i].sort()  # Sort each array to get min and second min easily
    if n == 1:
        print(arr[0][0])  # Only one array, so beauty = min element
    else:
        global_min = arr[0][1]  # Initialize with second smallest of first array
        idx = 0
        for i in range(1, n):  # Find index of array with smallest second smallest element
            if arr[i][1] < global_min:
                global_min, idx = arr[i][1], i
        ans = arr[idx][0]  # Start with first element of the selected array
        for i in range(n):
            ans = min(ans, arr[i][0])  # Take minimum of all first elements
        for i in range(n):
            if i != idx:  # Add second smallest of all arrays except the selected one
                ans += arr[i][1]
        print(ans)


# https://github.com/VaHiX/CodeForces/