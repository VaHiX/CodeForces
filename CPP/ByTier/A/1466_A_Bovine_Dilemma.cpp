// Problem: CF 1466 A - Bovine Dilemma
// https://codeforces.com/contest/1466/problem/A

/*
A. Bovine Dilemma
Algorithm: For each pair of points on the river (x-axis), calculate the difference in x-coordinates and store in a set to count unique differences. Then, for every pair of such differences, compute the area of the triangle formed with the point (0, 1) as the third vertex. The area of a triangle with base b and height h is 0.5 * b * h. Since height is always 1, we just need to store unique products of differences.

Time Complexity: O(n^2 log n) per test case due to nested loops and set insertion.
Space Complexity: O(n^2) for storing the differences in the set.
*/

#include <cstdio>
#include <set>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::set<long> s;
    for (long p = 0; p < n; p++) {
      for (long q = p + 1; q < n; q++) {
        s.insert(a[q] - a[p]); // Store all unique differences between x-coordinates
      }
    }
    std::set<long> areas;
    for (auto it1 = s.begin(); it1 != s.end(); ++it1) {
      for (auto it2 = s.begin(); it2 != s.end(); ++it2) {
        // For each pair of differences, compute the area as 0.5 * diff1 * diff2
        // But since we're counting unique areas, not actual values, we just store product 
        // and divide by 2 later if needed (but better to compute directly with doubles or long double)
        // Actually, using integer arithmetic: for each two differences a and b,
        // area = 0.5 * a * b => 2 * area = a * b
        // So store a * b in set to avoid duplicates from 0.5 * (a * b) -> we'll use a * b / 2.0
        // But for integral computation:
        // if diff1 and diff2 are integers, area = 0.5 * diff1 * diff2  
        // To count unique areas: store all possible integer products in a set of doubles or longs,
        // but we can just precompute the final multiplication to be safe in case of rounding
        // The most direct way is to compute full product and insert into a set, 
        // then convert to area by dividing by 2.0.
        // This is inefficient to do with long doubles here, better keep product values as integer,
        // and use an appropriate map/set for final count.
        areas.insert((*it1) * (*it2)); // Insert all pair-wise products of differences
      }
    }
    // The number of unique areas corresponds to the size of the set divided by 2
    // But since we're dealing with integer differences, product of two positive integers
    // is always integer, so let's recompute as: for every a * b in our new set,
    // area = 0.5 * (a * b). 
    // We count distinct values, but the question is, should we count actual area? or just 
    // number of possible combinations? 
    // Let’s clarify: the problem asks for number of different areas.
    // Therefore, let's reconsider:
    // All triangles have height 1 (from point (0,1)), base = difference in x-coordinates between two trees
    // Area = 0.5 * base1 * base2 where base1 and base2 are distances from origin along x-axis with third vertex at (0,1)
    // Let the triangle be formed by points (x_i, 0), (x_j, 0) and (0, 1).
    // Base of the triangle = |x_j - x_i|; height = 1; area = 0.5 * |x_j - x_i|
    // But wait: if we have two such triangles with bases b1 and b2, their respective areas will be 
    // 0.5*b1 and 0.5*b2 => they're different if b1 != b2.
    // That's not right either. We form triangles using points on x-axis and one fixed point (0,1).
    // So area = 0.5 * base1 * base2, where the triangle's vertices are
    // two points from x-axis: (x1,0), (x2,0) and fixed point (0,1)
    // Using cross product formula or determinants: Area = 0.5 * sqrt( ((x1 - 0)^2 + (0-1)^2)*((x2 - 0)^2 + (0-1)^2) - (x1*x2+0*0+1*0)^2 ) 
    // That leads to a complicated formula.
    
    // Simpler approach: Area = 0.5 * base * height
    // Triangle formed by: (0, 1), (x1, 0), (x2, 0) => 
    // height = 1; base = distance between x1 and x2 = |x1 - x2|
    // Total area = 0.5 * |x1 - x2|
    
    // But since three points are chosen for triangle: (0,1), (x1,0), (x2,0) we can consider:
    // The area of a triangle with vertices at (0, h), (x1, 0), (x2, 0) where h = 1.
    // Area = 0.5 * |x1 - x2| * 1 = 0.5 * |x1 - x2|
    
    // But that's only accounting for one height.
    // Another interpretation: three points in a plane with base on x-axis.
    // Triangle has three vertices: (0,1), (x1,0), (x2,0)
    // Let's assume x1 < x2; Area = 0.5 * (x2 - x1) * 1 = 0.5 * (x2 - x1) 

    // So for each pair of points (a[i], a[j]), we calculate area = 0.5 * (a[j] - a[i])
    // and store unique values.
    
    // Let’s rewrite inner loop logic:
    std::set<double> unique_areas;  
    for (auto it1 = s.begin(); it1 != s.end(); ++it1) {
      for (auto it2 = s.begin(); it2 != s.end(); ++it2) {
        if (*it1 < *it2) { // Avoid trivial case and ensure positive area by ordering
          double area = 0.5 * (*it1) * (*it2); 
          unique_areas.insert(area);
        }
      }  
    }  

    // However, looking again at example:
    // For points [1,2,4,5]: 
    // Pairs of x differences: 1, 2, 3, 1, 4, 1 => these are (2-1),(4-1),(5-1),(4-2),(5-2),(5-4) = 1,3,4,2,3,1
    // Triangle area = 0.5 * difference1 * difference2 (assuming we're using two segments)
    // But that approach is wrong.
    // Triangle formed by vertices A(x_a,0), B(x_b,0), C(0,1) has area:
    // Area = 0.5 * (x_a - x_b)^2 - (0-0)^2 = 0.5 * |x_a - x_b|
    
    // Wait no, it is triangle with base on x-axis from x_i to x_j and third vertex at (0,1)
    // Area = 0.5 * |x_j - x_i| * 1 = 0.5 * |x_j - x_i|

    // Now correct algorithm:
    std::set<double> unique_area;
    for (auto it1 = s.begin(); it1 != s.end(); ++it1) {
      for (auto it2 = s.begin(); it2 != s.end(); ++it2) {
        double base_diff = *it1;  // difference between x-coordinates of two points
        double area = 0.5 * base_diff;
        if (base_diff > 0) {         // Only nonzero areas
          unique_area.insert(area);
        }
      }
    }

    printf("%ld\n", unique_area.size());
  }
}


// https://github.com/VaHiX/codeForces/