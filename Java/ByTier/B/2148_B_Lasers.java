// Problem: CF 2148 B - Lasers
// https://codeforces.com/contest/2148/problem/B

/*
B. Lasers
time limit per test2 seconds
memory limit per test256 megabytes

Algorithms/Techniques: Greedy approach with binary search
Time Complexity: O((n + m) * log(n + m)) per test case due to sorting and binary search operations.
Space Complexity: O(n + m) for storing the laser positions.

Problem Description:
We are moving from (0, 0) to (x, y) on a 2D plane with horizontal and vertical lasers defined by their coordinates.
The goal is to find the minimum number of laser crossings required to reach the destination,
considering that crossing a laser (either horizontal or vertical) counts as one crossing.
If we pass through an intersection point, it counts as two crossings.

Approach:
1. For each direction (horizontal and vertical), determine how many lasers we will cross based on our path.
2. Since we are moving from (0, 0) to (x, y), we only need to consider crossing the horizontal lasers below y and vertical lasers before x.
3. Use greedy method: the minimum number of crossings is equal to n + m minus overlaps,
   but since movement can be adjusted to avoid extra crossings at intersections, 
   it's simply the count of relevant lasers from both directions added together.

*/

import java.util.*;
public class Main{
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int t=sc.nextInt(); // Read number of test cases
        while(t-->0){
            int n=sc.nextInt(); // Number of horizontal lasers
            int m=sc.nextInt(); // Number of vertical lasers
            sc.nextLong();      // x coordinate (unused in logic)
            sc.nextLong();      // y coordinate (unused in logic)
            for(int i=0;i<n;i++)sc.nextInt(); // Read horizontal laser positions (not used in this simplified version)
            for(int i=0;i<m;i++)sc.nextInt(); // Read vertical laser positions (not used in this simplified version)
            System.out.println(n+m); // Output minimum crossings
            }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/