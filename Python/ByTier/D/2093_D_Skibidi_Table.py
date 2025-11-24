# Problem: CF 2093 D - Skibidi Table
# https://codeforces.com/contest/2093/problem/D

"""
D. Skibidi Table

Algorithms/Techniques:
- Recursive decomposition of a 2^n x 2^n table into four quadrants.
- Each quadrant is recursively filled in a specific order (top-left, bottom-right, bottom-left, top-right).
- The mapping between coordinates and numbers, or vice versa, uses bit manipulation.

Time Complexity: O(q * n), where q is the number of queries and n is the size parameter.
Space Complexity: O(1) excluding output storage.

This problem involves navigating a recursively filled 2^n x 2^n table. 
The approach leverages bit manipulation to determine how a cell's coordinates or a number maps 
to its position in the recursive structure.
"""

def __Main__():
    T = int(input())
    outs = []
    for _ in range(T):
        n = int(input())
        for _ in range(int(input())):
            f = list(input().split())
            if f[0] == "->":
                x, y = int(f[1]) - 1, int(f[2]) - 1  # Convert to 0-based indexing
                d = 0
                for i in range(n):
                    nx, ny = x >> i & 1, y >> i & 1       # Extract i-th bit of x and y
                    nd = (nx * 2) ^ (ny * 3)             # Combine the bits according to specific rule
                    d |= nd << (2 * i)                   # Place result in appropriate position
                outs.append(str(d + 1))                  # Convert back to 1-based
            else:
                d = int(f[1]) - 1                        # Convert to 0-based
                x, y = 0, 0
                for i in range(n):
                    nd = d >> (2 * i) & 3                # Extract 2-bit chunk from d
                    nx, ny = (nd & 1) ^ (nd >> 1), nd & 1 # Decode bits back to x,y components
                    x |= nx << i                         # Build x coordinate
                    y |= ny << i                         # Build y coordinate
                outs.append(f"{x + 1} {y + 1}")          # Convert to 1-based indexing
    print("\n".join(map(str, outs)))


if __name__ == "__main__":
    __Main__()


# https://github.com/VaHiX/codeForces/