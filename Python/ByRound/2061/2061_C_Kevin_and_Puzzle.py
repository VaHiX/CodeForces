# Problem: CF 2061 C - Kevin and Puzzle
# https://codeforces.com/contest/2061/problem/C

"""
Algorithm: Dynamic Programming with State Tracking

This solution uses dynamic programming to count valid configurations of honest and liar classmates.
Each position can either be honest or a liar, and each person states how many liars are to their left.
We maintain two states:
- old0_val: the number of liars claimed by the last honest person
- old1_val: the number of liars claimed by the last liar person

Transitions are made based on consistency with current person's claim.
Time Complexity: O(n) per test case
Space Complexity: O(1) - only a few variables are stored
"""

def solve():
    import sys

    input_data = sys.stdin.read().strip().split()
    MOD = 998244353
    t = int(input_data[0])
    idx = 1
    out = []
    for _ in range(t):
        n = int(input_data[idx])
        idx += 1
        a = list(map(int, input_data[idx : idx + n]))
        idx += n
        # old0_val: number of liars claimed by the previous honest person
        # old0_cnt: number of ways to achieve this state
        old0_val = 0
        old0_cnt = 1
        # old1_val: number of liars claimed by the previous liar person
        # old1_cnt: number of ways to achieve this state
        old1_val = -1
        old1_cnt = 0
        for i in range(n):
            new0_val = -1
            new0_cnt = 0
            new1_val = -1
            new1_cnt = 0
            # If previous person was honest (old0_val != -1) and their claim matches current
            if old0_val != -1 and old0_val == a[i]:
                new0_val = a[i]
                new0_cnt = (new0_cnt + old0_cnt) % MOD
            # If previous person was a liar (old1_val != -1) and their claim matches current
            if old1_val != -1 and old1_val == a[i]:
                if new0_val == -1:
                    new0_val = a[i]
                new0_cnt = (new0_cnt + old1_cnt) % MOD
            # If previous person was honest, current person must be a liar
            if old0_val != -1:
                new1_val = old0_val + 1
                new1_cnt = old0_cnt
                new1_cnt %= MOD
            # Update states for next iteration
            old0_val = new0_val
            old0_cnt = new0_cnt
            old1_val = new1_val
            old1_cnt = new1_cnt
        ans = (old0_cnt + old1_cnt) % MOD
        out.append(str(ans))
    print("\n".join(out))


solve()


# https://github.com/VaHiX/CodeForces/