# Problem: CF 2129 C3 - Interactive RBS (Hard Version)
# https://codeforces.com/contest/2129/problem/C3

# C3. Interactive RBS (Hard Version)
# Purpose: Find a hidden bracket sequence of length n using interactive queries.
# Algorithm:
#   1. Determine the positions of the first '(' and last ')' in the sequence.
#   2. Use binary search to locate these special brackets.
#   3. Reconstruct the rest of the sequence by querying combinations of
#      known and unknown brackets, leveraging properties of valid bracket substrings.
# Time Complexity: O(n log n)
# Space Complexity: O(n)
import sys

for _ in range(int(input())):
    n = int(input())
    print("?", n, " ".join(str(x) for x in range(1, n + 1)))
    sys.stdout.flush()
    if input() == "0":
        # If the whole sequence has no valid brackets, then it's something like )))( or (((, etc.
        # Find a bracket that is not at the start but can be part of an opening/closing pair
        op, cl = n, 1
    else:
        # Binary search for the leftmost '(' (op) and rightmost ')' (cl)
        lo, hi = 1, n
        while lo < hi:
            m = (lo + hi) // 2
            print("?", m, " ".join(str(x) for x in range(1, m + 1)))
            sys.stdout.flush()
            if int(input()) > 0:
                hi = m
            else:
                lo = m + 1
        op, cl = lo - 1, lo
    s = bytearray(n + 1)
    s[op] = ord("(")  # Set the found opening bracket
    s[cl] = ord(")")  # Set the found closing bracket
    i = 1
    while True:
        qb = []  # Queue for positions to query
        q = []   # List of indices to send in query
        v = 0    # Counter for current depth level in recursion (used here as bit offset)
        bc = 0   # Count of possible bracket pairs to consider

        while True:
            a = q and [cl] or []  # If there are queued positions, prepend cl (to avoid interference)
            while i <= n and s[i]:
                i += 1
            if i > n:
                break
            # Prepend some opening brackets before the current position
            a += [op, cl] * ((1 << (v >> 1)) - 1)
            # Add a single closing bracket
            a += [i, cl]
            # Then add more bracket pairs after
            a += [op, cl] * ((1 << ((v + 1) >> 1)) - 1)
            
            if len(q) + len(a) > 1001:
                break  # Limit query size to stay under 1000
            
            np = (1 << (v >> 1)) + (1 << ((v + 1) >> 1)) - 1
            bc += np * (np + 1) // 2
            qb.append(i)
            q += a
            v += 1
            i += 1
        if not q:
            break  # Nothing left to process
        print("?", len(q), " ".join(str(v) for v in q))
        sys.stdout.flush()
        k = bc - int(input())  # Use the difference to determine pattern bits
        
        for v in qb:
            # Determine the final bracket by checking if bit is set
            s[v] = ord(")") if (k & 1) else ord("(")
            k >>= 1  # Shift right to check next bit
            
    print("!", s[1:].decode())
    sys.stdout.flush()


# https://github.com/VaHiX/codeForces/