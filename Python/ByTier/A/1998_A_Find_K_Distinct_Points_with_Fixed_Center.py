# Problem: CF 1998 A - Find K Distinct Points with Fixed Center
# https://codeforces.com/contest/1998/problem/A

"""
Find K Distinct Points with Fixed Center

Algorithm:
- The problem requires placing k distinct points such that their center is at (xc, yc).
- The approach is to place points symmetrically around the center to ensure the center is correct.
- We generate a range of x and y coordinates centered around the given center.
- For even k, we adjust the second half of the points to maintain distinctness and correct center.

Time Complexity: O(k)
Space Complexity: O(k)

This solution works by:
1. Generating a sequence of x and y coordinates centered around the input center.
2. For even k, adjusting the second half of the coordinates to ensure the center is correct.
3. Printing the k points.
"""

def solve():
    x, y, k = map(int, input().split())
    # Create a list of x coordinates centered around x
    xs = list(range(x - k // 2, x - k // 2 + k))
    # Create a list of y coordinates centered around y
    ys = list(range(y - k // 2, y - k // 2 + k))

    # If k is even, adjust second half to maintain center
    if k % 2 == 0:
        for i in range(k // 2, k):
            xs[i] += 1  # Shift x coordinate
            ys[i] += 1  # Shift y coordinate

    # Print all k points
    for i in range(k):
        print(xs[i], ys[i])


def main():
    t = int(input())
    for _ in range(t):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/