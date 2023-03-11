import java.util.*;
//import PrimeChecker;

public class Prg {
      public static void main(String args[]) {
            int n;

            Scanner sc= new Scanner(System.in);    //System.in is a standard input stream 
            System.out.print("Give a positive integer to check if it is prime: "); 
            n = sc.nextInt();
            sc.close();

            PrimeChecker a = new PrimeChecker();
            a.CheckIfPrime(n);
      }
}