// Problem: CF 2102 B - The Picky Cat
// https://codeforces.com/contest/2102/problem/B

/**
 * Problem: The Picky Cat
 * 
 * Task: Determine if it's possible to make the element at index 1 become the median of the array
 *       after performing any number of operations (multiplying any element by -1).
 * 
 * Algorithm:
 *   - For each test case, we consider the absolute values of elements.
 *   - We count how many elements in the array have smaller absolute values than the first element.
 *   - If this count is less than or equal to half the size of the array (rounded down), then it's possible
 *     to place the first element at the median position by flipping signs appropriately.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(n), due to the input array storage.
 */
import java.util.*;
public class Solution {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while(t-- >0) {
            int n = sc.nextInt();
            int[] arr = new int[n];
            for(int i=0; i<n; i++) {
                arr[i] = sc.nextInt(); // Read array elements
            }
            int a = arr[0]; // Store the first element
            int cnt = 0;
            for(int i=1; i<n; i++) {
                if(Math.abs(arr[i]) < Math.abs(a)) { // Count elements with smaller absolute value than first
                    cnt++;
                }
            }
            if(cnt <= (arr.length)/2) { // Check if it's possible to put a[0] at median
                System.out.println("Yes");
            }else {
                System.out.println("No");
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/