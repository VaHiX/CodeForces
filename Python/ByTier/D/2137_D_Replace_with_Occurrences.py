# Problem: CF 2137 D - Replace with Occurrences
# https://codeforces.com/contest/2137/problem/D

"""
D. Replace with Occurrences

Purpose:
This code determines whether there exists an array 'a' such that the frequency of each element in 'a'
matches the given array 'b'. If such an array exists, it constructs one; otherwise, it outputs -1.

Algorithm/Techniques:
- Greedy approach with frequency tracking
- Uses a mapping from elements to their assigned values based on occurrence counts
- Tracks how many times each number can still be used before being assigned a new value

Time Complexity: O(n) - Each element is processed once.
Space Complexity: O(n) - For storing arrays and counts.
"""

import sys

input = sys.stdin.readline
minput = lambda: map(int, input().split())

for _ in range(int(input())):
    n = int(input())
    cnt = [0] * (n + 1)          # Tracks how many times each number can be reused
    ans = [0] * n                # Output array to be constructed
    a = 0                        # Counter for assigning new values
    num = [0] * (n + 1)          # Maps numbers to their assigned values
    
    b = list(minput())
    
    for i in range(n):
        if cnt[b[i]] == 0:
            # First time seeing this number, assign a new value
            cnt[b[i]] = b[i] - 1   # Set how many more times we can reuse this value
            a += 1                 # Increment counter for new assignment
            num[b[i]] = a          # Assign the new value to this number
        else:
            # Reducing the remaining count before reusing
            cnt[b[i]] -= 1
        
        ans[i] = num[b[i]]       # Assign current value to answer array
    
    if sum(cnt) == 0:
        print(*ans)
    else:
        print(-1)


# https://github.com/VaHiX/codeForces/