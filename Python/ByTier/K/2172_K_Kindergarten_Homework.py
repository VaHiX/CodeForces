# Problem: CF 2172 K - Kindergarten Homework
# https://codeforces.com/contest/2172/problem/K

"""
Number Search Puzzle Solver
Algorithm: Brute-force enumeration of all possible expressions in 8 directions from each cell
Time Complexity: O(n * m * (n + m) * log(max_value)) where max_value <= 10^6
Space Complexity: O(max_value) = O(10^6) = O(1) since it's bounded by a constant

The solution precomputes all valid expressions in the grid by:
1. Starting from each digit cell
2. Expanding in all 8 directions (horizontal, vertical, diagonal)
3. Building numbers and evaluating expressions with proper operator precedence
4. Counting occurrences of each evaluated value in a frequency array
"""

import sys

input = sys.stdin.readline

n, m, q = map(int, input().split())
X = [0 for _ in range(int(1e6 + 1))]  # Frequency array to store count of each possible value

S = [input().strip() for _ in range(n)]

# For each cell in the grid
for i in range(n):
    for jj in range(m):
        # Skip if current cell is an operator
        if S[i][jj] in "+*":
            continue
        
        # Initialize variables for expression evaluation
        cur = int(S[i][jj])  # Current number being built
        X[cur] += 1  # Count the single digit expression
        cv = 0  # Current value of expression so far
        lv = 0  # Last operand for multiplication
        la = 0  # Flag indicating if last operation was multiplication (1) or addition (0)
        lst = False  # Flag to check if last character was an operator
        
        # Expand right (horizontal)
        for j in range(jj + 1, m):
            if S[i][j] == "+":
                # If last was already an operator, break
                if lst:
                    break
                lst = True
                # If we have a multiplication result pending
                if la:
                    cv += lv * cur
                    cur = 0
                else:
                    cv += cur
                    lv = 0
                    cur = 0
                la = 0  # Reset multiplication flag
            elif S[i][j] == "*":
                if lst:
                    break
                lst = True
                if la:
                    lv *= cur
                    cur = 0
                else:
                    lv = cur
                    cur = 0
                la = 1  # Set multiplication flag
            else:
                # Continue building number
                cur = 10 * cur + int(S[i][j])
                val = cv
                if la:
                    val += lv * cur
                else:
                    val += cur
                # Only count if value is within bounds
                if val >= len(X):
                    break
                X[val] += 1
                lst = False  # Reset operator flag

        # Reset variables for next direction
        cur = int(S[i][jj])
        cv = 0
        lv = 0
        la = 0
        lst = False

        # Expand left (horizontal)
        for j in range(jj - 1, -1, -1):
            if S[i][j] == "+":
                if lst:
                    break
                lst = True
                if la:
                    cv += lv * cur
                    cur = 0
                else:
                    cv += cur
                    lv = 0
                    cur = 0
                la = 0
            elif S[i][j] == "*":
                if lst:
                    break
                lst = True
                if la:
                    lv *= cur
                    cur = 0
                else:
                    lv = cur
                    cur = 0
                la = 1
            else:
                cur = 10 * cur + int(S[i][j])
                val = cv
                if la:
                    val += lv * cur
                else:
                    val += cur
                if val >= len(X):
                    break
                X[val] += 1
                lst = False

        # Reset variables for next direction
        cur = int(S[i][jj])
        cv = 0
        lv = 0
        la = 0
        lst = False

        # Expand down (vertical)
        for ii in range(i + 1, n):
            if S[ii][jj] == "+":
                if lst:
                    break
                lst = True
                if la:
                    cv += lv * cur
                    cur = 0
                else:
                    cv += cur
                    lv = 0
                    cur = 0
                la = 0
            elif S[ii][jj] == "*":
                if lst:
                    break
                lst = True
                if la:
                    lv *= cur
                    cur = 0
                else:
                    lv = cur
                    cur = 0
                la = 1
            else:
                cur = 10 * cur + int(S[ii][jj])
                val = cv
                if la:
                    val += lv * cur
                else:
                    val += cur
                if val >= len(X):
                    break
                X[val] += 1
                lst = False

        # Reset variables for next direction
        cur = int(S[i][jj])
        cv = 0
        lv = 0
        la = 0
        lst = False

        # Expand up (vertical)
        for ii in range(i - 1, -1, -1):
            if S[ii][jj] == "+":
                if lst:
                    break
                lst = True
                if la:
                    cv += lv * cur
                    cur = 0
                else:
                    cv += cur
                    lv = 0
                    cur = 0
                la = 0
            elif S[ii][jj] == "*":
                if lst:
                    break
                lst = True
                if la:
                    lv *= cur
                    cur = 0
                else:
                    lv = cur
                    cur = 0
                la = 1
            else:
                cur = 10 * cur + int(S[ii][jj])
                val = cv
                if la:
                    val += lv * cur
                else:
                    val += cur
                if val >= len(X):
                    break
                X[val] += 1
                lst = False

        # Reset variables for next direction
        cur = int(S[i][jj])
        cv = 0
        lv = 0
        la = 0
        lst = False

        # Expand down-right diagonal
        for pl in range(1, n + 1):
            if i + pl >= n or jj + pl >= m:
                break
            if S[i + pl][jj + pl] == "+":
                if lst:
                    break
                lst = True
                if la:
                    cv += lv * cur
                    cur = 0
                else:
                    cv += cur
                    lv = 0
                    cur = 0
                la = 0
            elif S[i + pl][jj + pl] == "*":
                if lst:
                    break
                lst = True
                if la:
                    lv *= cur
                    cur = 0
                else:
                    lv = cur
                    cur = 0
                la = 1
            else:
                cur = 10 * cur + int(S[i + pl][jj + pl])
                val = cv
                if la:
                    val += lv * cur
                else:
                    val += cur
                if val >= len(X):
                    break
                X[val] += 1
                lst = False

        # Reset variables for next direction
        cur = int(S[i][jj])
        cv = 0
        lv = 0
        la = 0
        lst = False

        # Expand down-left diagonal
        for pl in range(1, n + 1):
            if i + pl >= n or jj - pl < 0:
                break
            if S[i + pl][jj - pl] == "+":
                if lst:
                    break
                lst = True
                if la:
                    cv += lv * cur
                    cur = 0
                else:
                    cv += cur
                    lv = 0
                    cur = 0
                la = 0
            elif S[i + pl][jj - pl] == "*":
                if lst:
                    break
                lst = True
                if la:
                    lv *= cur
                    cur = 0
                else:
                    lv = cur
                    cur = 0
                la = 1
            else:
                cur = 10 * cur + int(S[i + pl][jj - pl])
                val = cv
                if la:
                    val += lv * cur
                else:
                    val += cur
                if val >= len(X):
                    break
                X[val] += 1
                lst = False

        # Reset variables for next direction
        cur = int(S[i][jj])
        cv = 0
        lv = 0
        la = 0
        lst = False

        # Expand up-right diagonal
        for pl in range(1, n + 1):
            if i - pl < 0 or jj + pl >= m:
                break
            if S[i - pl][jj + pl] == "+":
                if lst:
                    break
                lst = True
                if la:
                    cv += lv * cur
                    cur = 0
                else:
                    cv += cur
                    lv = 0
                    cur = 0
                la = 0
            elif S[i - pl][jj + pl] == "*":
                if lst:
                    break
                lst = True
                if la:
                    lv *= cur
                    cur = 0
                else:
                    lv = cur
                    cur = 0
                la = 1
            else:
                cur = 10 * cur + int(S[i - pl][jj + pl])
                val = cv
                if la:
                    val += lv * cur
                else:
                    val += cur
                if val >= len(X):
                    break
                X[val] += 1
                lst = False

        # Reset variables for next direction
        cur = int(S[i][jj])
        cv = 0
        lv = 0
        la = 0
        lst = False

        # Expand up-left diagonal
        for pl in range(1, n + 1):
            if i - pl < 0 or jj - pl < 0:
                break
            if S[i - pl][jj - pl] == "+":
                if lst:
                    break
                lst = True
                if la:
                    cv += lv * cur
                    cur = 0
                else:
                    cv += cur
                    lv = 0
                    cur = 0
                la = 0
            elif S[i - pl][jj - pl] == "*":
                if lst:
                    break
                lst = True
                if la:
                    lv *= cur
                    cur = 0
                else:
                    lv = cur
                    cur = 0
                la = 1
            else:
                cur = 10 * cur + int(S[i - pl][jj - pl])
                val = cv
                if la:
                    val += lv * cur
                else:
                    val += cur
                if val >= len(X):
                    break
                X[val] += 1
                lst = False

# Process queries
for _ in range(q):
    print(X[int(input())])


# https://github.com/VaHiX/CodeForces/