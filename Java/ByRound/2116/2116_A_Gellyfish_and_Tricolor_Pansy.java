// Problem: CF 2116 A - Gellyfish and Tricolor Pansy
// https://codeforces.com/contest/2116/problem/A

/**
 * Problem: A. Gellyfish and Tricolor Pansy
 * 
 * The game involves two players (Gellyfish and Flower) with HP values a and b respectively,
 * and their respective knights with HP values c and d.
 * 
 * Players alternate turns (odd k = Gellyfish's turn, even k = Flower's turn).
 * On each turn:
 * - If it's Gellyfish's turn and his knight is alive:
 *   - He can attack Flower (reduce b by 1) or attack Flower’s knight (reduce d by 1)
 * - If it's Flower's turn and her knight is alive:
 *   - She can attack Gellyfish (reduce a by 1) or attack Gellyfish’s knight (reduce c by 1)
 *
 * The goal is to determine who will win given optimal play.
 *
 * Key insight:
 * Since both players act optimally, we analyze the total effective HP available for each player,
 * which is min(a,c) + min(b,d). If Gellyfish has more such combined health, he wins; otherwise Flower does.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
import java.util.*;

public class contest {
  public static void main(String[] args) {
    Scanner sc= new Scanner(System.in);
    int t = sc.nextInt(); // Read number of test cases
    sc.nextLine(); // Consume the newline after reading 't'
     while (t-- > 0) { // Process each test case
      int a=sc.nextInt(),b=sc.nextInt(),c=sc.nextInt(),d=sc.nextInt(); // Read HP values for Gellyfish, Flower, and their knights
      
      int mina=Math.min(a,c); // Effective HP of Gellyfish: min of his own HP and knight HP
      int minb=Math.min(b, d); // Effective HP of Flower: min of her own HP and knight HP
      
      if(mina>=minb) System.out.println("Gellyfish"); // If Gellyfish has higher or equal effective HP, he wins
      else if(mina<minb)System.out.println("Flower");  // Otherwise, Flower wins
        
      System.out.flush(); // Flush output buffer, though not required for most Java IDEs
     }
  }
}


// https://github.com/VaHiX/CodeForces/