# Problem: CF 1718 B - Fibonacci Strings
# https://codeforces.com/contest/1718/problem/B

"""
Algorithm: Semi-Fibonacci String Checker

Approach:
1. Generate Fibonacci sequence up to a large enough number (60 terms).
2. For each test case:
   - Determine if the total number of characters can form a Fibonacci sum.
   - Try to assign character frequencies to Fibonacci numbers in reverse order.
   - Check if we can distribute all characters according to Fibonacci block sizes.

Time Complexity: O(m * k * log k + t * k * log k)
Where m is the number of Fibonacci terms generated (60), k is the alphabet size, and t is the number of test cases.
Space Complexity: O(m + k)
Where m is the size of Fibonacci array and k is the size of character frequency array.
"""

m = 60
fib = [1, 1]
for i in range(m):
    fib.append(fib[-1] + fib[-2])  # Generate Fibonacci sequence


def slv():
    n = int(input())
    _a = list(map(int, input().split()))
    a = []
    for i in range(n):
        a.append([_a[i], i])  # Store character counts with their indices
    j = -1
    for i in range(m):
        if sum(_a) == sum(fib[0 : i + 1]):  # Check if total chars match a Fibonacci sum
            j = i
            break
    if j == -1:
        print("no")  # No valid Fibonacci sum found
    else:
        _lst = -1  # Tracks last assigned character
        pok = 1    # Flag to indicate success/failure
        for k in range(j, -1, -1):  # Process in reverse Fibonacci order
            a.sort()  # Sort by character count
            need = fib[k]
            for i in range(n - 1, -1, -1):  # Iterate from largest count to smallest
                if a[i][1] == _lst:
                    continue  # Skip if already used this character
                if a[i][0] >= need and need:
                    x = min(need, a[i][0])
                    a[i][0] -= x
                    need -= x
                    _lst = a[i][1]
            if need > 0:  # Not enough characters to satisfy current Fibonacci number
                pok = 0
                break
        print("YES" if pok else "NO")


t = int(input())
for _ in range(t):
    slv()


# https://github.com/VaHiX/CodeForces/