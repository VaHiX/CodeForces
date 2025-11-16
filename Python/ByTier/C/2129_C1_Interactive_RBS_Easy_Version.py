# Problem: CF 2129 C1 - Interactive RBS (Easy Version)
# https://codeforces.com/contest/2129/problem/C1

"""
Interactive RBS (Easy Version)

This interactive problem involves reconstructing a hidden bracket sequence of length n consisting of '(' and ')'.

Algorithm:
1. First, we identify a key position 'p' where the prefix s[1..p] has a non-zero number of regular bracket substrings (f(s[1..p]) > 0).
   We do this with binary search over prefixes.
2. After finding 'p', analyze the structure using queries to determine the actual bracket at positions.
   The approach uses pattern matching of query results against known four patterns to recover individual brackets.
3. Uses a precomputed mapping from query responses (f value) to the two brackets in the current pair (based on pattern matching).
4. Finally, reconstructs and outputs the entire sequence.

Time Complexity: O(n * log n + n) = O(n * log n)
Space Complexity: O(n) for storing result array

Techniques:
- Binary search to identify key bracket positions
- Pattern matching with fixed mappings (4 cases)
- Interactive problem handling using standard I/O flushing

"""

import sys

for t in range(int(input())):
    n = int(input())
    l, r = 2, n
    got = False
    while l <= r:
        m = (l + r) // 2
        print("?", m, *range(1, m + 1))  # Ask for prefix s[1..m]
        sys.stdout.flush()
        res = int(input())
        if res > 0:  # If there's at least one valid bracket substring in the prefix
            p = m
            r = m - 1
            got = True
        else:
            l = m + 1
    if got:
        ro, rc = p - 1, p  # Found a position where prefix has regular brackets; these are our reference points
    else:
        ro, rc = n, 1      # No such point found, use default
    mp = {1: [")", ")"], 2: [")", "("], 3: ["(", ")"], 4: ["(", "("]}  # Mapping for pattern matching of queries
    ans = []
    for i in range(1, n, 2):  # Pair up indices from left to right for analysis
        print("?", 7, i, rc, ro, rc, rc, i + 1, rc)  # Query the combination of multiple positions
        sys.stdout.flush()
        v = int(input())
        ans += mp[v]  # Based on response, append matching brackets from mapping
    if n % 2 == 1:  # Handle odd-length sequences
        print("?", 2, ro, n)  # Query last element
        sys.stdout.flush()
        last = int(input())
        ans.append(")" if last == 1 else "(")
    print("!", *ans, sep="")  # Output final reconstructed sequence
    sys.stdout.flush()


# https://github.com/VaHiX/codeForces/