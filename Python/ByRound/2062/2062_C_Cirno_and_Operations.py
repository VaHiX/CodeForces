# Problem: CF 2062 C - Cirno and Operations
# https://codeforces.com/contest/2062/problem/C

"""
C. Cirno and Operations
Algorithms/Techniques: Simulation with difference sequences and reversing

Time Complexity: O(n^3) per test case, where n is the length of the sequence.
                 The outer loop runs up to n times, and each iteration involves
                 operations on a list of size up to n, leading to O(n^2) work
                 per iteration, and there are at most n iterations.

Space Complexity: O(n) for storing the sequence at each step.

The algorithm simulates all possible combinations of reversing and taking difference
sequences until the length of the array reduces to 1. It keeps track of the maximum
sum encountered during these operations.
"""

for _ in range(int(input())):  # Read number of test cases
    n = int(input())  # Read length of sequence
    a = list(map(int, input().split()))  # Read sequence elements
    ans = sum(a)  # Initialize answer with current sum
    
    while n > 1:  # Continue while array has more than one element
        n -= 1  # Reduce size by 1
        # Compute difference sequence: [a[i+1] - a[i] for i in range(n)]
        a = [a[i + 1] - a[i] for i in range(n)]
        # Update maximum sum seen so far
        ans = max(ans, abs(sum(a)))
    
    print(ans)  # Print result for current test case


# https://github.com/VaHiX/codeForces/