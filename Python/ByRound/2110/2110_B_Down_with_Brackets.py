# Problem: CF 2110 B - Down with Brackets
# https://codeforces.com/contest/2110/problem/B

# B. Down with Brackets
# Algorithm: 
#   - For each test case, we simulate removing exactly one '(' and one ')' from the string.
#   - We compute a running sum (c) where '(' adds +1 and ')' subtracts +1 to track balance.
#   - To determine if after removal of one '(' and one ')', it's no longer balanced,
#     we check whether there exists any point in the string, such that after removing
#     one '(' and one ')', the cumulative sum during traversal goes negative.
#     This is equivalent to checking if at any position in a modified sequence,
#     we have c < 0 (which indicates a premature closing bracket).
# Time Complexity: O(n) per test case, where n is the length of string s
# Space Complexity: O(1), only using a few variables for computation

for s in [*open(0)][1:]:
    c = 0
    print("YNEOS"[all(c := c + 81 - 2 * ord(x) for x in s[:-2]) :: 2])


# https://github.com/VaHiX/codeForces/