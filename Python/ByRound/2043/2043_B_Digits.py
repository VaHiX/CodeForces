# Problem: CF 2043 B - Digits
# https://codeforces.com/contest/2043/problem/B

# B. Digits
# time limit per test1 second
# memory limit per test256 megabytes
# Artem wrote the digit d on the board exactly n! times in a row. So, he got the number ddddddd…ddd (exactly n! digits).
# Now he is curious about which odd digits from 1 to 9 divide the number written on the board.
# Algorithms/Techniques: Mathematical properties of divisibility
# Time Complexity: O(1) - constant time operations for each test case
# Space Complexity: O(1) - only storing a fixed number of results

for s in [*open(0)][1:]:
    n, d = map(int, s.split())
    print(
        1,  # Always include 1 (all numbers are divisible by 1)
        *[3] * (n > 2 or d % 3 < 1)  # Include 3 if n>2 OR d is divisible by 3
        + [5] * (d == 5)  # Include 5 if d equals 5
        + [7] * (n > 2 or d == 7)  # Include 7 if n>2 OR d equals 7
        + [9] * (d > 8 or d % 3 < 1 < n - 1 or n > 5)  # Include 9 based on complex condition
    )


# https://github.com/VaHiX/codeForces/