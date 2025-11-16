# Problem: CF 1922 B - Forming Triangles
# https://codeforces.com/contest/1922/problem/B

"""
Purpose: 
    This code calculates the number of ways to choose exactly 3 sticks from a given set such that they can form a non-degenerate triangle.
    The length of each stick is 2^a[i]. For three sticks with lengths 2^x, 2^y, 2^z to form a triangle,
    the sum of any two sides must be greater than the third side. In this case, since all lengths are powers of 2,
    if we sort them as 2^a <= 2^b <= 2^c, then 2^a + 2^b > 2^c is the only condition needed (2^a + 2^b >= 2^c always holds when a <= b and c is the largest)

    Algorithm:
        1. Count frequency of each value in the input array.
        2. For each unique value 'i', calculate how many valid triplets can be formed using sticks of this value.
           - If there are exactly 2 sticks of value 'i', we can pair them with any stick of a smaller value.
           - If there are more than 2 sticks of value 'i', we can:
             a) Pick 2 sticks from these and pair with any smaller value.
             b) Pick 3 sticks from these (combinations).
        3. Accumulate total count while processing each element.

    Time Complexity: O(n)
    Space Complexity: O(n)
"""

from sys import stdin


def input():
    return stdin.readline()[:-1]


def eureka():
    n = int(input())
    arr = list(map(int, input().split()))
    l = [0] * (n + 1)  # Frequency array to count occurrences of each a[i]
    for i in arr:
        l[i] += 1
    total = 0  # Keeps track of number of sticks with power values less than current
    count = 0  # Result counter
    for i in range(n + 1):
        a = l[i]  # Number of sticks with power value i
        if a == 2:
            # Two sticks of same power. Can be paired with any of the previous total sticks
            count += total
        elif a > 2:
            # More than two sticks of same power.
            # First part: Choose 2 from a sticks and combine with any previous stick
            # Second part: Choose 3 from a sticks (valid triangle combinations)
            count += (a * (a - 1) // 2) * total + ((a * (a - 1) * (a - 2)) // 6)
        total += a  # Add sticks of current power to total for next iteration
    print(count)


for _ in range(int(input())):
    eureka()


# https://github.com/VaHiX/CodeForces/