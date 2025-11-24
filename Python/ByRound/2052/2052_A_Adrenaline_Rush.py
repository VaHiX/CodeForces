# Problem: CF 2052 A - Adrenaline Rush
# https://codeforces.com/contest/2052/problem/A

"""
Algorithm/Techniques: Greedy Algorithm, Set Operations

Time Complexity: O(n^2)
Space Complexity: O(n^2)

This code computes the maximum number of overtakes that could have occurred during a race,
given the final order of cars. It simulates a process where cars are inserted one by one
into a sequence and each new car overtakes all cars that come after it in the current list.
The result is a list of overtakes in temporal order, such that when applied to an initial
sorted sequence, it produces the given final order.

The greedy strategy ensures all possible overtakes occur, respecting the constraint that
a car cannot overtake another more than once. The solution builds the sequence step by step,
tracking which cars have already overtaken others and ensuring no duplicate overtakes.
"""

n = int(input())
c = list(map(int, input().split()))
ans = []

# For each car in the final order, simulate insertions
for i in range(n):
    for j in range(i + 1, n):
        # Add overtakes in reverse order: j overtakes i (j is behind i)
        ans.append(f"{j+1} {i+1}")

s = set()
# Process each car in the final order
for i in range(n):
    x = c[i]
    s.add(x)
    # For all positions after this car's current position, simulate overtakes
    for j in range(x + 1, n + 1):
        if j not in s:
            # Car x overtakes car j if j was not inserted yet
            ans.append(f"{x} {j}")

print(len(ans))
print("\n".join(ans))


# https://github.com/VaHiX/codeForces/