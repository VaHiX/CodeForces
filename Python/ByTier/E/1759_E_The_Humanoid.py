# Problem: CF 1759 E - The Humanoid
# https://codeforces.com/contest/1759/problem/E

"""
Algorithm: Greedy with Simulation
This problem involves finding the maximum number of astronauts a humanoid can absorb,
given that the humanoid has two green serums and one blue serum which can be used in any order.
The strategy involves trying all possible orders of using the serums (3! = 6 permutations) 
and simulating the process to find the maximum number of astronauts that can be absorbed.

Time Complexity: O(n log n) for sorting + O(n) for each permutation simulation = O(n log n + n) = O(n log n)
Space Complexity: O(1) additional space excluding input storage

Approach:
1. Sort astronaut powers in ascending order for greedy absorption
2. Try all 6 permutations of serum usage (green, green, blue) 
3. For each permutation, simulate the process:
   - Apply serums one by one (if available)
   - Absorb astronauts whose power is less than current humanoid power
   - Update humanoid power after absorption and serum usage
4. Return the maximum count from all simulations
"""

for _ in range(int(input())):
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    a.sort()

    def F(a, b):
        res = m  # Initial humanoid power
        cnt = 0  # Count of serums used (0, 1, or 2)
        i = 0    # Number of astronauts absorbed
        
        # Iterate through all astronauts in sorted order
        for x in a:
            # While humanoid power is not enough to absorb current astronaut
            while res <= x:
                # If we still have unused serums
                if cnt < 3:
                    # Apply next serum (2 for green, 3 for blue)
                    res *= b[cnt]
                else:
                    # No more serums available, return current absorption count
                    return i
                cnt += 1  # Increment serum count
            
            # Absorb the current astronaut (add floor of power divided by 2)
            res += x // 2
            i += 1  # Increment absorption count
        
        return i  # Return total astronauts absorbed

    # Try all 6 possible orders of serum usage:
    # [2, 2, 3] means: green, green, blue
    # [2, 3, 2] means: green, blue, green  
    # [3, 2, 2] means: blue, green, green
    print(max(F(a, [2, 2, 3]), F(a, [2, 3, 2]), F(a, [3, 2, 2])))


# https://github.com/VaHiX/CodeForces/