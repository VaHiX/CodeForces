# Problem: CF 1453 A - Cancel the Trains
# https://codeforces.com/contest/1453/problem/A

"""
Algorithm: Cancel the Trains
Techniques: Set operations, counting intersections

Purpose:
This program determines the minimum number of trains to cancel to prevent all crashes.
Trains from bottom (1-100) and left (1-100) ends move linearly in 2D space.
A crash occurs when two trains occupy the same position (x,y) at the same time T.
For i-th train starting from bottom at (i,0), it's at (i,T) after T minutes.
For j-th train starting from left at (0,j), it's at (T,j) after T minutes.
They crash if i = T and T = j, which means i = j.

Time Complexity: O(n + m) per test case
Space Complexity: O(n + m) per test case

Input Format:
- t test cases
- For each test case: n, m followed by two lines of train numbers

Output Format:
Minimum number of trains to cancel to prevent crashes
"""

for _ in range(int(input())):  # Read number of test cases
    input()  # Skip empty line
    a = set(map(int, input().split()))  # Set of trains from bottom end
    # Count how many trains from left end are also in bottom set (crashes)
    print(sum(int(x) in a for x in input().split()))


# https://github.com/VaHiX/codeForces/