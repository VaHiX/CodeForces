# Problem: CF 1997 B - Make Three Regions
# https://codeforces.com/contest/1997/problem/B

"""
Algorithm: 
- The problem asks to count the number of free cells (.) which, when blocked (converted to x), 
  create exactly 3 connected regions in a 2-row grid.
- Key insight: A free cell contributes to creating 3 regions if it is part of a "bridge" pattern 
  where it is flanked by blocked cells in the same row, and the corresponding cells in the other 
  row are also free.
- For each row, we scan for triplets (i, i+1, i+2) such that:
  - The middle cell (i+1) is free (.)
  - The cells at i and i+2 are blocked (x)
  - The corresponding cells in the other row are free
- We do this for both rows to count potential bridge patterns.
- Time Complexity: O(n), as we iterate through the grid twice.
- Space Complexity: O(1), since we only use a constant amount of extra memory.
"""

def solve(n, s1, s2):
    if n <= 2:
        print(0)
        return
    c = 0
    # Check for valid bridge patterns in row 1
    for i in range(n - 2):
        if s1[i] == "x" and s1[i + 2] == "x" and s1[i + 1] == ".":
            if s2[i] != "x" and s2[i + 2] != "x":
                c += 1
    # Check for valid bridge patterns in row 2
    for i in range(n - 2):
        if s2[i] == "x" and s2[i + 2] == "x" and s2[i + 1] == ".":
            if s1[i] != "x" and s1[i + 2] != "x":
                c += 1
    print(c)


if __name__ == "__main__":
    import sys

    input = sys.stdin.read
    data = input().split()
    t = int(data[0])
    index = 1
    for _ in range(t):
        n = int(data[index])
        index += 1
        s1 = data[index]
        index += 1
        s2 = data[index]
        index += 1
        solve(n, s1, s2)


# https://github.com/VaHiX/CodeForces/