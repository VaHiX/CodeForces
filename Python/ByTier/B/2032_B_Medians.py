# Problem: CF 2032 B - Medians
# https://codeforces.com/contest/2032/problem/B

"""
Algorithm: 
This solution uses a greedy approach to partition the array into 3 subarrays such that the median of medians equals k.

Key insight:
- For an odd-length array, the median is the middle element when sorted.
- If we split the array into 3 parts:
  - First part: [1, 1] => median = 1
  - Middle part: [k-1, k+1] => median = k (for k > 1)
  - Last part: [n, n] => median = n
- If k = 1 or k = n, it's impossible to achieve the desired result because we must have at least 3 subarrays and each has odd length.
- This greedy strategy works as long as k is not 1 or n.

Time Complexity: O(1) - Each test case is processed in constant time.
Space Complexity: O(1) - Only a constant amount of extra space is used.
"""

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    if n == 1:
        print("1\n1")
    elif k == 1 or k == n:
        print(-1)
    else:
        print(f"3\n{1} {k - k % 2} {k + 1 + k % 2}")


# https://github.com/VaHiX/CodeForces/