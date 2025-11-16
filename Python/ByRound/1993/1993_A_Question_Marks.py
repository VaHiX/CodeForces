# Problem: CF 1993 A - Question Marks
# https://codeforces.com/contest/1993/problem/A

"""
Purpose: To determine the maximum number of correct answers Tim can achieve in a test with 4n questions,
         where each of the four options (A, B, C, D) has exactly n correct answers. 
         '?' indicates unanswered questions and can be treated as any option to maximize score.

Algorithms/Techniques: Greedy approach - For each answer option (A, B, C, D), 
                       count how many there are in the input string and 
                       take the minimum of that count and n (the number of correct answers per option).

Time Complexity: O(n) per test case, since we count occurrences of each character in the string of length 4n.
Space Complexity: O(1), as we only use a constant amount of extra space for counting variables.
"""

for _ in range(int(input())):
    n = int(input())
    s = input()
    count = 0
    # For each of the four options A, B, C, D:
    # If the number of occurrences in the string exceeds n, use n (as there are only n correct answers for that option).
    # Otherwise, use the actual count from the string.
    if s.count("A") > n:
        count += n
    else:
        count += s.count("A")
    if s.count("B") > n:
        count += n
    else:
        count += s.count("B")
    if s.count("C") > n:
        count += n
    else:
        count += s.count("C")
    if s.count("D") > n:
        count += n
    else:
        count += s.count("D")
    print(count)


# https://github.com/VaHiX/CodeForces/