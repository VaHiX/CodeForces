# Problem: CF 1722 G - Even-Odd XOR
# https://codeforces.com/contest/1722/problem/G

"""
Problem: G. Even-Odd XOR
Algorithm: Construct an array of n distinct non-negative integers such that the XOR of elements at odd indices equals the XOR of elements at even indices.

Approach:
- We fix the first two elements as 1 and 2.
- Then, for the remaining positions, we use a predefined large value x (2^20) and y (2^30).
- The last element is computed such that the XOR of all elements equals zero.
- This is achieved by calculating the cumulative XOR of all elements except the last, and then setting the last element to that XOR result to ensure the final XOR is 0.
- This ensures the XOR of odd indices and even indices are equal.

Time Complexity: O(n) per test case
Space Complexity: O(1) excluding the output space

"""

x = 2**20
y = 2**30
for _ in range(int(input())):
    n = int(input())
    temp = x ^ y
    for i in range(1, n - 2):
        print(i, end=" ")
        temp ^= i
    print(x, y, temp)


# https://github.com/VaHiX/CodeForces/