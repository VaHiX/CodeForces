# Contest 2070, Problem E: Game with Binary String
# URL: https://codeforces.com/contest/2070/problem/E


def main():
    import sys

    input_data = sys.stdin.read().split()
    n = int(input_data[0])
    s = input_data[1].strip()

    # Build the prefix sum array f.
    # f[0] is set to 3*n, and then for each character,
    # we add 1 if the character is '0' and subtract 3 if it is '1'.
    f = [0] * (n + 1)
    f[0] = 3 * n
    for i in range(n):
        if s[i] == "0":
            f[i + 1] = f[i] + 1
        else:
            f[i + 1] = f[i] - 3

    # cnt will count frequencies for indices 0..4*n.
    cnt = [0] * (4 * n + 1)
    ans = 0
    ssum = 0  # using 'ssum' instead of sum (to avoid conflict with built-in sum)
    j = 3 * n  # starting value of j

    # Iterate over all positions in the prefix sum array.
    for i in range(n + 1):
        # If f[i] + 1 is in range, add the count to ans.
        if f[i] + 1 <= 4 * n:
            ans += cnt[f[i] + 1]

        # Compute r as the maximum of -1 and f[i] - 2.
        r = max(-1, f[i] - 2)

        # Increase j (and update ssum) until j reaches r.
        while j < r:
            j += 1
            ssum += cnt[j]
        # Decrease j (and update ssum) until j reaches r.
        while j > r:
            ssum -= cnt[j]
            j -= 1

        ans += ssum
        # Increase frequency of f[i].
        cnt[f[i]] += 1

        # If f[i] is less than or equal to j, increment ssum.
        if f[i] <= j:
            ssum += 1

    print(ans)


if __name__ == "__main__":
    main()
