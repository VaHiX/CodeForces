# Problem: CF 1847 E - Triangle Platinum?
# https://codeforces.com/contest/1847/problem/E

"""
Algorithm: Triangle Platinum Solver
Purpose: Determine hidden integers a_1, a_2, ..., a_n (each in [1,4]) using triangle area queries.
Approach:
1. For small n (<=8), brute force all combinations to find valid solutions.
2. For larger n:
   - Find a triple that forms a valid triangle with a specific area (using lookup).
   - Use this triple to deduce remaining values based on queries with other indices.
   - Handle special cases based on triangle inequalities and area calculations.

Time Complexity: O(4^n) in worst case for brute force, but with optimizations and early termination
Space Complexity: O(n) for storing intermediate results and recursion stack
"""

import sys
from itertools import combinations
from random import sample

input = sys.stdin.buffer.readline


def ask(i, j, k):
    # Query the area of triangle formed by indices i, j, k
    print("?", i, j, k)
    sys.stdout.flush()
    return int(input())


def answer(a):
    # Output the result or -1 if impossible
    if a != -1:
        print("!", *a)
    else:
        print("! -1")
    sys.stdout.flush()


def area(a, b, c):
    # Calculate area squared using Heron's formula
    p = a + b + c
    A = p * (p - 2 * a) * (p - 2 * b) * (p - 2 * c)
    return A if A > 0 else 0


def find(n, areas, valid, s=[]):
    # Recursively find all valid combinations for small arrays
    if len(s) == n:
        work = True
        cur = 0
        for a, b, c in combinations(s, 3):
            if area(a, b, c) != areas[cur]:
                work = False
            cur += 1
        if work:
            valid.append(s.copy())
    else:
        for i in range(1, 5):
            s.append(i)
            find(n, areas, valid, s)
            s.pop()


def brute(a):
    # Brute force solution for small arrays
    areas = []
    for i, j, k in combinations(a, 3):
        areas.append(ask(i, j, k))
    valid = []
    find(len(a), areas, valid)
    if len(valid) == 1:
        return valid[0]
    else:
        return -1


n = int(input())

if n <= 8:
    # For small n, use brute force
    answer(brute(list(range(1, n + 1))))
else:
    # For larger n, use more advanced approach

    triple = []
    s = 0

    # Precompute areas for three equal sides
    trip_areas = {}
    for i in range(1, 5):
        trip_areas[area(i, i, i)] = i
    
    while not triple:
        # Randomly sample a triple and check if it forms a valid triangle
        trip = sample(range(1, n + 1), 3)
        A = ask(*trip)
        if A in trip_areas:
            triple = trip
            s = trip_areas[A]
            break

    if s > 1:
        # If s > 1, we can deduce the rest easier
        a = []
        get_s = {}
        for i in range(1, 5):
            get_s[area(s, s, i)] = i
        for i in range(1, n + 1):
            if i not in triple:
                # Query with two elements of triple and one element from others
                a.append(get_s[ask(triple[0], triple[1], i)])
            else:
                a.append(s)
        answer(a)
    else:
        # Special case where s == 1
        a = [1] * n
        gt1 = []

        # Find indices whose queries give 0 area (implying they are all 1)
        for i in range(1, n + 1):
            if i not in triple:
                A = ask(triple[0], triple[1], i)
                if A == 0:
                    gt1.append(i)
                    if len(gt1) == 4:
                        break

        if len(gt1) < 4:
            # Brute force on smaller subset
            b = brute(gt1 + triple)
            if b == -1:
                answer(-1)
            else:
                for i in range(len(gt1)):
                    a[gt1[i] - 1] = b[i]
                answer(a)
        else:
            # Find two indices such that they form valid triangle with triple
            double = ()
            s = 0
            get_s = {}
            for i in range(2, 5):
                get_s[area(1, i, i)] = i
            for i, j in combinations(gt1, 2):
                A = ask(triple[0], i, j)
                if A in get_s:
                    double = (i, j)
                    s = get_s[A]
                    break
            
            # Deduce remaining values
            get_s = {}
            for i in range(1, 5):
                get_s[area(s, s, i)] = i
            for i in gt1:
                if i not in double:
                    a[i - 1] = get_s[ask(*double, i)]
                else:
                    a[i - 1] = s
            for i in range(gt1[-1] + 1, n + 1):
                a[i - 1] = get_s[ask(*double, i)]
            answer(a)


# https://github.com/VaHiX/CodeForces/