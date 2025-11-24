# Problem: CF 1987 C - Basil's Garden
# https://codeforces.com/contest/1987/problem/C

"""
Flower Garden Problem

Algorithm:
- For each flower at position i with height h_i, the time it takes for that flower to die (become 0) 
  is determined by how long it takes for the wind to reduce its height, which is h_i + i seconds.
  This is because, starting from position i, the wind will reduce the height of this flower every second,
  but only if it's taller than the next flower to its right (or if it's the last flower).
- The key insight is that the last flower to die is determined by the flower that takes the maximum time to die.
- We iterate through all flowers and calculate for each flower the time it would take to die: 
  time = height + index.
- The result is the maximum of all such times.

Time Complexity: O(n) per test case
Space Complexity: O(1) excluding input/output storage

"""
def process_test_cases():
    import sys

    input = sys.stdin.read
    data = input().split()
    index = 0
    t = int(data[index])
    index += 1
    results = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        heights = list(map(int, data[index : index + n]))
        index += n
        max_time = 0
        # For each flower, calculate the minimum time it takes for this flower to die
        for i in range(n):
            min_time_for_flower = heights[i] + i  # Time to reduce height to 0
            if min_time_for_flower > max_time:
                max_time = min_time_for_flower
        results.append(str(max_time))
    sys.stdout.write("\n".join(results) + "\n")


process_test_cases()


# https://github.com/VaHiX/CodeForces/