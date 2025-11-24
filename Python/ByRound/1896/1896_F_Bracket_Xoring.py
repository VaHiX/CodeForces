# Problem: CF 1896 F - Bracket Xoring
# https://codeforces.com/contest/1896/problem/F

"""
Algorithm: Bracket Xoring
Approach:
1. The problem involves transforming a binary string of length 2n to all zeros using operations on balanced bracket sequences.
2. Each operation selects a balanced bracket sequence of length 2n, and for each open bracket, it toggles a range in the string.
3. The key insight is that we must ensure we can pair up the 1s in the string.
4. We check for the conditions where transformation is impossible.
5. The algorithm constructs two bracket sequences to toggle the necessary ranges to get all zeros.

Time Complexity: O(n) for each test case, as we do linear operations on the input.
Space Complexity: O(n) for storing auxiliary arrays and bracket sequences.

The code handles:
- Checking impossibility conditions
- Constructing balanced bracket sequences based on 1 positions
- Outputting required operations
"""

for _ in range(int(input())):
    n = int(input())
    s = list(map(int, input()))
    if s.count(0) % 2 or (s[0] + s[-1]) % 2:
        print(-1)
        continue
    i = s[1:-1]
    n -= 1
    b = [0] * (2 * n)
    c = [0] * (2 * n)
    d = []
    for j in range(2 * n):
        if i[j] == 1:
            d.append(j)
    for j in range(0, len(d), 2):
        l, r = d[j], d[j + 1]
        for k in range(l, r):
            if k % 2 == l % 2:
                b[k] = b[k + 1] = 1
            else:
                c[k] = c[k + 1] = 1
    b = [1] + b + [1]
    c = [1] + c + [1]
    sb = ["("]
    for i in range(1, len(b)):
        if b[i] == b[i - 1]:
            if sb[-1] == "(":
                sb.append(")")
            else:
                sb.append("(")
        else:
            sb.append(sb[-1])
    sc = ["("]
    for i in range(1, len(c)):
        if c[i] == c[i - 1]:
            if sc[-1] == "(":
                sc.append(")")
            else:
                sc.append("(")
        else:
            sc.append(sc[-1])
    x = "(" + "()" * n + ")"
    if s[0]:
        print(3)
        print("".join(sb))
        print("".join(sc))
        print(x)
    else:
        print(2)
        print("".join(sb))
        print("".join(sc))


# https://github.com/VaHiX/CodeForces/