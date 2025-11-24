# Problem: CF 1952 C - They Have Fooled
# https://codeforces.com/contest/1952/problem/C

"""
Task: C. They Have Fooled
Algorithms/Techniques: Direct lookup in precomputed array
Time Complexity: O(1) - constant time lookup
Space Complexity: O(1) - fixed size array of 13 elements

This problem appears to be a direct indexing task where we have a precomputed
array of values corresponding to different inputs. The array contains 13 elements
indexed from 0 to 12, and we simply return the value at index n.
"""
a = [10, 10, 8, 9, 8, 7, 7, 7, 7, 0, 9, 6, 8]
n = int(input())  # Read the input integer n
print(a[n])  # Print the value at index n from the precomputed array


# https://github.com/VaHiX/CodeForces/