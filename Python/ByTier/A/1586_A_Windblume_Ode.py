# Problem: CF 1586 A - Windblume Ode
# https://codeforces.com/contest/1586/problem/A

"""
Algorithm: Windblume Ode
Purpose: Find the largest subset of an array whose sum is a composite number.
Techniques:
- Prime checking using trial division
- Greedy selection of elements to ensure sum is composite
Time Complexity: O(n * sqrt(S)) where S is the sum of all elements, due to prime checking
Space Complexity: O(n) for storing the result subset indices

The algorithm works as follows:
1. Calculate the total sum of the array.
2. If the sum is composite, return the entire array.
3. If the sum is prime, remove one odd element (if exists) to make the sum composite.
"""

import os
import sys
from io import BytesIO

sys.stdin = BytesIO(os.read(0, os.fstat(0).st_size))
f = sys.stdin
if os.environ.get("USER") == "loic":
    f = open("data.in")
line = lambda: f.readline().split()


def write(w):
    sys.stdout.write(w)
    sys.stdout.write("\n")


def is_prime(n):
    i = 2
    while i * i <= n:
        if n % i == 0:
            return False
        i += 1
    return True


def solve():
    B = []
    s = sum(A)
    if is_prime(s):  # If total sum is prime
        j = -1
        # Find the first odd number in the array
        for i in range(N):
            if A[i] % 2 == 1:
                j = i
                break
        # If an odd number exists, remove it to make sum composite
        # Build subset excluding the first odd number
        for i in range(j):
            B.append(i + 1)
        for i in range(j + 1, N):
            B.append(i + 1)
    else:
        # If sum is already composite, include all numbers
        B = list(i + 1 for i in range(N))
    return str(str(len(B)) + "\n" + " ".join(str(v) for v in B))


T = int(line()[0])
for test in range(1, T + 1):
    N = int(line()[0])
    A = list(map(int, line()))
    write(solve())
f.close()


# https://github.com/VaHiX/CodeForces/