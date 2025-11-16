# Problem: CF 1909 C - Heavy Intervals
# https://codeforces.com/contest/1909/problem/C

"""
Algorithm: Greedy with Sorting
Time Complexity: O(n log n)
Space Complexity: O(n)

This problem involves minimizing the total weighted length of intervals by optimally assigning
left endpoints, right endpoints, and weights. The key insight is to use a greedy approach:
- Sort left endpoints and right endpoints in ascending order.
- Sort weights in descending order to assign the heaviest weights to the smallest intervals.
- For each right endpoint, we greedily pair it with the smallest available left endpoint,
  ensuring that intervals are valid (l < r).
- The algorithm uses a stack-like mechanism (h) to maintain available left endpoints,
  and dynamically builds the interval lengths (P).
"""

def solve(L, R, C):
    h = []  # Stack to store available left endpoints
    P = []  # List to store interval lengths
    t = 0   # Pointer for left endpoints
    for r in R:
        # Add all left endpoints that are smaller than current right endpoint to the stack
        while t < len(L) and L[t] < r:
            h.append(L[t])
            t += 1
        # Pop the smallest left endpoint from the stack and calculate interval length
        P.append(r - h.pop())
    # Sort interval lengths in ascending order to pair with heaviest weights
    P.sort()
    # Return sum of product of weights and interval lengths
    return sum(c * p for c, p in zip(C, P))


def main():
    t = int(input())
    for z in range(t):
        int(input())
        L = sorted(int(x) for x in input().split())  # Sort left endpoints
        R = sorted(int(x) for x in input().split())  # Sort right endpoints
        C = sorted((int(x) for x in input().split()), reverse=True)  # Sort weights descending
        print(solve(L, R, C))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/