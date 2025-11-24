# Problem: CF 1860 A - Not a Substring
# https://codeforces.com/contest/1860/problem/A

"""
Purpose: 
    This code solves the problem of finding a regular bracket sequence of length 2n 
    such that the given bracket sequence s does not occur as a contiguous substring.
    
    Algorithm:
        1. For a given input string s of length n, construct two candidate regular bracket sequences:
           - x = "(" * n + ")" * n  (n opening brackets followed by n closing brackets)
           - y = "()" * n           (alternating pairs of brackets)
        2. Check if s is not a substring of x. If so, output "YES" and x.
        3. Else, check if s is not a substring of y. If so, output "YES" and y.
        4. If both x and y contain s as a substring, output "NO".

    Time Complexity:
        O(n^2) per test case due to substring checks (in worst case, checking if s is in x or y).
        With up to 1000 test cases and n up to 50, this is acceptable.

    Space Complexity:
        O(n) per test case for storing the constructed strings x and y.

"""

T = int(input())


def solve():
    s = input()
    n = len(s)
    x = "(" * n + ")" * n  # Construct a string like "(())"
    y = "()" * n           # Construct a string like "()()...()"

    # Check if s is not a substring of x
    if s not in x:
        print("YES")
        print(x)
    # Check if s is not a substring of y
    elif s not in y:
        print("YES")
        print(y)
    else:
        print("NO")


for _ in range(T):
    solve()


# https://github.com/VaHiX/CodeForces/