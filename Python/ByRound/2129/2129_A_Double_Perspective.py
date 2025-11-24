# Problem: CF 2129 A - Double Perspective
# https://codeforces.com/contest/2129/problem/A

"""
Algorithm: Double Perspective
Time Complexity: O(n log n)
Space Complexity: O(n)

This problem involves selecting a subset of pairs such that the difference between 
the union length (f(S)) and the number of nodes in simple cycles (g(S)) is maximized.

The key insight is:
- f(S) represents the total length covered by all intervals in the selection.
- g(S) is the number of vertices lying on at least one simple cycle of length ≥ 3.

We process pairs sorted by their start point ascending and end point descending.
Then we greedily pick intervals that do not overlap with previously selected ones
in terms of coverage, which ensures maximum contribution to f(S) while minimizing g(S).

Approach:
1. Sort the intervals by 'start' ascending and 'end' descending.
2. Traverse sorted list and for each interval, if its end point is greater than 
   the last chosen interval's end point, select it (greedily maximize coverage).
3. Return indices of selected intervals.

This greedy selection ensures high f(S) and low g(S) due to lack of overlapping or nested segments
that would contribute multiple times to g(S).
"""

for t in range(int(input())):  # Process each test case
    n = int(input())  # Read number of pairs
    a = []
    for i in range(n):
        # Append pair with 1-based index for later output
        a.append(list(map(int, input().split())) + [i + 1])
    
    # Sort by start time ascending, and end time descending to handle overlaps efficiently
    a.sort(key=lambda x: (x[0], -x[1]))
    
    p = 0  # Track the maximum right endpoint seen so far
    r = []  # Store indices of selected pairs
    
    for i in a:
        # If current interval's end is greater than previously processed max end,
        # it means we can include this without reducing f(S) due to overlaps
        if p < i[1]:
            p = i[1]  # Update max end point
            r.append(i[2])  # Store the original index (1-based)
    
    print(len(r))  # Print number of selected pairs
    print(*r)  # Print indices of selected pairs


# https://github.com/VaHiX/codeForces/