# Problem: CF 1965 D - Missing Subarray Sum
# https://codeforces.com/contest/1965/problem/D

"""
Algorithm: Missing Subarray Sum Recovery for Palindromes
Purpose: Given all but one subarray sums of a palindromic array, recover the original array.

Approach:
1. Identify the missing sum among the given subarray sums.
2. Use the properties of palindromes and subarray sums to reconstruct the array elements.
3. The key insight involves identifying which subarrays are symmetric and reconstructing
   the elements using known relationships.

Time Complexity: O(n^2)
Space Complexity: O(n)

Techniques used:
- Palindrome property: a[i] = a[n+1-i]
- Subarray sum relationships
- Sorting and comparison of sums
"""

from sys import stdin, stdout

input = stdin.readline
print = lambda s: stdout.write(s + "\n")


def getSubSums(odd, n):
    palin = getPalin(odd, n)
    sums = []
    for i in range(n):
        sum = 0
        for j in range(i, n):
            sum += palin[j]
            sums.append(sum)
    sums.sort(reverse=True)
    return sums


def getPalin(odd, n):
    pref = [(odd[i - 1] - odd[i]) // 2 for i in range(1, len(odd))]
    return pref + [odd[-1] // (2 - (n & 1))] * (2 - (n & 1)) + pref[::-1]


for _ in range(int(input())):

    n = int(input())
    a = list(map(int, input().split()))
    a.sort(reverse=True)

    odd = []
    for sum in a:
        if len(odd) and odd[-1] == sum:
            odd.pop()
        else:
            odd.append(sum)

    if len(odd) > (n + 1) >> 1:

        par = [[], []]
        for sum in odd:
            par[sum & 1].append(sum)

        if len(par[0]) == 1:
            m = par[0][0]
        elif len(par[1]) == 1:
            m = par[1][0]

        else:
            t, l = getSubSums(odd, n + 2), len(a)
            for i in range(len(t)):
                if i == l:
                    m = 2 * t[i] - odd[0]
                    break
                elif a[i] != t[i]:
                    m = 2 * t[i] - odd[0]
                    break

        odd.remove(m)

    else:
        t = getSubSums(odd, n - 2)
        l = len(t)
        for i in range(len(a)):
            if i == l:
                break
            elif a[i] != t[i]:
                break

        t, l = 2 * a[i] - odd[0], len(odd)
        for i in range(l + 1):
            if i == l:
                odd.append(t)
            elif t > odd[i]:
                odd.insert(i, t)
                break

    print(" ".join(map(lambda num: str(int(num)), getPalin(odd, n))))


# https://github.com/VaHiX/CodeForces/