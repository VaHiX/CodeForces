# Problem: CF 1912 E - Evaluate It and Back Again
# https://codeforces.com/contest/1912/problem/E

"""
Algorithm/Technique:
This solution constructs an arithmetic expression that evaluates to p when read left-to-right and q when read right-to-left.
It uses pre-defined patterns for positive and negative numbers to build the expression.
The core idea is to manipulate the structure of the expression such that the evaluation from both sides gives different results.
For positive numbers, we use a pattern that ends with "+0+" to ensure the structure remains valid.
For negative numbers, we reverse the pattern and apply similar logic.
The algorithm ensures:
- Expression length is within 1000 characters.
- No leading zeros except for the number '0'.
- All operations follow standard precedence.
- Unary operators are not used.

Time Complexity: O(1)
Space Complexity: O(1)
"""

p, q = input().split()

# Predefined patterns for positive and negative number expressions
expplus = "_*0+_*21+_*9+_*0-_*4+_*0-_*22-_*0-_*3-_*0"
expminus = "_*0-_*21-_*9-_*0+_*4-_*0+_*22+_*0+_*3+_*0"

r = 0  # flag to check if p ends with '0'
s = 0  # flag to check if q ends with '0'

# Adjust p if it ends with '0' to avoid edge case in processing
if p[-1] == "0":
    p = str(int(p) - 1)
    r = 1

# Adjust q if it ends with '0' to avoid edge case in processing
if q[-1] == "0":
    q = str(int(q) - 1)
    s = 1

ans = ""

# Select appropriate pattern based on sign of p
if p[0] != "-":
    ans += expplus.replace("_", p)  # Use positive pattern
else:
    ans += expminus.replace("_", p[1:])  # Use negative pattern (skip the minus sign)

ans += "+0+"  # Append a safe operation to ensure structure

# Select appropriate pattern based on sign of q and reverse it for right-to-left parsing
if q[0] != "-":
    ans += expplus.replace("_", q)[::-1]  # Use positive pattern reversed
else:
    ans += expminus.replace("_", q[1:])[::-1]  # Use negative pattern reversed

# Handle the adjustment for p if it ended with '0'
if r == 1:
    ans += "+0+"
    ans += expplus.replace("_", "1")  # Add a small correction term

# Handle the adjustment for q if it ended with '0'
if s == 1:
    ans += "+0+"
    ans += expplus.replace("_", "1")[::-1]  # Add a small correction term reversed

print(ans)


# https://github.com/VaHiX/CodeForces/