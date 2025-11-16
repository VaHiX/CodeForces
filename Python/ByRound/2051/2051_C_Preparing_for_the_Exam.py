# Problem: CF 2051 C - Preparing for the Exam
# https://codeforces.com/contest/2051/problem/C

"""
C. Preparing for the Exam

Algorithm:
- For each test case, we process n, m, k and three lines of input.
- The list of questions Monocarp knows is stored in a set for O(1) lookup.
- Each question list corresponds to one of m lists, where exactly one question from [1, n] is missing.
- We precompute the sum of all possible questions (1 + 2 + ... + n) as 'qs'.
- For each query (list), we compute the sum of the questions in that list and compare it with total sum minus the missing question index.
- Special cases:
    - If k == n, then Monocarp knows all questions => answer is "1" * m.
    - If k <= n - 2, then Monocarp doesn't know enough to pass any list => answer is "0" * m.

Time Complexity: O(n + m) per test case
Space Complexity: O(n + m) per test case

"""
lines = [list(map(int, line.strip().split())) for line in open(0).readlines()[1:]]
t = len(lines)
for i in range(0, t, 3):
    n, m, k = lines[i]
    # Convert the known questions to a set for fast lookup
    ans = sum(lines[i + 2])
    # Compute sum of all possible questions from 1 to n
    qs = n * (n + 1) // 2
    if k == n:
        # Monocarp knows all questions => he will pass every list
        print("1" * m)
    elif k <= n - 2:
        # Monocarp doesn't know enough to pass any list
        print("0" * m)
    else:
        # For each question list, determine if Monocarp passes
        for mq in lines[i + 1]:
            # If sum of questions in this list matches total minus the missing one,
            # then he knows all the questions in that list
            if qs - mq == ans:
                print("1", end="")
            else:
                print("0", end="")
        print()  # Newline after each test case


# https://github.com/VaHiX/codeForces/