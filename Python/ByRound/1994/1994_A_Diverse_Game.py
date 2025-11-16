# Problem: CF 1994 A - Diverse Game
# https://codeforces.com/contest/1994/problem/A

"""
Code Purpose:
This code solves the problem of constructing a new matrix b from a given matrix a such that:
- Matrix b contains all integers from 1 to n*m exactly once (same as a)
- For every position (i,j), a[i,j] != b[i,j]
The approach is to rotate the flattened matrix a by one position to create b. This works for all cases except when n*m = 1, where it's impossible.

Algorithms/Techniques:
- Flattening the matrix into a 1D array
- Performing a right rotation of the array by one element
- Reshaping the rotated array back into the original matrix dimensions
- Special handling for the edge case when n*m = 1

Time Complexity: O(n * m) per test case, as we iterate through all elements once to flatten and once to reconstruct.
Space Complexity: O(n * m) for storing the flattened array and output matrix.

"""
import sys


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    t = int(next(it))
    out_lines = []
    for _ in range(t):
        n = int(next(it))
        m = int(next(it))
        total = n * m

        flat = [int(next(it)) for _ in range(total)]
        if total == 1:
            out_lines.append("-1")
            continue

        # Rotate the flat array by one position to the right
        rotated = flat[-1:] + flat[:-1]

        # Reconstruct the matrix from rotated array
        for i in range(n):
            row = rotated[i * m : (i + 1) * m]
            out_lines.append(" ".join(map(str, row)))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/