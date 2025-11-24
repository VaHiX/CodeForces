# Problem: CF 1510 K - King's Task
# https://codeforces.com/contest/1510/problem/K

# K. King's Task
# time limit per test
# 3 seconds
# memory limit per test
# 512 megabytes
# input
# standard input
# output
# standard output
#
# The brave Knight came to the King and asked permission to marry the princess. The King knew that the Knight was brave, but he also wanted to know if he was smart enough. So he asked him to solve the following task.
# There is a permutation p_i of numbers from 1 to 2n. You can make two types of operations.
#
# Swap p_1 and p_2, p_3 and p_4, ..., p_{2n-1} and p_{2n}.
# Swap p_1 and p_{n+1}, p_2 and p_{n+2}, ..., p_{n} and p_{2n}.
# The task is to find the minimal number of operations required to sort the given permutation.
#
# Algorithms/Techniques: Simulation with two operation types
# Time Complexity: O(n^2) - due to nested loops in worst-case scenario where we might need to perform O(n) swaps for each of the O(n) steps to reach sorted order
# Space Complexity: O(n) - for storing arrays a and b, both of size 2n

import sys

input = sys.stdin.readline
n = 2 * (int(input()))
a = [int(i) for i in input().split()]
b = [i for i in range(1, n + 1)]
ans = 0
for i in range(n):
    if a != b:  # If current array is not sorted
        if a[0] < a[n // 2]:  # Check condition for first type of operation
            # Perform operation 1: swap pairs (0,1), (2,3), ..., (n-2,n-1)
            for i in range(0, n - 1, 2):
                a[i], a[i + 1] = a[i + 1], a[i]
        else:
            # Perform operation 2: swap elements at position 0 to n//2 with respective elements from n//2 to n
            x = n // 2
            a = a[x:] + a[:x]
        ans += 1  # Increment operation count
    else:
        break  # If sorted, exit loop
if a == b:  # Check if sorting was successful
    print(ans)
else:
    print(-1)  # Return -1 if impossible to sort


# https://github.com/VaHiX/codeForces/