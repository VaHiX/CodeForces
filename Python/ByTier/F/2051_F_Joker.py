# Problem: CF 2051 F - Joker
# https://codeforces.com/contest/2051/problem/F

"""
F. Joker

Purpose:
This code processes a series of operations on a deck of n cards where a joker is initially at position m.
Each operation moves a card from a specified position to either the beginning or the end of the deck.
After each operation, we compute how many distinct positions the joker can occupy.

Algorithms/Techniques:
- Tracking the range of possible joker positions using two pointers 'l' and 'r'
- Efficiently updating the range based on where the moved card is relative to the current range
- Using mathematical computation to count valid positions without simulating full deck

Time Complexity: O(q) amortized per test case, as each element is processed at most a constant number of times.
Space Complexity: O(1) excluding input/output storage.

Input Format:
- For each test case:
  - First line: n (deck size), m (initial joker position), q (number of operations)
  - Second line: q integers representing positions to move

Output Format:
- For each test case, print q integers representing the number of valid joker positions after each operation.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    N, M, Q = map(int, input().split())
    A = list(map(int, input().split()))
    a, b = 0, N + 1  # Track the leftmost and rightmost joker positions (invalid initially)
    l, r = M, M      # Current valid range for joker position
    Ans = []
    
    for n in A:
        if l != N + 1:  # If there's a valid range for joker
            if l <= n <= r:
                # Moving inside the range -> extend the range by shrinking or extending a/b
                a += 1
                b -= 1
                if l == r:
                    # If l == r, it means we have one position; reset to invalid range
                    l, r = N + 1, 0
            elif n > r:
                # Moving right of current range -> grow the right boundary
                r = min(N, r + 1)
                if a != 0:
                    a += 1
                if b != N + 1 and n < b:
                    b -= 1
            else:
                # Moving left of current range -> shrink the left boundary
                l = max(l - 1, 1)
                if b != N + 1:
                    b -= 1
                if a != 0 and a < n:
                    a += 1
        else:
            # If no valid range exists, update based on position `n`
            if a < n:
                a += 1
            if b > n:
                b -= 1

        # Compute the count of possible positions
        if l != N + 1:
            cnt = r - l + 1  # Size of interval [l, r]
            if a < l:
                cnt += a     # Add from left side
            else:
                cnt += l - 1   # Subtract from the start if not fully overlapping

            if b > r:
                cnt += N - b + 1  # Add tail beyond right
            else:
                cnt += N - r      # Add from right
        else:
            # No valid interval, but we have a,b tracking
            if a < b:
                cnt = a + N - b + 1   # Compute via two segments
            else:
                cnt = N               # All positions available

        Ans.append(cnt)
    print(*Ans)


# https://github.com/VaHiX/codeForces/