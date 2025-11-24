# Problem: CF 1290 A - Mind Control
# https://codeforces.com/contest/1290/problem/A

"""
Algorithm/Technique: 
- This problem involves dynamic selection of array elements by people in a line.
- You control up to k people's choices (first or last element).
- The goal is to find the maximum guaranteed value you can obtain at your turn.
- Uses a combination of precomputed ranges and sliding window minimums to simulate all possible scenarios.

Time Complexity: O(n * m) per test case
Space Complexity: O(n) per test case

This approach works by:
1. Precomputing min values for each possible segment where you could end up
2. Simulating the choices of controlled people and uncontrolled people
3. Using a sliding window technique to evaluate max guaranteed value across all valid strategies
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, m, k = map(int, input().split())
    w = list(map(int, input().split()))
    
    # If the number of elements to take is less than or equal to 2*k+2,
    # we can only consider up to m elements from both ends.
    if m < k + 2:
        w = w[:m] + w[-m:]
        print(max(w))
    else:
        c = 0
        # d[i] represents the maximum of the first and last (n - m) elements starting at position i
        d = [max(w[i], w[i + n - m]) for i in range(m)]
        # Sliding window to find best guaranteed value considering k controlled people
        for i in range(k + 1):
            # For each valid control scenario, compute worst-case min for uncontrolled people
            c = max(c, min(d[i : i + m - k]), min(d[k - i : m - i]))
        print(c)


# https://github.com/VaHiX/codeForces/