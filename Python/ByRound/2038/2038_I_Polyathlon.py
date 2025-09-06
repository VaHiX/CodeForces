# Contest 2038, Problem I: Polyathlon
# URL: https://codeforces.com/contest/2038/problem/I

import io,os
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline




def main():
    m,n = map(int,input().split())

    data = [] 
    grid = []
    for i in range(m):
        s = input().decode('utf-8')[:n]
        grid.append(s)
        data.append((s,i+1))

    data.sort(reverse=True)

    ranking = [data[i][1] for i in range(m)]




    ans = [0]*n

    ans[0] = ranking[0]


    for j in range(n-1,0,-1):
        left = []
        right = []
        for index in ranking:
            if grid[index-1][j]=='1':  left.append(index)
            else: right.append(index)

        ranking = left + right
        ans[j] = ranking[0]

 
        

    print(*ans)


    

        







main()
