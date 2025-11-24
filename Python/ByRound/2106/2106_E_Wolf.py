# Problem: CF 2106 E - Wolf
# https://codeforces.com/contest/2106/problem/E

"""
E. Wolf

Problem Description:
Given a permutation p of integers from 1 to n, we want to perform binary search on a range [l, r] for a value k.
The goal is to determine the minimum number of elements that need to be reordered in the subarray [l, r] so that 
the binary search succeeds. We can choose any subset of indices within [l, r] and reorder those elements.

Approach:
- Precompute positions of all values in p for quick lookup.
- For each query (l, r, k):
  - Check if k is in the range [l,r]; otherwise, answer is -1.
  - Use binary search to simulate path taken by the algorithm.
  - Count mismatches in the simulated path based on number of elements that are greater/less than k on left/right side.
  - Compute minimum reordering cost as twice maximum of bad L or bad R.

Time Complexity: O(n + q * log n)
Space Complexity: O(n)

"""
import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n, q = map(int, input().split())
    p = list(map(int, input().split()))
    pos = [0] * (n + 1)
    for i, v in enumerate(p):
        pos[v] = i + 1  # Store the position of each value in the permutation
    ans = []
    for _ in range(q):
        l, r, x = map(int, input().split())
        px = pos[x]
        if px < l or px > r:
            ans.append(-1)
            continue
        low, high = l, r
        badL = badR = 0
        cntL = cntR = 0
        while low <= high:
            mid = (low + high) // 2
            if mid == px:
                break
            if mid < px:
                cntL += 1
                if p[mid - 1] > x:
                    badL += 1
                low = mid + 1
            else:
                cntR += 1
                if p[mid - 1] < x:
                    badR += 1
                high = mid - 1
        # If there aren't enough elements on either side to place x correctly, not possible
        if cntL > x - 1 or cntR > n - x:
            ans.append(-1)
        else:
            ans.append(2 * max(badL, badR))
    print(" ".join(map(str, ans)))


# https://github.com/VaHiX/codeForces/