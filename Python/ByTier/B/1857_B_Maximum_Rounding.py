# Problem: CF 1857 B - Maximum Rounding
# https://codeforces.com/contest/1857/problem/B

"""
Maximum Rounding

Algorithm:
- For each number, we simulate the rounding process from right to left
- We keep track of the carry (c) and the position where rounding occurs (behind)
- For each digit from right to left:
  - If the digit plus carry is >= 5, we round up and set carry = 1
  - Otherwise, carry = 0
- After identifying the rounding position, we construct the result:
  - If rounding position is at the end (no digits rounded), return original
  - If rounding position is at the beginning (first digit rounded), return 1 followed by zeros
  - Otherwise, increment the digit at rounding position and fill the rest with zeros

Time Complexity: O(n) where n is the length of the input string
Space Complexity: O(n) for storing the result strings
"""

ans = []
for _ in range(int(input())):
    s = input()
    n = len(s)
    c, behind = 0, n
    for i in range(n - 1, -1, -1):
        if int(s[i]) + c >= 5:
            c = 1
            behind = i
        else:
            c = 0
    if behind == n:
        ans.append(s)
    elif behind == 0:
        ans.append("1" + "0" * n)
    else:
        ans.append(s[: behind - 1] + str(int(s[behind - 1]) + 1) + "0" * (n - behind))
for i in ans:
    print(i)


# https://github.com/VaHiX/CodeForces/