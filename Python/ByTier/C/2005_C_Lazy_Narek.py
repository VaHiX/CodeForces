# Problem: CF 2005 C - Lazy Narek
# https://codeforces.com/contest/2005/problem/C

"""
Algorithm: Dynamic Programming with State Tracking
Techniques: 
- State compression using DP to track progress in forming "narek"
- For each string, compute how many points Narek gets and how many points ChatGPT gets
- Use DP to maintain max score difference at each stage of forming "narek"

Time Complexity: O(n * m) where n is number of strings and m is average length of strings
Space Complexity: O(n) for the DP array and intermediate data structures

The solution processes each string to track how many "narek" sequences can be formed,
and how many letters are left unused (which contributes to the opponent's score).
"""
def main():
    import sys

    narek = "narek"
    char_to_index = [-1] * 256
    for idx, ch in enumerate(narek):
        char_to_index[ord(ch)] = idx
    data = sys.stdin.read().split()
    ptr = 0
    t = int(data[ptr])
    ptr += 1
    results = []
    for _ in range(t):
        n = int(data[ptr])
        ptr += 1
        int(data[ptr])
        ptr += 1
        s_indices = []
        for _ in range(n):
            s = data[ptr]
            ptr += 1
            s_idx = []
            for c in s:
                idx = char_to_index[ord(c)]
                s_idx.append(idx)
            s_indices.append(s_idx)
        dp = [-(10**9)] * 5
        dp[0] = 0
        for s in s_indices:
            ndp = dp.copy()
            for j in range(5):
                if dp[j] == -(10**9):
                    continue
                counted_score = 0
                next_j = j
                for idx in s:
                    if idx == -1:
                        continue
                    if next_j == idx:
                        next_j = (next_j + 1) % 5
                        counted_score += 1
                    else:
                        counted_score -= 1
                if ndp[next_j] < dp[j] + counted_score:
                    ndp[next_j] = dp[j] + counted_score
            dp = ndp
        ans = max(dp[i] - 2 * i for i in range(5))
        results.append(ans)
    print("\n".join(map(str, results)))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/