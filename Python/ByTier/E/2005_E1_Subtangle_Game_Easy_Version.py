# Problem: CF 2005 E1 - Subtangle Game (Easy Version)
# https://codeforces.com/contest/2005/problem/E1

"""
Algorithm: Game Theory with Memoization (Minimax)
Time Complexity: O(l * n * m), where l is the length of array a, n and m are matrix dimensions
Space Complexity: O(l * n * m), for memoization table dp

This problem is a game theory problem where two players (Tsovak and Narek) take turns finding elements of an array in a matrix.
The game rules are:
1. Tsovak starts first.
2. Each player finds the current element of the array in the matrix.
3. After finding an element at (r, c), the next player must find the next element in the submatrix starting from (r+1, c+1) to (n, m).
4. If a player cannot find the required element or the submatrix is empty, the player loses.
5. Both players play optimally.

Approach:
We use recursive minimax with memoization:
- f(ind, r, c) returns True if the current player can win from state (ind, r, c).
- ind: current index in array a
- r, c: starting position for submatrix search
- Base cases:
  - If all elements are processed or submatrix is empty: current player loses (return 0)
- Memoization: store computed results to avoid recomputation
- For each valid state:
  - Try skipping positions (not taking any element, but this is not directly applicable here)
  - Try taking current element if it matches and recursively check if opponent loses in resulting subgame
"""

def f(ind, r, c, arr, st, dp):
    # Base case: if we've processed all elements or submatrix is empty, current player loses
    if ind == len(arr) or r == n or c == m:
        return 0
    # Check if result is already computed
    if (ind, r, c) in dp:
        return dp[(ind, r, c)]
    # Try moving right or down in the submatrix
    nt = f(ind, r + 1, c, arr, st, dp) or f(ind, r, c + 1, arr, st, dp)
    take = 0
    # If current cell matches the required element
    if st[r][c] == arr[ind]:
        # Take this element and move to subgame with next element
        take = not f(ind + 1, r + 1, c + 1, arr, st, dp)
    # If taking this element leads to a winning position for current player, or
    # moving forward leads to a winning position, then current player wins
    dp[(ind, r, c)] = take or nt
    return take or nt


t = int(input())
for _ in range(t):
    l, n, m = map(int, input().split())
    arr = [eval(x) for x in input().split()]
    st = []
    for _ in range(n):
        temp = [eval(x) for x in input().split()]
        st.append(temp)
    dp = {}
    ans = f(0, 0, 0, arr, st, dp)
    if ans == 1:
        print("T")
    else:
        print("N")


# https://github.com/VaHiX/CodeForces/