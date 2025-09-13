# Contest 2108, Problem D: Needle in a Numstack
# URL: https://codeforces.com/contest/2108/problem/D

# author: Sushmanth
from sys import stdin, stdout

input = stdin.readline
inp = lambda: list(map(int, input().split()))

"""
Observations :-
"""


# a = [2 , 4 , 3 , 1 , 2 , 4 , 3 , 1 , 2 , 1 , 3 , 2 , 4 , 1 , 3 , 2 , 4 , 1]
# a = [1 , 3 , 2 , 4 , 1 , 3 , 4 , 2 , 1 , 3 , 4 , 2]
# a = [1 , 2 , 3 , 1 , 2 , 3 , 1 , 3 , 2]
def ask(x):

    print("?", x, flush=True)
    # return a[x - 1]
    return int(input())


def answer():

    if (2 * k) == n:
        return [k, k]

    perm = []
    for i in range(k):
        perm.append(ask(i + 1))

    perm_end = []
    for i in range(k):
        perm_end.append(ask(n - k + i + 1))

    d_point = n - k
    low, high = n - k, k
    for delta in range(k):
        ind = (n // k) * k + delta
        rightind = (k - 1) - (n - ind - 1) % k
        if perm[delta] == perm_end[rightind]:
            continue

        point = n - k
        l, h = 0, (n - delta - 1) // k
        while l <= h:
            mid = (l + h) // 2
            p = mid * k + delta
            value = ask(p + 1)
            leftind = p % k
            if value == perm[leftind]:
                l = mid + 1
            else:
                point = p
                h = mid - 1

        d_point = min(d_point, point)
        break

    # From any one d_point the optimal point can be in the range [d_point - k , d_point]
    # Didn't realize this during the contest I know trying for all k points would work with more queries
    # To optimize was doing binary search but didn't notice the search was not monotonic
    # Just realized this facts. Too Late :(.
    for i in range(max(k, d_point - k), d_point):
        if ask(i + 1) != perm[i % k]:
            d_point = i
            break

    if d_point > k:
        value = ask(d_point + 1)
        for i in range(k):
            rightind = (k - 1) - (n - (d_point - 1) - 1) % k
            if value == perm[i] and perm_end[rightind] == ask(d_point):
                return [-1]

    return [d_point, n - d_point]


for T in range(int(input())):

    n, k = inp()

    print("!", *answer(), flush=True)
