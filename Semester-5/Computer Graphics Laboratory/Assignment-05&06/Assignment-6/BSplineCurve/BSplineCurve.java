package PACK1.CURVE_ALGORITHMS;

import java.awt.*;
import java.lang.Math;
import java.math.BigDecimal;
import java.math.RoundingMode;
import PACK1.UTILITIES.*;

public class BSplineCurve {
    public static int n = 20;               //1 less than the number of control-points
    public static int K = 5;                //Order of the curve
    public static double Precision=0.25;    //Parameter

    public static int[] cX = new int[n+1];  //X Co-ords. of control-points
    public static int[] cY = new int[n+1];  //Y Co-ords. of control-points

    private int Seg = n-K+2;                //Number of segments of the curve
    private int m = n+K;                    //Knot-vector is [t(0), t(1), t(2),....., t(m)]; There are total (m+1) knots

    private int t(int i) {
        if(i<K) {
            return 0;
        }
        else if((i>=K)&&(i<=n)) {
            return i-K+1;
        }
        else return n-K+2;
    }         //Knot-values

    private double f(int i,int j,double u) {
        if((t(j-1+i)-t(i)) != 0) {
            return ((u-t(i))/(t(j-1+i)-t(i)));
        }
        
        return 0;
    }

    private double g(int i,int j,double u) {
        return (1-f(i,j,u));
    }

    private double N(int i,int j,double u) {
        if(j==1) {
            if((u>=t(i))&&(u<=t(i+1))) {
                return 1;
            }
            else return 0;
        }
        else {
            return ((f(i,j,u)*N(i,j-1,u)) + (g(i+1,j,u)*N(i+1,j-1,u)));
        }
    }              //Cox-de Boor's recurssion or B-spline Basis Function or Blending Function

    private static double round(double value,int places) {
        if(places<0) throw new IllegalArgumentException();
    
        BigDecimal bd = new BigDecimal(Double.toString(value));
        bd = bd.setScale(places,RoundingMode.HALF_UP);
        return bd.doubleValue();
    }
    
    public void drawCurve(Graphics g) {
        int p=0;
        double u=0.0;
        int steps = (int)(Seg/Precision) + 1;
        double[] x = new double[steps];
        double[] y = new double[steps];

        while(u <= (double)Seg) {
            /*System.out.println();
            System.out.print("u=");
            System.out.print(u);
            System.out.println("--------------------------------------------------------------");*/
            x[p] = 0.0;
            y[p] = 0.0;
            for(int i=0;i < (n+1);i++) {
                /*System.out.print("i=");
                System.out.print(i);
                System.out.print(" :  ");*/
                x[p] += N(i,K,u)*cX[i];
                y[p] += N(i,K,u)*cY[i];
                
                /*System.out.print("CP:(");
                System.out.print(cX[i]);
                System.out.print(",");
                System.out.print(cY[i]);
                System.out.print(")");
                System.out.print("      ");
                System.out.print("N(i,K,u)=");
                System.out.print(N(i,K,u));
                System.out.print("          ");
                System.out.print("Int. val: (");
                System.out.print(x[p]);
                System.out.print(",");
                System.out.print(y[p]);
                System.out.println(")");*/
            }
            /*System.out.print("To plot: (");
            System.out.print(x[p]);
            System.out.print(",");
            System.out.print(y[p]);
            System.out.println(")");*/
            PlotPoint a = new PlotPoint();
            a.plot(g,x[p],y[p],Color.MAGENTA);

            p++;
            u = round((u+Precision),8);
        }
    }
}