# Problem: CF 2070 E - Game with Binary String
# https://codeforces.com/contest/2070/problem/E

"""
E. Game with Binary String
Algorithm:
    This problem uses dynamic programming and a technique similar to counting inversions,
    with a twist involving game theory.

    For each prefix of the string, we compute a value f[i] which represents a score.
    The scoring system is:
        - If we encounter a '0', add 1 to the score
        - If we encounter a '1', subtract 3 from the score

    Then, for every prefix, we calculate how many previous prefixes can lead to a winning
    move for the first player. This requires maintaining a count of frequencies of values
    of f[i] and using a sliding window technique to efficiently query how many previous
    f[i] values satisfy certain conditions.

    To determine if a substring is winning for the first player, it must be such that 
    no valid move can be made by the second player in the current configuration.

    Time Complexity: O(n)
    Space Complexity: O(n)

    Techniques used:
        - Prefix sum technique
        - Sliding window with frequency counting
        - Game theory analysis (winning/losing positions)
"""

def main():
    import sys

    input_data = sys.stdin.read().split()
    n = int(input_data[0])
    s = input_data[1].strip()
    f = [0] * (n + 1)
    f[0] = 3 * n
    for i in range(n):
        if s[i] == "0":
            f[i + 1] = f[i] + 1
        else:
            f[i + 1] = f[i] - 3
    cnt = [0] * (4 * n + 1)
    ans = 0
    ssum = 0
    j = 3 * n
    for i in range(n + 1):
        if f[i] + 1 <= 4 * n:
            ans += cnt[f[i] + 1]
        r = max(-1, f[i] - 2)
        while j < r:
            j += 1
            ssum += cnt[j]
        while j > r:
            ssum -= cnt[j]
            j -= 1
        ans += ssum
        cnt[f[i]] += 1
        if f[i] <= j:
            ssum += 1
    print(ans)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/