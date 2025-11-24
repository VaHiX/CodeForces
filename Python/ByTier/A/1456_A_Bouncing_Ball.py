# Problem: CF 1456 A - Bouncing Ball
# https://codeforces.com/contest/1456/problem/A

"""
Bouncing Ball Game Level Optimization

Algorithm:
- For each possible starting position modulo k (s = 0 to k-1), we check all valid bouncing sequences
- A sequence is valid if it starts at position p and continues at p+k, p+2k, ... 
- We want to minimize cost of making the path valid using two operations:
    * Add a platform (cost x per platform)
    * Remove first cell (cost y per removal)
- For each sequence starting at s, we compute the minimum cost by considering:
    * How many platforms are missing in the sequence going backwards
    * Cost of removing cells from start and adding missing platforms

Time Complexity: O(n*k) where n is the length of string S and k is the step size
Space Complexity: O(1) - only using a constant amount of extra space
"""

import sys

input = sys.stdin.buffer.readline


def process(S, p, k, x, y):
    n = len(S)
    answer = float("inf")
    
    # Try all possible starting offsets modulo k
    for s in range(k):
        # Compute number of steps in the sequence (starting at position s)
        # such that s + t*k <= n
        t = (n - s) // k
        
        missing = 0  # Count of missing platforms
        # Iterate backwards through the sequence to compute cost efficiently
        for t2 in range(t, -1, -1):
            i = s + t2 * k  # Position in the sequence
            if i < p:  # Stop if we go before p
                break
            if S[i - 1] == "0":  # If platform is missing at this position
                missing += 1
            x_cost = x * missing  # Cost of adding all missing platforms (in current window)
            y_cost = y * (i - p)  # Cost of removing cells from start to this position
            answer = min(answer, x_cost + y_cost)
    
    print(answer)


t = int(input())
for i in range(t):
    n, p, k = [int(x) for x in input().split()]
    S = input().decode().strip()
    x, y = [int(x) for x in input().split()]
    process(S, p, k, x, y)


# https://github.com/VaHiX/codeForces/