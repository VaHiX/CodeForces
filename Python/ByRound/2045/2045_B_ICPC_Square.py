# Problem: CF 2045 B - ICPC Square
# https://codeforces.com/contest/2045/problem/B

"""
B. ICPC Square

Purpose:
  Given a hotel with N floors, a maximum difference D between consecutive floors in the elevator path,
  and a starting floor S, determine the highest floor reachable by using the elevator rules:
    - From floor x, you can go to floor y if y is a multiple of x and y - x <= D.
  
Algorithms/Techniques:
  - Preprocessing: Normalize input by dividing N, D, and S by S to reduce search space.
  - Optimization: Try to find the largest valid value by checking divisors of N.
  - Brute-force divisor search up to sqrt(N) with early termination.

Time Complexity:
  O(sqrt(N)) in the worst case due to checking divisors up to sqrt(N).
  In practice, the loop is limited to 10^6, so it's effectively constant time for large inputs.

Space Complexity:
  O(1) - only using a few variables regardless of input size.

"""

def main():
    N, D, S = map(int, input().split())
    # Normalize by dividing all values by S to reduce search space
    N //= S
    D //= S
    # If N is small enough, we can directly go to N * S
    if N <= D + 1:
        print(N * S)
    else:
        # Limit N to avoid large searches
        N = min(N, 2 * D)
        # Try all possible divisors up to 10^6
        for i in range(2, 10**6 + 1):
            if N % i == 0 and N - N // i <= D:
                print(N * S)
                return
        # If no divisor found, we must use the previous step (N-1)
        print((N - 1) * S)

main()


# https://github.com/VaHiX/codeForces/