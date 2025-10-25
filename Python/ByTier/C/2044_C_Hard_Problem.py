# Problem: CF 2044 C - Hard Problem
# https://codeforces.com/contest/2044/problem/C

# C. Hard Problem
# time limit per test1 second
# memory limit per test256 megabytes
#
# Ball is the teacher in Paperfold University. The seats of his classroom are arranged in
# 2 rows with m seats each.
# Ball is teaching a+b+c monkeys, and he wants to assign as many monkeys to a seat as possible. 
# Ball knows that a of them only want to sit in row 1,
# b of them only want to sit in row 2, and c of them have no preference. 
# Only one monkey may sit in each seat, and each monkey's preference must be followed if it is seated.
# What is the maximum number of monkeys that Ball can seat?
#
# Algorithm:
# - First assign all mandatory monkeys (a from row 1, b from row 2)
# - Then calculate how many seats are left in each row
# - Use remaining monkeys with no preference optimally to fill up rows
# - Greedily allocate remaining c monkeys to maximize total seating
#
# Time Complexity: O(1) per test case
# Space Complexity: O(1)

for s in [*open(0)][1:]:
    m, a, b, c = map(int, s.split())
    # Assign as many as possible from the mandatory rows (a in row 1, b in row 2)
    # Take min of available seats and required monkeys for each row
    x = min(a, m) + min(b, m)  # total assigned in both rows
    # Now, how many more can we place using the remaining monkeys with no preference?
    # The maximum extra that could be placed is limited by:
    #   - 2*m - x (total seats - already used)
    #   - c (remaining no preference monkeys)
    print(x + min(c, 2 * m - x))


# https://github.com/VaHiX/codeForces/