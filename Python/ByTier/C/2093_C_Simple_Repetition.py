# Problem: CF 2093 C - Simple Repetition
# https://codeforces.com/contest/2093/problem/C

"""
C. Simple Repetition
time limit per test1 second
memory limit per test256 megabytes

Pasha loves prime numbers! Once again, in his attempts to find a new way to generate prime numbers, he became interested in an algorithm he found on the internet:
To obtain a new number y, repeat k times the decimal representation of the number x (without leading zeros).
For example, for x=52 and k=3, we get y=525252, and for x=6 and k=7, we get y=6666666.

The task is to determine whether the resulting number y is prime.

Algorithm:
- For each test case, given x and k:
    - If k > 1 or x == 1, check if y can be prime.
      - If k == 2 and x == 1: output YES (since 11 is prime)
      - Otherwise: output NO
    - If k == 1:
        - Check if x itself is a prime number using trial division up to sqrt(x).
        - Output YES if x is prime, otherwise NO

Time Complexity: O(sqrt(x) * t) where t is the number of test cases and x <= 10^9.
Space Complexity: O(1), only using constant extra space.
"""

n = int(input())
while n != 0:
    n -= 1
    x, k = map(int, input().split())
    # If k != 1 or x == 1, further checks are needed
    if k != 1 or x == 1:
        # Special case: if k == 2 and x == 1, then y = 11 which is prime
        if k == 2 and x == 1:
            print("YES")
            continue
        print("NO")
        continue
    # If k == 1, we check primality of x directly
    isPrime = True
    for i in range(2, int(x**0.5) + 1):
        if x % i == 0:
            isPrime = False
            break
    if isPrime:
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/codeForces/