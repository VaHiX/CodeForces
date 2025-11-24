// Problem: CF 2122 C - Manhattan Pairs
// https://codeforces.com/contest/2122/problem/C

/*
C. Manhattan Pairs
time limit per test2 seconds
memory limit per test256 megabytes

Algorithm/Technique: Greedy + Sorting
Approach:
- For each point, we sort points by x-coordinate and divide into two groups (left and right).
- Then we sort again by y-coordinate and divide into two groups (bottom and top).
- We then pair points from group combinations such that we maximize Manhattan distance.
- This is a greedy strategy: pairing points with opposite x and y groupings to maximize differences.

Time Complexity: O(n log n) per test case due to sorting operations
Space Complexity: O(n) for storing points and groups

Input:
Each test contains multiple test cases. The first line contains the number of test cases
t (1≤t≤10^4). The description of the test cases follows.
The first line of each test case contains a single even integer n (2≤n≤2⋅10^5) — the number of points.
The i-th of the next n lines contains two integers xi and yi (−10^6≤xi,yi≤10^6) — the coordinates of the i-th point.
It is guaranteed that the sum of n over all test cases does not exceed 2⋅10^5.

Output:
For each test case, output n/2 lines, the i-th line containing two integers ai and bi — the indices of points in the i-th pair.
If there are multiple solutions, print any of them.
*/

import java.util.*;

public class Main {
    static class Point {
        int x, y, index;
        String groupx, groupy;
        Point(int x, int y, int index) { 
            this.x = x; 
            this.y = y; 
            this.index = index; 
        }
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt();
            Point[] pts = new Point[n];
            for (int i = 0; i < n; i++)
                pts[i] = new Point(sc.nextInt(), sc.nextInt(), i + 1);
            
            // Sort points by x-coordinate to form left and right groups
            Arrays.sort(pts, Comparator.comparingInt(p -> p.x));
            for (int i = 0; i < n / 2; i++) pts[i].groupx = "xl";
            for (int i = n / 2; i < n; i++) pts[i].groupx = "xr";
            
            // Sort points by y-coordinate to form top and bottom groups
            Arrays.sort(pts, Comparator.comparingInt(p -> p.y));
            for (int i = 0; i < n / 2; i++) pts[i].groupy = "yl";
            for (int i = n / 2; i < n; i++) pts[i].groupy = "yr";
            
            // Group points according to their x and y group assignments
            ArrayList<Point> a = new ArrayList<>(), b = new ArrayList<>(), c = new ArrayList<>(), d = new ArrayList<>();
            for (Point p : pts) {
                if (p.groupx.equals("xl") && p.groupy.equals("yl")) a.add(p); // bottom-left
                else if (p.groupx.equals("xl") && p.groupy.equals("yr")) b.add(p); // top-left
                else if (p.groupx.equals("xr") && p.groupy.equals("yl")) c.add(p); // bottom-right
                else d.add(p); // top-right
            }
            
            // Pair points from appropriate groups to maximize Manhattan distance
            for (int i = 0; i < a.size(); i++) System.out.println(a.get(i).index + " " + d.get(i).index);
            for (int i = 0; i < b.size(); i++) System.out.println(b.get(i).index + " " + c.get(i).index);
        }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/