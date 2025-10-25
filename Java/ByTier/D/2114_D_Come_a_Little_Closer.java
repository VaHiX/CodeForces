// Problem: CF 2114 D - Come a Little Closer
// https://codeforces.com/contest/2114/problem/D

/*
 * Problem: D. Come a Little Closer
 *
 * Purpose:
 *   Given n monsters on a large grid (10^9 x 10^9), we can move at most one monster to an empty cell,
 *   then select a rectangle that contains all remaining monsters. The cost is the area of the rectangle.
 *   We aim to minimize this cost by possibly moving one monster optimally.
 *
 * Algorithm:
 *   - Sort monsters by x-coordinates and y-coordinates separately.
 *   - Consider four possible scenarios for the optimal rectangle:
 *     1. Use all original rectangles (no moves).
 *     2. Remove the topmost monster by moving it (and compute new min rectangle).
 *     3. Remove the bottommost monster by moving it.
 *     4. Remove the leftmost monster by moving it.
 *     5. Remove the rightmost monster by moving it.
 *   - For each scenario, compute a bounding rectangle and its area.
 *
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing coordinates.
 */

import java.util.*;
public class Main {
  public static long calc(int minx , int maxx , int miny , int maxy , long n){
    long ht = maxy-miny+1; // Height of rectangle
    long wt = maxx-minx+1; // Width of rectangle
    if(ht*wt==n-1){ // If the area is exactly one less than total monsters, we might have moved one
      return Math.min((ht+1)*wt , (wt+1)*ht); // Return minimal area when expanded by 1 unit in either direction
    }
    return ht*wt; // Otherwise return original area
  }

  public static void help(int[][] x , int[][] y){
    long n = x.length;
    long val= calc(x[0][1],x[x.length-1][1] , y[0][1], y[y.length-1][1] ,n); // Initial bounding box area
    if(x.length==1){ // If only one monster, no need to move or adjust
      System.out.println(val);
      return;
    }
    
    int[] idx = new int[]{x[0][0] , x[x.length-1][0] , y[0][0] , y[y.length-1][0]}; // Indexes of extreme points
    
    for(int i=0 ; i<4 ; i++){ // Try all four corners to simulate removal from rectangle
      int minx = x[0][0]==idx[i] ? x[1][1] : x[0][1]; // Adjust min x after removing one point
      int maxx = x[x.length-1][0]==idx[i] ? x[x.length-2][1] : x[x.length-1][1]; // Adjust max x
      int miny = y[0][0]==idx[i] ? y[1][1] : y[0][1]; // Adjust min y
      int maxy= y[y.length-1][0]==idx[i] ? y[y.length-2][1]: y[y.length-1][1]; // Adjust max y
      val = Math.min(val , calc(minx,maxx , miny,maxy , x.length)); // Compute and track minimum
    }
    System.out.println(val);
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int t = sc.nextInt();
    while(t>0){
      int n = sc.nextInt(); // Read number of monsters
      int[][] x = new int[n][2]; // Store x-coordinates with indices
      int[][] y = new int[n][2]; // Store y-coordinates with indices
      for(int i=0 ; i<n ; i++){
        x[i][0] = y[i][0] = i; // Track original index
        x[i][1] = sc.nextInt(); // Read x coordinate
        y[i][1] = sc.nextInt(); // Read y coordinate
      }
      
      Arrays.sort(x , (a,b)->a[1]-b[1]); // Sort by x-coordinate
      Arrays.sort(y , (a,b)->a[1]-b[1]); // Sort by y-coordinate
      
      help(x, y); // Perform analysis
      t--;
    }
  }
}


// https://github.com/VaHiX/CodeForces/