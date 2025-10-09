// Problem: CF 2130 B - Pathless
// https://codeforces.com/contest/2130/problem/B

/*
B. Pathless
Algorithms/Techniques: Greedy, Array manipulation

Time Complexity: O(n) per test case
Space Complexity: O(1) - uses only a fixed-size array of size 3

The solution counts occurrences of 0s, 1s, and 2s in the input array.
It then checks if it's possible to rearrange these elements such that
Alice cannot reach exactly sum s by moving from index 1 to n.
If not possible, we output -1.
Otherwise, we construct a valid sequence by placing all 0s first,
then 2s, then 1s to satisfy the constraints.
*/
import java.util.*;
public class Main {
    public static void main(String[] args) {
      Scanner in = new Scanner(System.in);
      int t = in.nextInt();
      while(t-- > 0){
        int n = in.nextInt();
        int k = in.nextInt();
        int[] arr = new int[3]; // arr[0], arr[1], arr[2] count of each element
        int num = 0;
        for(int i = 0;i < n;i++){
          num = in.nextInt(); // read next number
          arr[num]++; // increment count for that number
        }
        // Check if it's impossible to achieve target sum 'k'
        if(arr[1]+2*arr[2] == k || arr[1] + 2*arr[2]+2 <= k){
          System.out.println(-1);
        }else{
          // Print 0s first
          for(int i = 0;i < arr[0];i++){
            System.out.print(0 + " ");
          }
          // Print 2s next
          for(int i = 0;i < arr[2];i++){
            System.out.print(2 + " ");
          }
          // Print 1s last
          for(int i = 0;i < arr[1];i++){
            System.out.print(1 + " ");
          }
          System.out.println();
        }
      }
  }
}


// https://github.com/VaHiX/codeForces/