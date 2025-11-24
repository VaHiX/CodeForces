# Problem: CF 2136 F2 - From the Unknown (Hard Version)
# https://codeforces.com/contest/2136/problem/F2

# Problem: F2. From the Unknown (Hard Version)
# Purpose: Determine the width parameter W of an interactive text editor by querying articles and observing line counts.
# Algorithm: Binary search with two queries to efficiently bracket the value of W.
# Time Complexity: O(log(10^5)) due to binary search on possible W values.
# Space Complexity: O(10^5) for storing precomputed mappings in val dictionary.

import sys

input = sys.stdin.readline
val = {}
for i in range(125, 10**5 + 1):  # Precompute ranges of W values for each result
    cnt = i // 125  # How many times we can pack 125-sized items
    v = 9999 // cnt + 1  # Approximate number of lines needed for 9999 total length with count items
    if v not in val:
        val[v] = []
    val[v].append(i)  # Group W values by how they behave in query

for _ in range(int(input())):
    q1 = [125 for _ in range(10000)]  # First query: pack as many 125-length words as possible
    print("?", 10000, *q1, flush=True)
    resp = int(input())
    if resp == 0:
        # First query failed -> W must be less than sum of all words (125 * 10000)
        q2 = [1 for _ in range(15000)]  # Second query: many small items to get min line count
        print("?", 15000, *q2, flush=True)
        resp2 = int(input())
        # Find appropriate W based on response of second query
        for i in range(1, 126):
            if 14999 // i + 1 == resp2:
                print("!", i, flush=True)
                break
    else:
        # First query succeeded -> W >= sum of all words (i.e. 1250000)
        start, end = val[resp][0], val[resp][-1]  # Get min and max W values matching response
        q2 = []
        length = end - start  # Range to cover in binary search
        for i in range(1, length + 1):
            q2.append(start)  # Append the start of range
            q2.append(i)      # And an incrementing value to determine line count
        print("?", len(q2), *q2, flush=True)
        resp2 = int(input())
        cnt = length * 2  # Expected lines for this query setup
        # Binary search through possible W values in range
        for i in range(start, end + 1):
            if cnt == resp2:
                print("!", i, flush=True)
                break
            cnt -= 1  # Decrease expected lines as we move up in W


# https://github.com/VaHiX/codeForces/