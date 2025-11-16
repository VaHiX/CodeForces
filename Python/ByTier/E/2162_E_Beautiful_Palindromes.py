# Problem: CF 2162 E - Beautiful Palindromes
# https://codeforces.com/contest/2162/problem/E

"""
Algorithm: Beautiful Palindromes
Purpose: Minimize the number of palindromic subarrays after appending exactly k elements to the given array.
Approach:
1. Identify the missing integers in the range [1, n] from the original array.
2. Based on the count of missing integers and the last element of the array:
   - If 2 or more missing integers exist, append the last element to make a palindromic subarray less likely.
   - If exactly 1 missing integer, find two different integers not equal to the missing one or the last element.
   - If no missing integers, use the first 3 elements as a base.
3. Repeat the sequence of chosen integers k times.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the presence array and result list

"""

import sys

input = sys.stdin.readline
print = sys.stdout.write

t = int(input())
dap_an = []

for _ in range(t):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    present = [False] * (n + 1)
    for i in a:
        present[i] = True
    dap_an1 = []
    for i in range(1, n + 1):
        if not present[i]:
            dap_an1.append(i)
        if len(dap_an1) >= 2:
            break
    c = len(dap_an1)
    e = a[-1]
    if c >= 2:
        dap_an1.append(e)
    elif c == 1:
        for i in range(1, min(n + 1, 10)):
            if i != dap_an1[0] and i != e:
                dap_an1.append(i)
                dap_an1.append(e)
                break
    else:
        dap_an1 = a[:3]
    res = []
    for i in range(k):
        res.append(str(dap_an1[i % len(dap_an1)]))
    dap_an.append(res)

sys.stdout.write("\n".join(" ".join(map(str, x)) for x in dap_an) + "\n")


# https://github.com/VaHiX/CodeForces/