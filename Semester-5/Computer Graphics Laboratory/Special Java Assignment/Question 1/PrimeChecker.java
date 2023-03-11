import java.lang.Math;

public class PrimeChecker {
      public void CheckIfPrime(int n) {
            int i=0;
            boolean flag = false;

            for(i=2;i <= Math.sqrt(n);++i) {
               if(n % i == 0) {                 // condition for nonprime number
                 flag = true;
                 break;
               }
            }

            if(!flag) System.out.println(n + " is a Prime number.");
            else System.out.println(n + " is not a Prime number.");
      }
}