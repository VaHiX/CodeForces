# Problem: CF 2030 D - QED's Favorite Permutation
# https://codeforces.com/contest/2030/problem/D

"""
D. QED's Favorite Permutation

Problem Description:
Given a permutation p of length n and a string s of length n containing only 'L' and 'R',
we want to determine if it's possible to sort the permutation p into non-decreasing order
using specific swap operations:
- If s[i] == 'L', we can swap p[i] with p[i-1]
- If s[i] == 'R', we can swap p[i] with p[i+1]

Operations are allowed only when s[i] matches the operation type.
The string is guaranteed to start with 'R' and end with 'L'.
We process q queries where each query flips the character at index i in s.

Key Observations:
- An element at index i can move to the left only if s[j] = 'L' for all j from i down to the destination
- Similarly, an element can move to the right only if s[j] = 'R' for all j from i up to the destination
- For sorting to be possible, there must be no "forbidden" positions that block movement

Algorithm:
- Precompute allowed positions where each element can reach its final position
- Track forbidden transitions: indices where s[i-1] = 'L' and s[i] = 'R', blocking swaps
- For each query, update forbidden set based on the change in s

Time Complexity: O(n + q) per test case
Space Complexity: O(n) for storing forbidden and allowed positions
"""

import sys
from itertools import accumulate

read = sys.stdin.readline
input = lambda: read().strip()
ir = lambda: int(read())
rir = lambda: range(int(read()))
mir = lambda: map(int, read().split())
lmir = lambda: list(map(int, read().split()))


def main():
    for _ in rir():  # Process multiple test cases
        n, q = mir()  # Read n (length of permutation) and q (number of queries)
        p = [x - 1 for x in mir()]  # Convert to 0-based indexing
        s = [c == "R" for c in input()]  # Convert string to boolean list (True for 'R')
        
        # Precompute allowed positions where a value can be placed
        # allowed: positions where i != max(p[0:i+1])
        allowed = {i + 1 for i, x in enumerate(accumulate(p, max)) if i == x != n - 1}
        
        # forbidden: positions where s[i-1] = 'L' and s[i] = 'R'
        forbidden = {
            i for i in range(1, n) if not s[i - 1] and s[i] and i not in allowed
        }
        
        # Process each query
        for _ in range(q):
            idx = ir() - 1  # Convert to 0-based indexing
            s[idx] = not s[idx]  # Flip the value at index idx
            
            # Check if the change causes a forbidden transition
            for j in (idx, idx + 1):  # Check both current and adjacent indices
                if not s[j - 1] and s[j] and j not in allowed:
                    forbidden.add(j)  # Add to forbidden set
                else:
                    forbidden.discard(j)  # Remove from forbidden set
            
            # Output result based on whether forbidden set is empty
            print("NO" if forbidden else "YES")


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/