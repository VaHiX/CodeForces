# Problem: CF 484 A - Bits
# https://codeforces.com/contest/484/problem/A

"""
Algorithm: Greedy Bit Manipulation
Approach:
For each query (l, r), we want to find the number x in [l, r] with the maximum number of set bits ('1' bits).
If there are multiple such numbers, we return the smallest one.

The strategy is to start from l and try to set each unset bit (from least significant to most significant)
to see if we can increase the number of set bits without exceeding r.

Time Complexity: O(60 * n) = O(n), where n is the number of queries, since we loop at most 60 times (for 60 bits).
Space Complexity: O(1), as we only use a constant amount of extra space.
"""

def solve():
    import sys

    input = sys.stdin.readline
    q = int(input())
    for _ in range(q):
        l, r = map(int, input().split())
        x = l
        # Iterate through all possible bit positions (up to 60 bits for 10^18)
        for b in range(60):
            # Check if the b-th bit is not set in x
            if not (x >> b) & 1:
                # Create a candidate by setting the b-th bit
                candidate = x | (1 << b)
                # If the candidate is within range [l, r], update x
                if candidate <= r:
                    x = candidate

        print(x)


solve()


# https://github.com/VaHiX/CodeForces/