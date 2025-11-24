# Problem: CF 1680 C - Binary String
# https://codeforces.com/contest/1680/problem/C

"""
Algorithm: Prefix Sums + Sliding Window
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(n) for the prefix sum array

The problem is to find the minimum cost of removing characters from the beginning and end of a binary string such that:
- Cost = max(number of 0s remaining, number of 1s removed)
- We can remove any number of 0s from the start and any number of 1s from the end
- The goal is to minimize this cost

Approach:
1. Use prefix sums to quickly calculate number of 1s in any subsegment
2. For each possible number of 1s to remove from the end (from 0 to total 1s), 
   compute the minimum cost of the remaining situation
3. The cost for a given configuration is max(0s left, 1s removed)
"""

t = int(input())
for tub in range(t):
    s = input()
    n = len(s)
    # a[i] stores number of 1s in s[0:i]
    a = [0]
    for i in range(n):
        a.append(a[-1] + int(s[i]))
    # Initially, remove all 0s from the end
    # ans is initialized to all 1s removed
    ans = n - a[-1]
    # Try all possible numbers of 1s to remove from the end
    for i in range(n - a[-1] + 1):
        j = i + a[-1]  # j is the end index of window to keep
        # Calculate 1s in this window
        ones_in_window = a[j] - a[i]
        # Number of 1s removed = total 1s - 1s in window
        ones_removed = a[-1] - ones_in_window
        # Number of 0s remaining = total length - window length - 1s in window
        zeros_remaining = (j - i) - ones_in_window
        # Cost = max(0s remaining, 1s removed)
        cost = max(zeros_remaining, ones_removed)
        ans = min(ans, cost)
    print(ans)


# https://github.com/VaHiX/CodeForces/