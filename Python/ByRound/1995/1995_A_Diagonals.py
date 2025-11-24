# Problem: CF 1995 A - Diagonals
# https://codeforces.com/contest/1995/problem/A

"""
Algorithm: Greedy placement on diagonals
Techniques: Mathematical analysis, greedy strategy

Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem asks to place k chips on an n x n board such that the number of occupied diagonals is minimized.
Each diagonal is defined by the sum i+j. To minimize occupied diagonals, we greedily try to place as many chips as possible
on each diagonal before moving to the next one.

We calculate how many chips can fit on a diagonal in increasing order (from 1 to n and then from n-1 to 1),
and count how many diagonals are needed until we place all k chips.
"""

for s in [*open(0)][1:]:
    n, k = map(int, s.split())
    r = 0
    # Loop condition ensures we process up to k chips
    while -k < k:
        r += 1
        # Subtract the number of chips that can fit on current diagonal
        k -= n - r // 2
    print(r)


# https://github.com/VaHiX/codeForces/