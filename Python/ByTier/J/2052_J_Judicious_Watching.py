# Problem: CF 2052 J - Judicious Watching
# https://codeforces.com/contest/2052/problem/J

"""
J. Judicious Watching

Problem Description:
Jill needs to complete n homework tasks, each with a required time 'a[i]' and a deadline 'd[i]'. 
She also wants to watch m episodes of a series, each lasting 'l[j]' minutes, in order. 
For each query time t_k, we need to find the maximum number of episodes Jill can watch before that time 
while still being able to complete all homework tasks on time.

Approach:
1. Sort tasks by deadline to process them in order.
2. Compute cumulative time for completing tasks and headway (the time available 
   between finishing a task and its deadline).
3. Use a greedy strategy to assign episodes to available time slots, tracking when each episode ends.
4. For each query, use binary search to count how many episodes finish before the query time.

Time Complexity: O(n log n + m + q * log(m))
Space Complexity: O(n + m + q)

Key Techniques:
- Sorting with custom key
- Prefix sum computation
- Greedy assignment with backward pass for headway calculation
- Binary search (bisect_right) for efficient query processing

"""

II = lambda: int(input())
MII = lambda: map(int, input().split())
LII = lambda: list(MII())
from bisect import bisect_right

results = []
tests = II()
for _ in range(tests):
    n, m, q = MII()
    a = LII()
    d = LII()
    l = LII()
    q = LII()
    # Pair tasks with their deadlines and sort by deadline
    tasks = [(a[i], d[i]) for i in range(n)]
    tasks.sort(key=lambda el: el[1])
    a = [i[0] for i in tasks]
    d = [i[1] for i in tasks]
    
    # Compute prefix sums of task times
    total_time = [a[0]] * n
    for i in range(1, n):
        total_time[i] = a[i] + total_time[i - 1]
    
    # Compute headway (time between task completion and deadline)
    headway = [0] * n
    headway[-1] = d[-1] - total_time[-1]
    for i in range(n - 2, -1, -1):
        headway[i] = min(headway[i + 1], d[i] - total_time[i])
    
    # Determine finish times of episodes
    finish_time = []
    series_ptr = 0
    time_spent = 0
    total_time.append(0)  # Extend to avoid index error when accessing total_time[-2]
    for i in range(n):
        # While there are unassigned episodes and we can fit them into the available headway
        while series_ptr < m and headway[i] - time_spent >= l[series_ptr]:
            time_spent += l[series_ptr]
            finish_time.append(total_time[i - 1] + time_spent)
            series_ptr += 1
    
    # Assign remaining episodes after all tasks are done
    while series_ptr < m:
        time_spent += l[series_ptr]
        finish_time.append(total_time[-2] + time_spent)
        series_ptr += 1
    
    # Process queries using binary search on finish_times
    ans = []
    for i in q:
        ans.append(bisect_right(finish_time, i))
    results.append(" ".join(map(str, ans)))
print("\n".join(map(str, results)))


# https://github.com/VaHiX/codeForces/