# Problem: CF 2139 D - Antiamuny Wants to Learn Swap
# https://codeforces.com/contest/2139/problem/D

"""
Algorithm: 
This code solves a problem about determining whether a subarray of a permutation is "perfect".
A subarray is perfect if the minimum number of operations needed to sort it using both adjacent swaps and swaps of elements at distance 2 is the same as the number of adjacent swaps only.

Approach:
1. For each element, find the nearest previous element that is smaller (rightmost smaller element).
2. For each element, find the nearest next element that is larger (leftmost larger element).
3. For each position, determine the maximum leftmost index where a valid swap (using operation 2) can be performed to move an element rightward.
4. Preprocess this information using a monotonic stack approach.
5. Use prefix maximums to efficiently answer queries.

Time Complexity: O(n + q)
Space Complexity: O(n)

"""

from sys import stdin

input = stdin.readline


def main():
    n, q = map(int, input().split())
    a = [int(i) for i in input().split()]
    
    # gr[i] stores the index of the nearest previous element that is smaller than a[i]
    gr = [-1] * (n)
    s = []
    for i in range(n):
        while len(s) and a[s[-1]] < a[i]:
            s.pop()
        if len(s):
            gr[i] = s[-1]
        s.append(i)
    
    # lr[i] stores the index of the nearest next element that is larger than a[i]
    lr = [n] * (n)
    s = []
    for i in range(n - 1, -1, -1):
        while len(s) and a[s[-1]] > a[i]:
            s.pop()
        if len(s):
            lr[i] = s[-1]
        s.append(i)
    
    # p[i] stores the maximum leftmost index that can contribute to sorting a subarray ending at i
    p = [-1] * n
    for i in range(n):
        l, r = gr[i], lr[i]
        if l == -1 or r == n:
            continue
        p[r] = max(p[r], l)
    
    # Prefix maximum to get best left position for any right index
    for i in range(1, n):
        p[i] = max(p[i], p[i - 1])
    
    # Process queries
    for _ in range(q):
        l, r = map(int, input().split())
        l -= 1
        r -= 1
        if p[r] < l:
            print("YES")
        else:
            print("NO")


t = int(input())
for __ in range(t):
    (main())


# https://github.com/VaHiX/codeForces/