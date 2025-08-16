# Contest 863, Problem B: Kayaking
# URL: https://codeforces.com/contest/863/problem/B

N = int(input())
nums = [int(x) for x in input().split()]
nums.sort()

answer = 10000000
for i in range(len(nums)):
    for j in range(i+1, len(nums)):
        temp = nums.copy()
        count = 0
        temp.pop(i)
        temp.pop(j-1)
        for k in range(0, len(temp)-1, 2):
            count += temp[k+1] - temp[k]
        answer = min(answer, count)
print(answer)