# Problem: CF 1891 C - Smilo and Monsters
# https://codeforces.com/contest/1891/problem/C

"""
Algorithm: Greedy approach to minimize number of attacks.
Techniques: Sorting, two-pointer like logic.

Time Complexity: O(n log n) due to sorting.
Space Complexity: O(1) if we ignore the space used for input.

The idea is to use a greedy strategy where we prioritize using 
the second type of attack (ultimate attack) on the largest hordes 
to maximize the number of monsters destroyed per attack. This reduces 
the total number of attacks needed.
"""

for _ in range(int(input())):  # Read number of test cases
    n = int(input())  # Read number of hordes
    a = list(map(int, input().split()))  # Read monsters in each horde
    a.sort()  # Sort hordes in ascending order to process from largest
    sm = sum(a)  # Total number of monsters
    half = sm // 2  # Target: destroy at least half the monsters using first type of attack
    x = 0  # Counter for second type attacks (ultimate attacks)
    i = n - 1  # Index pointing to the largest remaining horde
    
    # Greedily use first type of attack (normal attack) on hordes
    # until we have enough monsters destroyed to meet the half threshold
    while half > 0:
        half -= a[i]  # Reduce half by monsters in current largest horde
        x += 1  # Increment ultimate attack counter
        i -= 1  # Move to next largest horde
    
    # Result = (monsters destroyed via normal attacks) + (ultimate attacks) + (remaining monsters if odd)
    print(sm // 2 + x + sm % 2)


# https://github.com/VaHiX/CodeForces/