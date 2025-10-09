# Problem: CF 2098 C - Sports Betting
# https://codeforces.com/contest/2098/problem/C

# C. Sports Betting
# Problem Description:
# Vadim makes bets with students on specific days. For each day a_i, he predicts
# the boarding process for days a_i+1 and a_i+2. The goal is to determine if there
# exists a strategy that guarantees at least one correct prediction for some student.
#
# Approach:
# - Sort the input days.
# - Use a greedy approach to check whether we can assign predictions to ensure
#   at least one correct guess among all students.
# - Track counts of consecutive days and determine if a valid pattern allows
#   for guaranteeing success.
#
# Time Complexity: O(n log n) due to sorting, where n is the number of students
# Space Complexity: O(1) as we only use constant extra space

from sys import stdin

input = lambda: stdin.readline().rstrip()
ri = lambda: int(input())
rl = lambda: list(map(int, input().split()))
T = ri()
for _ in range(T):
    n = ri()
    a = rl()
    a.sort()
    last, cur = 0, [0, 0]
    flg = 0
    for i in a:
        if i == last:
            # Increment count of current value
            cur[1] += 1
            # Check if enough predictions can be made to guarantee one correct
            if cur[1] + cur[0] * 2 >= 4:
                flg = 1
                break
        else:
            # Transition to new value, compute previous group's contribution
            # If the new value is not consecutive, reset to zero
            cur[0] = (cur[1] + cur[0]) // 2 if last + 1 == i else 0
            # Set new count for current value
            cur[1] = 1
            last = i
            # Check again after update
            if cur[1] + cur[0] * 2 >= 4:
                flg = 1
                break
    print(["No", "Yes"][flg])


# https://github.com/VaHiX/codeForces/