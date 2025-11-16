# Problem: CF 1090 M - The Pleasant Walk
# https://codeforces.com/contest/1090/problem/M

"""
Code Purpose:
This code finds the longest segment of houses on a road such that no two adjacent houses have the same color.
The approach uses a sliding window technique to group consecutive houses with different colors, then returns the maximum length of such a group.

Algorithms/Techniques:
- Sliding window / grouping technique
- Linear scan with grouping

Time Complexity: O(n log n) due to sorting the group sizes
Space Complexity: O(n) for the array 'b' that stores group lengths
"""

n, k = map(int, input().split())
a = list(map(int, input().split()))
b = [1] * n  # Array to store lengths of segments with no adjacent same colors
j = 0  # Index pointer for the current segment in 'b'

# Iterate through the houses starting from the second one
for i in range(1, n):
    # If current house color is different from previous house color
    if a[i] != a[i - 1]:
        # Extend the current segment length
        b[j] += 1
    else:
        # If colors are same, start a new segment
        j += 1

# Sort the segment lengths in descending order to get the maximum first
b.sort(reverse=True)
ans = b[0]  # The longest segment length
print(ans)


# https://github.com/VaHiX/CodeForces/