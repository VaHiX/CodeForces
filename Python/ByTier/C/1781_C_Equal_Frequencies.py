# Problem: CF 1781 C - Equal Frequencies
# https://codeforces.com/contest/1781/problem/C

"""
Algorithm: Equal Frequencies
Purpose: Given a string s, find a balanced string t (all characters appear same number of times) 
         that differs from s in minimum number of positions.

Approach:
1. Count frequency of each character in s.
2. Try all possible numbers of unique characters (from 1 to 26) that could form a balanced string.
3. For each candidate number of unique characters k:
   - Calculate how many times each character should appear (t = n // k).
   - Calculate maximum characters we can reuse from original string under this configuration.
   - Keep track of the best configuration (maximum reuse).
4. Construct result string:
   - Assign characters from the best configuration to positions where they match.
   - Fill remaining positions with extra characters.

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing intermediate results and strings
"""

for i in range(int(input())):
    n = int(input())
    s = input()
    order = [0] * 26
    for a in s:
        order[ord(a) - 97] += 1
    order.sort(reverse=True)
    best = -1
    c = 0
    for k in range(1, 27):
        if n % k:  # Skip if n is not divisible by k
            continue
        t = n // k
        cur = 0
        for i in range(k):
            cur += min(t, order[i])
        if cur > best:
            best = cur
            c = k
    t = n // c
    print(n - best)
    extra = []
    best = [""] * n
    order = [0] * 26
    for a in s:
        order[ord(a) - 97] += 1
    order = sorted(zip(order, range(26)), reverse=True)
    for i in range(c):
        k, a = order[i]
        k = min(k, t)
        a = chr(a + 97)
        cur = 0
        j = 0
        while cur < k:
            if s[j] == a:
                best[j] = a
                cur += 1
            j += 1
        extra.extend([a] * (t - k))
    for i in range(n):
        if not best[i]:
            best[i] = extra[-1]
            extra.pop()
    print("".join(best))


# https://github.com/VaHiX/CodeForces/