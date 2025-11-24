# Problem: CF 1839 C - Insert Zero and Invert Prefix
# https://codeforces.com/contest/1839/problem/C

"""
Algorithm: Greedy approach to reconstruct the sequence of operations.
Time Complexity: O(n) where n is the length of the input array.
Space Complexity: O(n) for storing the result and auxiliary variables.

The problem involves simulating a process where we build a binary sequence b by inserting 0 at position p and inverting the prefix of length p. 
We reverse-engineer the process by analyzing the final array a and working backwards to determine valid insertion positions.

Key idea: 
We process the array from right to left. For each element:
- If it's 0, we insert 0 at position 0.
- If it's 1, we consider the previous element to decide where to insert 0 and how to adjust our counter.

This greedy strategy correctly determines the operations needed if a solution exists.
"""

import sys

input = sys.stdin.readline
rounds = int(input())
for ii in range(rounds):
    out = 0
    length = int(input())
    arr = list(map(int, input().split()))
    if length == 1 and arr[0] == 1:
        print("NO")
        continue
    if arr[-1] == 1:
        print("NO")
        continue

    print("YES")
    ans = []
    cur = []
    cnt1 = 0
    for l in range(length - 1, -1, -1):  # Traverse array from right to left
        if arr[l] == 0:
            ans.append(0)  # Insert 0 at position 0
        else:
            if l == 0:
                # Special case for the first element
                cur = []
                ans.append(cnt1 + 1)
                cnt1 = 0
            else:
                if arr[l - 1] == 1:
                    # If previous element is 1, increment counter and append 0
                    cnt1 += 1
                    ans.append(0)
                else:
                    # If previous element is 0, append current count and reset counter
                    cnt1 += 1
                    ans.append(cnt1)
                    cnt1 = 0
    print(*ans)


# https://github.com/VaHiX/CodeForces/