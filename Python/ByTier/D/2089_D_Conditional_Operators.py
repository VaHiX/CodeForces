# Problem: CF 2089 D - Conditional Operators
# https://codeforces.com/contest/2089/problem/D

"""
D. Conditional Operators

Problem Description:
Given a binary string of length 2n+1, determine whether it's possible to insert n conditional operators (`?` and `:`) such that the resulting expression evaluates to 1. The expression must use parentheses appropriately and maintain the original character order.

Algorithm:
- The solution uses recursive backtracking logic with specific cases based on the first and last characters of the string.
- For strings that start or end with '1', special handling is applied for valid conditional expressions.
- For strings starting with '0', we try to match patterns where a conditional expression could produce 1 given the constraints.
- The `inter` helper function formats pairs of characters as "?:" sequences.

Time Complexity:
    O(n) per test case, amortized over all test cases due to the constraint on sum of n.
Space Complexity:
    O(n) for recursion stack and string building in worst case.

Techniques:
    - Greedy pattern matching with conditional evaluation
    - String manipulation with careful indexing
    - Recursive case handling based on first/last character values

"""

def inter(S):
    ans = []
    for i in range(0, len(S) - 1, 2):  # Iterate through pairs of characters
        ans.append(f"{S[i]}?{S[i + 1]}:")  # Format pair as "?:" sequence
    if len(S) & 1:  # If odd length, append last character separately
        ans.append(S[-1])
    return "".join(ans)


def solve(n, s):
    if s[-1] == "1":  # If the string ends with '1'
        if s == "101":  # Special case: trivially impossible to form a valid expression ending in 1
            return None
        if s[0] == "0":  # If string starts with '0', build prefix with leading '0'
            return f"0?({inter(s[1:-1])}):1"
        if s.startswith("11"):  # Start with "11", build a nested expression with two 1s
            return f"1?1:({inter(s[2:])})"
        return f"(1?0:{s[2]})?({inter(s[3:-1])}):1"  # General case involving nested pattern
    i = 0  # Find the first '1' after sequence of 0s
    while i < n and s[i] == "0":
        i += 2
    if i < n:
        j = i + 1  # Find the next '1'
        while j < n and s[j] == "0":
            j += 2
        if j < n:
            # Build expression for pattern found
            return f"{inter(s[:i])}(1?({inter(s[i + 1 : j])}1):{inter(s[j + 1 : -1])}0)"


for tc in range(int(input())):
    ans = solve(2 * int(input()) + 1, input())
    print(f"Yes\n{ans}" if ans else "No")


# https://github.com/VaHiX/codeForces/