# Problem: CF 2091 B - Team Training
# https://codeforces.com/contest/2091/problem/B

"""
B. Team Training

Algorithm:
- Sort the array in descending order.
- Use a greedy approach to form teams:
  - For each element, accumulate it into a group (m).
  - When the product of group size (m) and the smallest skill in the group (current element) is >= x,
    increment the team count and reset the group size.
- Time Complexity: O(n log n) due to sorting; Space Complexity: O(1)

Input:
- Number of test cases t
- For each test case:
  - n (number of students), x (minimum strength required)
  - Array of skills a_i

Output:
- Maximum number of strong teams possible
"""

for t in range(int(input())):
    n, x = map(int, input().split())         # Read n and x
    arr = list(map(int, input().split()))    # Read skill array
    arr.sort(reverse=True)                   # Sort in descending order for greedy selection
    count = 0                                # Count of strong teams formed
    m = 0                                    # Current group size
    for i in arr:
        m += 1                               # Add current student to group
        if i * m >= x:                       # Check if team strength meets requirement
            count += 1                       # Form a new team
            m = 0                            # Reset group size
    print(count)


# https://github.com/VaHiX/codeForces/