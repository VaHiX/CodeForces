# Problem: CF 1901 D - Yet Another Monster Fight
# https://codeforces.com/contest/1901/problem/D

"""
Algorithm: Dynamic Programming with Preprocessing
Purpose: Find the minimum initial spell power to kill all monsters in a chain lightning attack.

The problem is about choosing an optimal starting monster and determining the minimum power 
needed such that regardless of how the chain lightning spreads (always choosing adjacent 
unhit monsters), all monsters die.

Approach:
1. For each monster, calculate the maximum damage it can receive from the left and right sides 
   when the spell starts from that monster.
2. The damage received by any monster in the chain is:
   - First monster: x damage
   - Second monster: x - 1 damage
   - And so on.
3. Since the first monster gets x damage, then for monster i, if it's the k-th monster hit:
   - Damage = x - (k - 1) => x = damage + k - 1
4. We compute left_arr[i]: maximum possible damage to monster i when the chain comes from the left.
5. We compute right_arr[i]: maximum possible damage to monster i when the chain comes from the right.
6. Finally, for each starting point i, we compute the required power x as max(a[i], left_arr[i], right_arr[i]).

Time Complexity: O(n)
Space Complexity: O(n)

Input:
- First line: number of monsters n
- Second line: health values a[0] to a[n-1]

Output:
- Minimum initial spell power required
"""

import sys

def main():
    data = sys.stdin.read().split()
    if not data:
        print(0)
        return
    n = int(data[0])
    a = list(map(int, data[1 : 1 + n]))
    if n == 0:
        print(0)
        return
    
    # Precompute the maximum damage any monster can take from the left
    left_arr = [-(10**18)] * n
    if n > 1:
        left_arr[1] = a[0] + (n - 1)  # First hit is monster 0, then 1, so power x = a[0] + (n - 1)
        for i in range(2, n):
            value = a[i - 1] + (n - i)
            left_arr[i] = max(left_arr[i - 1], value)
    
    # Precompute the maximum damage any monster can take from the right
    right_arr = [-(10**18)] * n
    if n > 1:
        right_arr[n - 2] = a[n - 1] + (n - 1)
        for i in range(n - 3, -1, -1):
            value = a[i + 1] + (i + 1)
            right_arr[i] = max(right_arr[i + 1], value)
    
    # Find the minimum x needed for each starting position
    ans = 10**18
    for i in range(n):
        candidate = max(a[i], left_arr[i], right_arr[i])
        if candidate < ans:
            ans = candidate
    print(ans)

if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/