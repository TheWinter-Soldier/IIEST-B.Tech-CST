package PACK1;

import PACK1.PACK2.*;
import PACK1.PACK2.PACK3.Third;

public class First {
      public static void main(String args[]) {
            System.out.println("Hello,");

            Second p = new Second();
            p.f1();

            Second_D q = new Second_D();
            q.fd();
            q.f1();

            Third r = new Third();
            r.f2();
      }
}
