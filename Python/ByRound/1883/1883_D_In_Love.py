# Problem: CF 1883 D - In Love
# https://codeforces.com/contest/1883/problem/D

"""
Code Purpose:
This code solves the problem of determining, after each operation (adding or removing a segment), 
whether there exists a pair of non-intersecting segments in the multiset. 
It uses min-heaps to efficiently track the left and right endpoints of active segments and 
maintains a counter of how many times each endpoint appears.

Algorithms/Techniques:
- Use of min-heaps (priority queues) to manage left and right endpoints.
- Maintains frequency counts of left and right endpoints.
- Lazy deletion from heaps: only remove elements when their count drops to zero.
- Checks if the smallest right endpoint is less than the largest left endpoint to determine non-intersection.

Time Complexity: O(q log q), where q is the number of operations. Each heap operation (push/pop) takes O(log q) time.
Space Complexity: O(q), for storing the endpoints and their frequencies in the heaps and dictionaries.
"""

import heapq as hp
import sys
from collections import defaultdict

input = sys.stdin.readline
a = defaultdict(int)  # Count of left endpoints
b = defaultdict(int)  # Count of right endpoints
c = []  # Min-heap for left endpoints (stored as negative values for max-heap behavior)
d = []  # Min-heap for right endpoints
ans = []

for _ in range(int(input())):
    i, j, k = input().split()  # i is operation type (+ or -), j is left, k is right
    j = -int(j)  # Store left endpoint as negative to simulate max-heap using min-heap
    k = int(k)
    
    if i == "+":  # Add segment
        a[j] += 1  # Increment count of left endpoint
        b[k] += 1  # Increment count of right endpoint
        hp.heappush(c, j)  # Push left endpoint to heap
        hp.heappush(d, k)  # Push right endpoint to heap
    else:  # Remove segment
        a[j] -= 1  # Decrement count of left endpoint
        b[k] -= 1  # Decrement count of right endpoint
    
    # Remove outdated entries from heap c (left endpoints)
    while c and a[c[0]] < 1:
        hp.heappop(c)
    
    # Remove outdated entries from heap d (right endpoints)
    while d and b[d[0]] < 1:
        hp.heappop(d)
    
    # Check if there exists a non-intersecting pair:
    # If smallest right endpoint is less than the largest left endpoint (remember j was stored as -j)
    ans.append("YES" if (c and d[0] < -c[0]) else "NO")

print("\n".join(ans))


# https://github.com/VaHiX/CodeForces/