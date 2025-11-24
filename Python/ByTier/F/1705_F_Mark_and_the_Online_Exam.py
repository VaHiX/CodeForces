# Problem: CF 1705 F - Mark and the Online Exam
# https://codeforces.com/contest/1705/problem/F

"""
Algorithm: Mark and the Online Exam
Purpose: Determine the answer key for a true-false exam by querying a grading system.
Technique: 
    - Use 3-question group comparisons to deduce individual answers.
    - First, query all T's to get baseline score.
    - Then, for each group of 3 questions, flip all to F and query to determine pattern.
    - After that, flip combinations to determine individual answer patterns.
    - Handle remaining 1 or 2 questions separately.
Time Complexity: O(n) - We make at most ~2n/3 queries.
Space Complexity: O(n) - We store the answer string and temporary data structures.
"""

import sys


def solve():
    n = int(input())
    s = ["T"] * n
    print("".join(s))
    sys.stdout.flush()
    tot1 = int(input())
    if tot1 == n:
        return
    res1 = []
    # Query all T's, then flip 3 at a time to F and check how many correct answers are lost
    for i in range(0, n, 3):
        if i + 2 < n:
            s[i] = s[i + 1] = s[i + 2] = "F"
            print("".join(s))
            sys.stdout.flush()
            res1.append(int(input()))
            if res1[-1] == n:
                return
            s[i] = s[i + 1] = s[i + 2] = "T"
    s = ["T"] * n
    # Second group, flip 2 of every 3 questions to F
    for i in range(0, n, 3):
        if i + 2 < n:
            s[i] = s[i + 2] = "F"
    print("".join(s))
    sys.stdout.flush()
    tot2 = int(input())
    if tot2 == n:
        return
    res2 = []
    # Third group, flip 1 of every 3 questions to F
    for i in range(0, n, 3):
        if i + 2 < n:
            s[i + 1] = s[i + 2] = "F"
            s[i] = "T"
            print("".join(s))
            sys.stdout.flush()
            res2.append(int(input()))
            if res2[-1] == n:
                return
            s[i] = s[i + 2] = "F"
            s[i + 1] = "T"

    ans = []
    # Decode the pattern from the response
    for i in range(n // 3):
        x = tot1 - res1[i]
        y = tot2 - res2[i]
        if (x, y) == (3, 0):
            ans.append("TTT")
        elif (x, y) == (1, 2):
            ans.append("FTT")
        elif (x, y) == (1, -2):
            ans.append("TFT")
        elif (x, y) == (-1, 0):
            ans.append("FFT")
        elif (x, y) == (1, 0):
            ans.append("TTF")
        elif (x, y) == (-1, 2):
            ans.append("FTF")
        elif (x, y) == (-1, -2):
            ans.append("TFF")
        elif (x, y) == (-3, 0):
            ans.append("FFF")
    res = n - n // 3 * 3

    if res == 1:
        s = ["T"] * n
        s[-1] = "F"
        print("".join(s))
        sys.stdout.flush()
        t = int(input())
        if t == n:
            return
        if t < tot1:
            ans.append("T")
        else:
            ans.append("F")
    if res == 2:
        s = ["T"] * n
        s[-2] = "F"
        print("".join(s))
        sys.stdout.flush()
        t = int(input())
        if t == n:
            return
        if t < tot1:
            ans.append("T")
        else:
            ans.append("F")
        s[-1] = "F"
        print("".join(s))
        sys.stdout.flush()
        t1 = int(input())
        if t1 == n:
            return
        if t1 < t:
            ans.append("T")
        else:
            ans.append("F")
    print("".join(ans))
    sys.stdout.flush()
    t = int(input())


solve()


# https://github.com/VaHiX/CodeForces/