# Problem: CF 1862 E - Kolya and Movie Theatre
# https://codeforces.com/contest/1862/problem/E

"""
Algorithm: Greedy with PriorityQueue (Min-Heap)
Approach:
- We process movies in order from day 1 to n.
- For each movie, if its entertainment value a[i] is positive, we consider including it.
- We maintain a min-heap of size at most m to keep track of the m most valuable movies we've seen so far.
- As we iterate, we keep track of total entertainment value (rsum) and update the maximum possible value of 
  (rsum - (idx + 1) * d) which represents total entertainment minus the penalty due to delay.

Time Complexity: O(n * log m) per test case, where n is number of movies and m is max visits allowed.
Space Complexity: O(m) for the heap storage.
"""

from heapq import heappush, heappushpop


def run():
    n, m, d = list(map(int, input().split()))
    a = list(map(int, input().split()))
    rsum = 0
    c = 0
    h = []
    ret = 0
    for idx, x in enumerate(a):
        if x < 0:
            continue  # Skip negative entertainment values
        rsum += x  # Add current movie's value to running sum
        if c < m:  # If we haven't reached the limit yet
            c += 1
            heappush(h, x)  # Add to heap
        else:
            t = heappushpop(h, x)  # Replace smallest in heap with current value
            rsum -= t  # Adjust sum accordingly
        tmp = rsum - (idx + 1) * d  # Calculate total entertainment with day count penalty
        if tmp > ret:
            ret = tmp  # Update maximum entertainment value
    print(ret)


TT = int(input())
for _ in range(TT):
    run()


# https://github.com/VaHiX/CodeForces/