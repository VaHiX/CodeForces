# Problem: CF 1881 D - Divide and Equalize
# https://codeforces.com/contest/1881/problem/D

"""
Algorithm: Divide and Equalize
Techniques: Mathematical analysis using logarithms and GCD

Time Complexity: O(n), where n is the number of elements in the array
Space Complexity: O(1), only using a constant amount of extra space

The approach involves:
1. Computing the geometric mean of all elements
2. Checking if the geometric mean is an integer
3. Verifying that each element either equals 1 or shares a common factor with the geometric mean
"""

from math import exp, gcd, log


def test(n, xs):
    # Calculate the geometric mean using logarithms to avoid overflow
    root = exp(sum(log(x) for x in xs) / n)
    
    # Check if the geometric mean is close to an integer
    if abs(root - round(root)) > 0.00001:
        return False
    
    # For each element in the array, check:
    # - If it's 1, it's valid
    # - Otherwise, it must share a common factor with the rounded geometric mean
    return all(x == 1 or gcd(x, round(root)) != 1 for x in xs)


def task():
    n = int(input())
    xs = [int(x) for x in input().split()]
    print("YES" if test(n, xs) else "NO")


for _ in range(int(input())):
    task()


# https://github.com/VaHiX/CodeForces/