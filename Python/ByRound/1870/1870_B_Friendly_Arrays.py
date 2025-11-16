# Problem: CF 1870 B - Friendly Arrays
# https://codeforces.com/contest/1870/problem/B

"""
Code Purpose:
This code solves the "Friendly Arrays" problem where we are given two arrays of integers,
a and b. We can perform operations on array a by OR-ing each element of a with any element from b.
The goal is to find the minimum and maximum possible XOR values of all elements in a after any number of operations.

Approach:
- For each element in array a, we can perform OR with any element from array b.
- If we OR all elements of b together to get a single value 'b', we can essentially make all elements of a
  as large as possible (or equal to the OR of entire b with some element), because OR is monotonic and
  only increases or keeps the same value.
- To compute minimum XOR, we simply apply no operations, and XOR all elements of a as-is.
- To compute maximum XOR, we first calculate b = OR of all b[i], then OR each a[i] with b, and XOR all resulting values.

Time Complexity: O(n + m) per test case, since we iterate through each array once.
Space Complexity: O(1) extra space, excluding input array storage.
"""

def solve():
    input()  # Read n and m (we don't need to store them)
    a = linp()  # Read array a
    b = 0  # Initialize b as 0
    for i in inp():  # Read array b and calculate OR of all elements
        b |= i  # OR operation accumulates all bits
    y = 0  # y will store XOR of original a
    x = 0  # x will store XOR of modified a
    for i in a:  # Calculate XOR of original array a
        y ^= i
    a = [j | b for j in a]  # Apply OR of b to all elements of a
    for i in a:  # Calculate XOR of modified array a
        x ^= i
    print(*sorted([x, y]))  # Output sorted min and max XOR values


def main():
    for t in range(int(input())):  # For each test case
        solve()  # Solve the problem for current test case


def inp():
    return map(int, input().split())  # Read space-separated integers


def linp():
    return list(inp())  # Convert map to list


ONLINE_JUDGE = __debug__
if ONLINE_JUDGE:
    import io
    import os

    input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline  # Optimize input for online judge
main()


# https://github.com/VaHiX/CodeForces/