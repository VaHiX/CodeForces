# Problem: CF 1719 C - Fighting Tournament
# https://codeforces.com/contest/1719/problem/C

"""
Algorithm: Fighting Tournament
Purpose: Determine the number of victories for a given participant in the first k rounds of a tournament.
Techniques:
- Simulation of a tournament with a deque-like structure
- Preprocessing to calculate maximum victories for each participant
- Efficient query processing based on precomputed values

Time Complexity: O(n + q) per test case where n is the number of participants and q is the number of queries
Space Complexity: O(n) for storing the victory counts and preprocessing data

The solution works by:
1. Preprocessing the array to calculate how many times each participant can win before the maximum strength participant wins
2. Using this preprocessing to quickly answer queries in O(1) time
3. Special case handling for the participant with maximum strength who wins infinitely
"""
def cf_1719_c():
    N, qn = map(int, input().split())

    a = list(map(int, input().split()))
    m, mn = a[0], 0

    f = [0] * N
    # Calculate how many fights each participant wins before the maximum strength participant
    for i in range(1, N):
        if a[i] > m:
            m = a[i]
            mn = i
        f[mn] += 1

    # The participant with maximum strength wins infinitely
    f[mn] = float("inf")

    for _ in range(qn):
        n, k = map(int, input().split())
        # Calculate how many fights the nth participant has already won 
        # before the maximum strength participant wins all subsequent fights
        fuck = max(n - 2, 0)
        print(min(max(k - fuck, 0), f[n - 1]))


if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        cf_1719_c()


# https://github.com/VaHiX/CodeForces/