# Problem: CF 2126 B - No Casino in the Mountains
# https://codeforces.com/contest/2126/problem/B

"""
B. No Casino in the Mountains

Purpose:
This code solves a problem where Jean wants to maximize the number of peaks he can visit.
Each hike takes exactly k consecutive days of good weather (0), and after each hike,
he must take a break (at least one day). The goal is to determine the maximum number
of hikes Jean can complete.

Algorithm/Techniques:
- Greedy approach: iterate through the array once, tracking available days for hiking.
- Use a sliding window-like logic: maintain a count of consecutive good weather days,
  and when k good days are found, start a hike and reset the counter.
- Track breaks using the constraint that after each hike, a mandatory break follows.

Time Complexity: O(n), where n is the length of the array. Each element is visited once.
Space Complexity: O(1), only constant extra space is used.

Input:
- First line: number of test cases t
- For each test case:
  - Line 1: n (number of days) and k (hike duration)
  - Line 2: n integers a_i where a_i = 0 means good weather, 1 means rain

Output:
- For each test case, print the maximum number of hikes Jean can make.
"""

for _ in range(int(input())):           # Handle multiple test cases
    n, k = map(int, input().split())    # Read n (days) and k (hike duration)
    a = list(map(int, input().split())) # Read the weather array
    i = 0                               # Pointer to current day
    c = 0                               # Count of hikes completed
    x = k                               # Store original value of k for reset
    while i < n:                        # Loop through all days
        if a[i] == 0:                   # If it's good weather
            k -= 1                      # Decrease remaining days needed for hike
            i += 1                      # Move to next day
        elif a[i] == 1:                 # If it's rain
            k = x                       # Reset k to original value (start fresh)
            i += 1                      # Move to next day
        if k == 0:                      # If we've found k consecutive good days
            c += 1                      # Complete a hike
            k = x                       # Reset k for next potential hike
            i += 1                      # Skip the mandatory break day
    print(c)                            # Output number of hikes for this test case


# https://github.com/VaHiX/codeForces/