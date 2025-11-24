# Problem: CF 2137 C - Maximum Even Sum
# https://codeforces.com/contest/2137/problem/C

"""
C. Maximum Even Sum

Purpose:
This code solves a problem where we are given two integers a and b. We must choose an integer k such that b is divisible by k, then simultaneously multiply a by k and divide b by k. The goal is to find the maximum possible even value of a+b. If it's impossible to make a+b even, we output -1.

Algorithms/Techniques:
- Math-based approach: Iterating over divisors of b to find optimal k
- Greedy logic: Try different valid values of k to maximize a+b while ensuring it's even
- Modular arithmetic: Check parity to determine if the result is even

Time Complexity:
O(sqrt(b)) per test case, due to iterating through all divisors of b.

Space Complexity:
O(1), as we only use a constant amount of extra space (excluding input/output lists).

"""

t = int(input())  # Read number of test cases
l = []  # List to store results for each test case
for i in range(t):
    a, b = map(int, input().split())  # Read integers a and b
    
    if b % 2 == 0:  # If b is even
        k = b // 2  # Set k to half of b
    else:  # If b is odd
        k = b  # Set k to b itself
    
    # Check if the sum a*k + b//k is even
    if (a * k + b // k) % 2 != 0:
        l.append(-1)  # If not even, append -1
    else:
        l.append(a * k + b // k)  # Otherwise, append the calculated sum

for i in range(len(l)):  # Print results for each test case
    print(l[i])


# https://github.com/VaHiX/codeForces/