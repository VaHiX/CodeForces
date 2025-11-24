# Problem: CF 2052 E - Expression Correction
# https://codeforces.com/contest/2052/problem/E

"""
E. Expression Correction

Purpose:
This code solves an expression correction puzzle where:
- An equality containing addition and subtraction operations is given.
- The goal is to determine if it's correct, or if one digit can be moved to make it correct.
- If no single digit move makes it correct, output "Impossible".

Algorithms/Techniques:
1. Parse expressions into numbers and operators using the eval function.
2. Validate number format (no leading zeros except for "0").
3. Evaluate expressions and check equality.
4. If incorrect, try removing each digit and inserting it in all valid positions to find a correction.

Time Complexity: O(n^3) where n is the length of input string due to:
- Parsing and evaluation: O(n)
- Trying all digit moves: O(n^2) * checking validity per move: O(n)

Space Complexity: O(n) for storing parsed numbers and operators.
"""

def eval(s):
    # Check for edge cases: empty string or starting/ending with operator
    if len(s) == 0 or s[0] == "+" or s[-1] == "+" or s[0] == "-" or s[-1] == "-":
        return False, 0
    
    # Parse numbers and operators
    d = [""]
    op = [1]
    for c in s:
        if c == "+":
            op.append(1)
            d.append("")
        elif c == "-":
            op.append(-1)
            d.append("")
        else:
            d[-1] += c
    
    sm = 0
    for i in range(len(d)):
        # Validate number format: empty or length > 10
        if d[i] == "" or len(d[i]) > 10:
            return False, 0
        # Check for leading zeros (except "0")
        if d[i][0] == "0" and len(d[i]) > 1:
            return False, 0
        sm += int(d[i]) * op[i]
    return True, sm


def test(s):
    l, r = s.split("=")
    pl, nl = eval(l)  # Parse left side
    pr, nr = eval(r)  # Parse right side
    return pl and pr and nl == nr  # Return True if both sides valid and equal


s = input()
if test(s):
    print("Correct")
else:
    for i in range(len(s)):
        if s[i] != "+" and s[i] != "-":  # Only consider digits
            t = s[:i] + s[i + 1 :]  # Remove digit at position i
            for j in range(len(s)):  # Try inserting at every position
                q = t[:j] + s[i] + t[j:]  # Insert the removed digit
                if test(q):
                    print(q)
                    exit()
    print("Impossible")


# https://github.com/VaHiX/codeForces/