# Problem: CF 1873 F - Money Trees
# https://codeforces.com/contest/1873/problem/F

"""
Problem: F. Money Trees
Algorithm: Sliding Window Technique
Time Complexity: O(n) for each test case, where n is the number of trees
Space Complexity: O(n) for storing the input arrays

Approach:
- Use a sliding window to maintain a valid subarray where each adjacent height is divisible.
- Expand the window by moving the right pointer.
- If the current height is not divisible by the next height, reset the window.
- Shrink the window from the left if the total fruits exceed k.
- Track the maximum length of valid subarrays.
"""

import sys

input = sys.stdin.readline


def solve():
    n, k = map(int, input().strip().split())  # Read n (number of trees) and k (max fruits)
    fruits = list(map(int, input().strip().split()))  # Read fruits in each tree
    heights = list(map(int, input().strip().split()))  # Read heights of each tree
    ans = 0  # Initialize the maximum length of valid subarray
    left = 0  # Left pointer of the sliding window
    curr = 0  # Current sum of fruits in the window
    for right, val in enumerate(fruits):  # Iterate through each tree
        curr += val  # Add current tree's fruits to the window
        if right > left:  # If not the first element
            # Check if current height is divisible by the previous height
            if heights[right - 1] % heights[right] != 0:
                left = right  # Reset window
                curr = val  # Reset fruit sum to current tree
        # Shrink window from left if current sum exceeds k
        while curr > k:
            curr -= fruits[left]
            left += 1
        # Update maximum length of valid subarray
        ans = max(ans, right - left + 1)
    print(ans)  # Print the result for current test case


for tc in range(int(input())):  # Process each test case
    solve()


# https://github.com/VaHiX/CodeForces/