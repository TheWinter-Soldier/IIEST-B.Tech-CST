package PACK1;

import java.util.*;
import PACK1.PACK2.*;

public class BasicCal {
  public static void main(String args[]) {
    int l, a, b;

    Scanner sc= new Scanner(System.in);    //System.in is a standard input stream 
    System.out.print("Press 1 if you want to multiply or 2 if you want to add two numbers: "); 
    l = sc.nextInt();

    System.out.print("Give First number: ");
    a = sc.nextInt();
    System.out.print("Give First number: ");
    b = sc.nextInt();
    
    sc.close();

    if(l==2) {
      Add x = new Add();
      x.FindSum(a,b);
    }
    else {
      Mul y = new Mul();
      y.FindProd(a,b);
    }
  }
}