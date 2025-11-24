# Problem: CF 1677 B - Tokitsukaze and Meeting
# https://codeforces.com/contest/1677/problem/B

"""
Algorithm/Techniques: Simulation with Optimized Row/Column Tracking
Time Complexity: O(n * m)
Space Complexity: O(m)

This solution simulates the process of students entering the meeting hall and
determines the number of good rows and columns after each student's entry.

Key observations:
- Students enter in order and sit in the 1st column of the 1st row.
- Existing students shift right, wrapping around to the next row.
- A row/column is "good" if it contains at least one serious student (1).
- The algorithm tracks:
  - vis: whether a column has at least one serious student
  - col: number of good columns
  - win: number of serious students in the current row
  - f: number of good rows (counted via tracking how many times a row had a 1)
"""

for _ in range(int(input())):
    n, m = map(int, input().split())
    a = list(input())

    vis = [False] * m
    col = win = 0
    f = [0] * m
    ans = []

    for i in range(n * m):
        # If this column hasn't been marked as good yet and the current student is serious
        if not vis[i % m] and a[i] == "1":
            vis[i % m] = True
            col += 1

        # If current student is serious, increment win (current row serious count)
        if a[i] == "1":
            win += 1
        # If previous student was in the same column but a different row, decrement win
        if i - m >= 0 and a[i - m] == "1":
            win -= 1
        # Update f[i%m] based on whether current row has any serious students
        f[i % m] += 1 if win else 0

        # Total good rows + columns
        ans.append(col + f[i % m])

    print(*ans)


# https://github.com/VaHiX/CodeForces/