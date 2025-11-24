# Problem: CF 1970 A1 - Balanced Shuffle (Easy)
# https://codeforces.com/contest/1970/problem/A1

"""
Balanced Shuffle Algorithm

This code performs the "balanced shuffle" operation on a given balanced parentheses sequence.

The algorithm works as follows:
1. Compute the balance of the input sequence at each position.
2. Group characters by their balance level.
3. For each balance level, reverse the group and append to the result.

Time Complexity: O(n), where n is the length of the input string.
Space Complexity: O(n), for storing the groups and the result.

Algorithm Techniques:
- Prefix balance tracking
- Grouping by balance levels
- Reversal of groups for final ordering
"""

def solve():
    s = input().strip()
    len(s)
    current_balance = 0
    max_balance = 0
    # First pass: compute maximum balance to determine number of groups
    for char in s:
        if current_balance > max_balance:
            max_balance = current_balance
        if char == "(":
            current_balance += 1
        else:
            current_balance -= 1
    # Initialize groups for each balance level
    groups = [[] for _ in range(max_balance + 1)]
    current_balance = 0
    # Second pass: group characters by their balance level
    for char in s:
        groups[current_balance].append(char)
        if char == "(":
            current_balance += 1
        else:
            current_balance -= 1
    result = []
    # Build result by appending reversed groups from highest to lowest balance
    for i in range(max_balance + 1):
        result.extend(reversed(groups[i]))
    print("".join(result))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/