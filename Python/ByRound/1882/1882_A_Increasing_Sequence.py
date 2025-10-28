# Problem: CF 1882 A - Increasing Sequence
# https://codeforces.com/contest/1882/problem/A

"""
Purpose: 
    Find the minimum possible value of the last element in a good sequence b, where:
    - Each b[i] is a positive integer
    - b[i] != a[i] for all i
    - b is strictly increasing
Algorithm/Techniques:
    - Greedy approach: For each position, assign the smallest possible integer that:
        * Is not equal to a[i]
        * Keeps the sequence strictly increasing
Time Complexity: O(n)
Space Complexity: O(n)
"""
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    b = []
    number = 1  # Start from 1 to ensure positive integers
    for i in range(n):
        if number != a[i]:  # If current number is not forbidden by a[i]
            b.append(number)  # Use it
        else:
            number += 1  # Skip the forbidden number
            b.append(number)  # Use the next available number
        number += 1  # Move to next candidate for the next element
    print(b[n - 1])  # Output the last element of the constructed sequence


# https://github.com/VaHiX/CodeForces/