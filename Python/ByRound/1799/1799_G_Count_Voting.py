# Problem: CF 1799 G - Count Voting
# https://codeforces.com/contest/1799/problem/G

"""
Count Voting

Algorithm:
- The problem involves assigning votes among people such that:
  - Each person votes for someone from a different team.
  - Each person receives exactly the desired number of votes.
- Approach:
  1. Group people by their teams.
  2. Use dynamic programming to count valid vote assignments.
  3. Use combinatorics for arranging votes within teams.
  4. Apply inclusion-exclusion principle for final calculation.

Time Complexity: O(n^3)
Space Complexity: O(n^2)

This solution uses:
- Precomputed factorials and inverse factorials for combinatorial calculations.
- Dynamic programming with inclusion-exclusion to avoid overcounting.
- Modular arithmetic for large numbers.
"""

MOD = 998244353


def main():
    import sys

    data = sys.stdin.read().split()
    n = int(data[0])
    c_list = list(map(int, data[1 : 1 + n]))
    t_list = list(map(int, data[1 + n : 1 + 2 * n]))

    s_arr = [0] * (n + 1)  # s_arr[team] = number of people in that team
    C_team_arr = [0] * (n + 1)  # C_team_arr[team] = total desired votes for that team

    # Count members and desired votes per team
    for i in range(n):
        team = t_list[i]
        s_arr[team] += 1

    for i in range(n):
        team = t_list[i]
        C_team_arr[team] += c_list[i]

    maxN = 500
    fact = [1] * (maxN + 1)  # fact[i] = i!
    inv_fact = [1] * (maxN + 1)  # inv_fact[i] = 1/i!

    # Precompute factorials
    for i in range(1, maxN + 1):
        fact[i] = fact[i - 1] * i % MOD

    # Precompute inverse factorials using Fermat's little theorem
    inv_fact[maxN] = pow(fact[maxN], MOD - 2, MOD)
    for i in range(maxN, 0, -1):
        inv_fact[i - 1] = inv_fact[i] * i % MOD

    # part3: Calculate the number of ways to assign votes within each team
    part3 = 1
    for h in range(1, n + 1):
        if C_team_arr[h] == 0:
            continue
        # Compute the denominator for multinomial coefficient
        denom = 1
        for i in range(n):
            if t_list[i] == h:
                denom = (denom * fact[c_list[i]]) % MOD
        part3 = (part3 * fact[C_team_arr[h]] % MOD) * pow(denom, MOD - 2, MOD) % MOD

    # dp[e_total] = number of valid ways to satisfy exactly 'e_total' total vote constraints
    dp = [0] * (n + 1)
    dp[0] = 1  # Base case: 0 constraints satisfied

    # Process each team
    for g in range(1, n + 1):
        s_g = s_arr[g]  # Number of people in team g
        if s_g == 0:
            continue
        C_g = C_team_arr[g]  # Required votes for team g
        low_g = max(0, C_g - s_g)  # Minimum possible votes from this team
        high_g = C_g  # Maximum possible votes from this team
        
        new_dp = [0] * (n + 1)
        # Iterate for all possible numbers of votes from this team
        for e_g in range(low_g, high_g + 1):
            # Compute multinomial coefficient for e_g votes from team g
            # This represents choosing which people will cast e_g votes
            denom = fact[C_g - e_g] % MOD
            temp = fact[s_g - C_g + e_g] % MOD
            denom = denom * temp % MOD
            denom = denom * fact[e_g] % MOD
            term_val = fact[s_g] * pow(denom, MOD - 2, MOD) % MOD
            
            for e_total in range(e_g, n + 1):
                new_dp[e_total] = (new_dp[e_total] + dp[e_total - e_g] * term_val) % MOD
        dp = new_dp

    # part2: Apply inclusion-exclusion principle
    inner = 0
    for e_total in range(0, n + 1):
        sign = 1 if e_total % 2 == 0 else -1
        term = sign * fact[e_total] % MOD * dp[e_total] % MOD
        inner = (inner + term) % MOD

    part2 = inner * pow(-1, n, MOD) % MOD  # Multiply by (-1)^n
    ans = part3 * part2 % MOD  # Combine results
    print(ans)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/