# Problem: CF 2043 C - Sums on Segments
# https://codeforces.com/contest/2043/problem/C

# C. Sums on Segments
# Problem: Find all possible subarray sums of an array where at most one element is not ±1.
# Algorithm:
#   - Process the array in segments of consecutive ±1 values.
#   - For each such segment, track the minimum and maximum prefix sum.
#   - When encountering a non-±1 value, start a new segment.
#   - Combine ranges from previous and current segments to compute all possible sums.
# Time Complexity: O(n) per test case (linear scan)
# Space Complexity: O(1) for tracking ranges, O(k) for output where k is number of unique sums.

from sys import stdin

inp = stdin.readline
t = int(inp())
for _ in range(t):
    n = int(inp())
    arr = [int(x) for x in inp().split()]
    m = [[0, 0], [0, 0]]  # m[0] for first segment, m[1] for second (when f=1)
    f = 0                  # flag to switch between segments
    d = [0, 0]             # d[0] max positive deviation, d[1] max negative deviation
    nr = 0                 # store last non ±1 number
    cnt = 0                # running sum in current segment

    for c in arr:
        if c == 1 or c == -1:
            # Update cumulative sum and range stats
            cnt += c
            d[0] = max(cnt - m[f][0], d[0])  # maximum positive deviation from segment start
            d[1] = max(m[f][1] - cnt, d[1])  # maximum negative deviation from segment start
            m[f][0] = min(cnt, m[f][0])      # minimum prefix sum in segment (initially 0)
            m[f][1] = max(cnt, m[f][1])      # maximum prefix sum in segment (initially 0)
        else:
            # When we hit non ±1 value:
            # move current segment to the start of next one
            m[0][0] -= cnt              # subtract accumulated sum from segment 0 start
            m[0][1] -= cnt              # same for end
            cnt = 0                     # reset running sum
            f = 1                       # switch flag
            nr = c                      # store the special value

    # Now build set of possible sums:
    s = set(range(-d[1], d[0] + 1))  # all possible sums from first segment range
    
    if f:
        # If there was a non ±1 element, combine ranges
        # Compute bounds based on segment 0 and 1 interaction with nr
        start_val = min(-m[0][0] + nr + m[1][1], -m[0][1] + nr + m[1][0])
        end_val = max(-m[0][0] + nr + m[1][1], -m[0][1] + nr + m[1][0])
        s = s.union(set(range(start_val, end_val + 1)))

    print(len(s))
    print(*sorted(list(s)))


# https://github.com/VaHiX/codeForces/