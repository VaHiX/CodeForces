# Problem: CF 1978 A - Alice and Books
# https://codeforces.com/contest/1978/problem/A

"""
Algorithm: Greedy
Purpose: To maximize the sum of the last element and the maximum among all other elements,
         we should place the maximum element (excluding the last) in one pile and the last element in the other pile.
         The last element is always chosen because it's the highest number in its pile.
Time Complexity: O(n) - Single pass through the array to find max element.
Space Complexity: O(1) - Only using a constant amount of extra space.
"""

from sys import stdin, stdout

input = lambda: stdin.readline().rstrip()
ints = lambda: [int(x) for x in input().split()]
println = lambda x: stdout.write(str(x) + "\n")


def solve(n, a) -> int:
    # Return the sum of the last element and the maximum of all elements except the last
    return a[-1] + max(a[:-1])


for _ in range(int(input())):
    n = int(input())
    a = ints()
    println(solve(n, a))


# https://github.com/VaHiX/CodeForces/