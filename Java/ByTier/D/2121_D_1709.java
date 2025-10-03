// Problem: CF 2121 D - 1709
// https://codeforces.com/contest/2121/problem/D

/*
 * Problem: D. 1709
 * Purpose: Sort two arrays such that both arrays are strictly increasing and every element in array 'a' 
 *          is less than the corresponding element in array 'b'.
 * Algorithms:
 *   - Bubble sort-like approach to make arrays a and b strictly increasing.
 *   - For each position, if a[i] > b[i], swap elements at that index between arrays a and b.
 * Time Complexity: O(n^3) in worst case due to nested loops and bubble sort operations.
 * Space Complexity: O(n^2) for storing the operations (at most 1709 operations, each of size 2).
 */
import java.util.*;
public class D_1709{
    public static  void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while(t-->0){
            int n = sc.nextInt();
            int[] a = new int[n];
            for(int i=0; i<n; i++){
                a[i] = sc.nextInt();
            }
            int[] b = new int[n];
            for(int i=0; i<n; i++){
                b[i] = sc.nextInt();
            }
            List<int[]> list = new ArrayList<>();
            // Sort array 'a' in ascending order using bubble sort
            for(int i=0; i<n-1; i++){
                for(int j=1; j<n-i; j++){
                    if(a[j]<a[j-1]){
                        swap(a,j,j-1);
                        list.add(new int[]{1,j});
                    }
                }
            }
            // Sort array 'b' in ascending order using bubble sort
            for(int i=0; i<n-1; i++){
                for(int j=1; j<n-i; j++){
                    if(b[j]<b[j-1]){
                        swap(b,j,j-1);
                        list.add(new int[]{2,j});
                    }
                }
            }
            // Ensure all a[i] < b[i] by swapping when needed
            for(int i=0; i<n; i++){
                if(a[i]>b[i]){
                    int temp = a[i];
                    a[i] = b[i];
                    b[i] = temp;
                    list.add(new int[]{3,i+1});
                }
            }
            System.out.println(list.size());
            for(int[] e : list){
                System.out.println(e[0] + " " + e[1]);
            }
        }
    }
    public static void swap(int[] arr, int i, int j){
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}


// https://github.com/VaHiX/CodeForces/