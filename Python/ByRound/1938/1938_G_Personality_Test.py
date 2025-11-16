# Problem: CF 1938 G - Personality Test
# https://codeforces.com/contest/1938/problem/G

# ====================================================================
# Purpose: Find a pair of students (a, b) such that a < b and they are 
#          similar based on at least k common questions with same answers.
#          If multiple pairs exist, choose the one with smallest b, 
#          and if still tied, largest a.
#
# Algorithm: 
#   - For each student (b), we track which questions they answered.
#   - For each answered question, we store the student index in a hash map 
#     indexed by (question_index * 26 + answer_char_index).
#   - When processing a new student, we check previous students who answered 
#     the same question with the same answer.
#   - Maintain a count of matching answers for each previous student.
#   - If count reaches k, we found a valid pair (a, b).
#
# Time Complexity: O(n * m * 26) where n is number of students, m is number of questions.
# Space Complexity: O(m * 26 + n) for storing the mapping and counts.
# ====================================================================

from sys import stdin


def solve():
    n, m, k = map(int, stdin.readline().split())
    # prev[key] stores list of student indices who answered question (key // 26) 
    # with answer (key % 26) + 'A'
    prev = [[] for i in range(m * 26)]
    # counts[a] keeps track of how many questions students a and b answered similarly
    counts = [0] * n

    for b in range(n):  # Process each student
        line = stdin.readline().strip()
        lim = -1  # To track the earliest valid candidate 'a' to avoid reprocessing
        for i, c in enumerate(line):  # For each question in current student's answers
            if c == ".":
                continue
            key = i * 26 + ord(c) - ord("A")  # Unique key for question and answer
            # Iterate backwards over students who answered same question with same answer
            for a in reversed(prev[key]):
                if a <= lim:  # Skip if already processed or invalid
                    break
                counts[a] += 1  # Increment counter for student a
                if counts[a] == k:  # Found k matches
                    lim = a  # Mark this as last valid a to avoid overcounting
                    break
            prev[key].append(b)  # Record current student for future matching
        
        # If we have a valid pair, output the 1-indexed indices
        if lim != -1:
            print(lim + 1, b + 1)
            return
        
        # Reset counts for next student
        for i in range(b):
            counts[i] = 0
    
    # If no pair found
    print(-1)


solve()


# https://github.com/VaHiX/CodeForces/