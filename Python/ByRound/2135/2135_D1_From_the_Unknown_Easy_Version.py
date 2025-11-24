# Problem: CF 2135 D1 - From the Unknown (Easy Version)
# https://codeforces.com/contest/2135/problem/D1

"""
Problem: Find the width W of a text editor by making at most 2 queries.

Algorithms/Techniques:
- Binary search-like approach using two strategic queries to determine W.
- Preprocessing lookup tables m1 and m2 to map results of queries to possible values of W.
- Adaptive interaction, where W may change but is always valid for all prior answers.

Time Complexity: O(1) per test case (preprocessing O(1) + constant-time queries)
Space Complexity: O(1) (fixed-size arrays m1 and m2 of size 100001)

The solution uses two lookup tables:
- m1 maps query result to a potential value of W for certain input patterns.
- m2 maps query results to base values for computing W in the second scenario.

Query Strategy:
1. First query: [100000] 330 times to get a rough idea about W using m1.
2. If result is 0, second query uses one big word to determine exact value with m2.
3. Otherwise, use a specific pattern to calculate the final value of W.

"""

from sys import stdout

m1 = [0] * 100001  # Lookup table for first strategy
m2 = [0] * 100001  # Lookup table for second strategy

# Preprocessing step to fill lookup tables based on mathematical properties
for i in range(1, 330):
    m1[99999 // i + 1] = i
for i in range(1, 100000 // 330 + 1):
    m2[99999 // i + 1] = i * 330

def solve():
    global m1, m2
    # First query: send a large number of small words to get an estimate of W
    print("? 100000" + " 330" * 100000)
    stdout.flush()
    res = int(input())
    
    if res == 0:
        # If first query fails (result is 0), it means W was too small
        # Send a new query to find exact W using one big word pattern
        print("? 100000" + " 1" * 100000)
        stdout.flush()
        res = int(input())
        print(f"! {m1[res]}")  # Use m1 to map result back to W
    else:
        # If the first query succeeded, compute result using second strategy
        l = m2[res]  # Get base value from m2 mapping
        # Send another query with a mix of values to calculate difference
        print("? 658 " + " ".join([f"{l} {i}" for i in range(1, 330)]))
        stdout.flush()
        res = int(input())
        print(f"! {l + 658 - res}")  # Final calculation using second pattern


for ca in range(int(input())):
    solve()


# https://github.com/VaHiX/codeForces/