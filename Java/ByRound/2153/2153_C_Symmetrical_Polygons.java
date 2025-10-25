// Problem: CF 2153 C - Symmetrical Polygons
// https://codeforces.com/contest/2153/problem/C

/*
C. Symmetrical Polygons

Algorithms/Techniques: Sorting, Greedy, Polygon Construction

Time Complexity: O(n log n) due to sorting, where n is the number of sticks.
Space Complexity: O(n) for storing the array and auxiliary data structures.

Task:
Given n sticks with lengths a_i, find the maximum possible perimeter of a
non-degenerate, symmetrical, and strictly convex polygon that can be formed
using a subset of these sticks.

Key Observations:
- For a polygon to be convex and non-degenerate, the sum of any (n-1) sides must be greater than the remaining side.
- For symmetry, certain groupings of equal-length sides are required.
- An isosceles triangle (3 sides with two equal) can form a symmetrical convex polygon.
- We prioritize forming larger polygons (with more sides) for maximum perimeter.

Approach:
1. Sort the array to group identical elements together.
2. Process the sorted array to build unique side lengths and count pairs.
   - If two sticks have the same length, they can be used together as a symmetric pair.
3. Use greedy approach: Try to form polygons using as many sides as possible, ensuring that
   the sum of smaller sides is greater than the largest side (triangle inequality).
4. If at least 3 valid sides can be arranged into a symmetric polygon, return their total perimeter,
   otherwise return 0.
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;
public class C {
    static BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in));
    public static void main(String[] args) throws IOException {
        StringTokenizer s1
                = new StringTokenizer(br.readLine());
        int t = Integer.parseInt(s1.nextToken());
        while (t-- > 0) {
            StringTokenizer s2
                    = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(s2.nextToken());
            int[] arr = new int[n];
            StringTokenizer s3
                    = new StringTokenizer(br.readLine());
            for (int i = 0; i < n; i++) arr[i] = Integer.parseInt(s3.nextToken());
            solve(arr, n);
        }
    }
    static void solve(int[] arr, int n) {
        Arrays.sort(arr); // O(n log n)
        long sum=0;
        int i=0,c=0;
        ArrayList<Integer> list=new ArrayList<>();
        while(i<n) {
            if(i==n-1 ||arr[i]!=arr[i+1]) list.add(arr[i++]); // Add single stick
            else if(arr[i]==arr[i+1]) { // If two sticks are same, pair them
                sum+=arr[i]+arr[i+1];
                i+=2;
                c+=2;
            }
        }
        int max1=0,max2=0;
        for(i=list.size()-1;i>0;i--) {
            if(sum+list.get(i-1)>list.get(i)) { // Check polygon inequality
                max1=list.get(i);
                max2=list.get(i-1);
                break;
            }
        }
        if(max1==0 &&!list.isEmpty() &&sum>list.getFirst()) max1=list.getFirst();  // If last element can form triangle with sum
        if(max1!=0) c++;
        if(max2!=0) c++;
        if(c<3) System.out.println(0);  // At least 3 sides needed to form polygon
        else System.out.println(sum+max1+max2);
    }
    static void print(int[] arr) {
        PrintWriter out=new PrintWriter(System.out);
        for (int i = 0; i < arr.length; i++)
            out.print(arr[i] + " ");
        out.print("\n");
        out.flush();
    }
}


// https://github.com/VaHiX/CodeForces/