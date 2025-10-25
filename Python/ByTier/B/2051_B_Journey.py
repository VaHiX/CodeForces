# Problem: CF 2051 B - Journey
# https://codeforces.com/contest/2051/problem/B

"""
B. Journey

Purpose:
This code determines the day on which Monocarp completes his hiking journey,
where he walks a specific pattern of distances (a, b, c, a, b, c, ...) until the total distance reaches at least n kilometers.

Algorithm/Techniques:
- Simulate the pattern of walking distances: a, b, c repeated cyclically.
- Use integer division to quickly calculate complete cycles of 3 days.
- Handle remaining days linearly to determine when the total distance meets or exceeds n.

Time Complexity: O(1) - The loop runs at most 3 times (for 3 days), making it constant time per test case.
Space Complexity: O(1) - Only a fixed number of variables are used regardless of input size.

Input Format:
- First line: t (number of test cases)
- Each test case: n, a, b, c (distance goals and walking pattern)

Output Format:
- For each test case, output the day number on which total distance reaches at least n.
"""

for _ in range(int(input())):
    n, a, b, c = map(int, input().split())  # Read n, a, b, c from input
    q, n = divmod(n, a + b + c)  # Calculate complete cycles and remaining distance
    q *= 3  # Each complete cycle is 3 days
    for e in [a, b, c]:  # Iterate through the pattern (a, b, c)
        if n > 0:  # If we haven't reached target yet
            n -= e  # Subtract current day's distance
            q += 1  # Increment day counter
    print(q)  # Output the final day number


# https://github.com/VaHiX/codeForces/