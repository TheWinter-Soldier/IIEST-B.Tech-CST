package PACK1.CURVE_ALGORITHMS;

import java.awt.*;
import java.lang.Math;
import java.math.BigDecimal;
import java.math.RoundingMode;
import PACK1.UTILITIES.*;

public class BezierCurve {
    public static int n=10;                 //Number of control-points
    public static double Precision=0.25;    //Precision of the curve

    public static int[] cX = new int[n];    //X Co-ords. of control-points
    public static int[] cY = new int[n];    //Y Co-ords. of control-points

    private int Factorial(int n1) {
        int res = 1;

        if(n1==0) {
            return 1;
        }

        for(int i=2;i<=n1;i++) {
            res = res*i;
        }
        
        return res;
    }

    private int Combination(int n2,int r) {
        return Factorial(n2)/(Factorial(r)*Factorial(n2 - r));
    }

    private static double round(double value,int places) {
        if(places<0) throw new IllegalArgumentException();
    
        BigDecimal bd = new BigDecimal(Double.toString(value));
        bd = bd.setScale(places,RoundingMode.HALF_UP);
        return bd.doubleValue();
    }
    
    public void drawCurve(Graphics g) {
        int k=0;
        double u = 0.0;
        double steps = 1/Precision;
        double[] x = new double[(int)steps+1];
        double[] y = new double[(int)steps+1];

        while(u<=1.0) {
            x[k] = 0;
            y[k] = 0;
            for(int i=0;i<n;i++) {
                x[k] += Combination(n-1,i)*Math.pow(1.0-u,n-1-i)*Math.pow(u,i)*cX[i];
                y[k] += Combination(n-1,i)*Math.pow(1.0-u,n-1-i)*Math.pow(u,i)*cY[i];
            }
            PlotPoint a = new PlotPoint();
            a.plot(g,x[k],y[k],Color.MAGENTA);

            k++;
            u = round((u+Precision),8);
            //System.out.println(u);
        }
    }
}