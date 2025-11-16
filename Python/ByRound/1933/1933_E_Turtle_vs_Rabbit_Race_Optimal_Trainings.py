# Problem: CF 1933 E - Turtle vs. Rabbit Race: Optimal Trainings
# https://codeforces.com/contest/1933/problem/E

"""
Algorithm: 
- For each query (l, u), we need to find optimal r such that the total performance increase is maximized.
- Performance increase for k sections is sum of (u - (k - 1)) = k*u - k*(k-1)/2.
- We use binary search to find the best r.
- The key is to calculate total sections and then compute performance increase for that number of sections using arithmetic series formula.

Time Complexity: O(q * log n * log u) where q is number of queries and n is length of array
Space Complexity: O(n) for prefix sum array
"""

from sys import stdin


def I():
    return int(stdin.readline().strip())


def II():
    return map(int, stdin.readline().strip().split())


def IL():
    return list(map(int, stdin.readline().strip().split()))


def SIL():
    return sorted(
        map(int, stdin.readline().strip().split()),
    )


def S():
    return stdin.readline().strip()


def SL():
    return list(stdin.readline().strip().split())


def solve():
    length = I()
    nums = IL()

    prefix = [0]  # Prefix sum array

    for num in nums:
        prefix.append(prefix[-1] + num)

    def add(i, j):
        # Helper function to compute sum of arithmetic sequence
        i -= 1
        i = i * (i + 1) // 2
        j = j * (j + 1) // 2

        return j - i

    def check(l, r):
        # Get total number of sections from l to r
        val = prefix[r] - prefix[l - 1]

        return val

    answer = []
    for _ in range(I()):
        l, u = II()

        r = length
        init = l

        # Binary search for the optimal r
        while l + 1 < r:
            mid = (l + r) // 2
            val = check(init, mid)
            if val <= u:
                l = mid
            elif val > u:
                r = mid
                
        # Calculate performance for l and r
        vall = check(init, l)
        val2 = check(init, r)
        
        # Compute values using arithmetic series formula
        first = add(vall - u, u + 1)
        second = add(val2 - u, u + 1)

        # Compare and choose minimum r that gives maximum performance
        if first >= second:
            answer.append(l)
        else:
            answer.append(r)

    print(*answer)


T = I()
for _ in range(T):
    solve()


# https://github.com/VaHiX/CodeForces/