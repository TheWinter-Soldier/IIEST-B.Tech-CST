package PACK1.LINE_ALGORITHMS;

import java.awt.*;
import java.lang.Math;
import PACK1.UTILITIES.*;

public class MidPointLDA {
    public void makeLine(Graphics g,int X0,int Y0,int X1,int Y1,Color C) {
        int dx=0,dy=0;
        double P=0.0,x=0.0,y=0.0;

        dx = X1-X0;
        dy = Y1-Y0;

        double m = ((double)dy/dx);
         
        PlotPoint k = new PlotPoint();
        if(Math.abs(m)<1) {
            x = (double)(Math.min(X0,X1));
            if(x==(double)X0) y = (double)Y0;
            else y = (double)Y1;
            
            if(m>0) {
                P = 0.5 - m;
                
                while((int)x<=Math.max(X0,X1)) {
                    k.plot(g,x,y,C);

                    if(P>=0.0) {
                        x+=1.0;

                        P = P - m;
                    }
                    else {
                        x+=1.0;
                        y+=1.0;

                        P = P + 1.0 - m;
                    }
                }
            }
            else if(m<0) {
                P = -0.5 - m;
                
                while((int)x<=Math.max(X0,X1)) {
                    k.plot(g,x,y,C);

                    if(P>0.0) {
                        x+=1.0;
                        y-=1.0;

                        P = P - 1.0 - m;
                    }
                    else {
                        x+=1.0;

                        P = P - m;
                    }
                }
            }
        }                                        //When Increment of x is greater than increment of y
        else if(Math.abs(m)>1) {
            y = (double)(Math.min(Y0,Y1));
            if(y==(double)Y0) x = (double)X0;
            else x = (double)X1;
            
            if(m>0) {
                P = 1.0 - (m/2);

                while((int)y<=Math.max(Y0,Y1)) {
                    k.plot(g,x,y,C);

                    if(P>=0.0) {
                        x+=1.0;
                        y+=1.0;

                        P = P + 1.0 - m;
                    }
                    else {
                        y+=1.0;

                        P = P + 1.0;
                    }
                }
            }
            else if(m<0) {
                P = 1.0 + (m/2);

                while((int)y<=Math.max(Y0,Y1)) {
                    k.plot(g,x,y,C);

                    if(P>0.0) {
                        x-=1.0;
                        y+=1.0;

                        P = P + 1.0 + m;
                    }
                    else {
                        y+=1.0;

                        P = P + 1.0;
                    }
                }
            }
        }                                        //When Increment of x is greater than increment of y
        else if(Math.abs(m)==1) {
            x = (double)(Math.min(X0,X1));
            if(x==(double)X0) y = (double)Y0;
            else y = (double)Y1;
            
            while((int)x<=Math.max(X0,X1)) {
                k.plot(g,x,y,C);
                if(m==1.0) {
                    x+=1.0;
                    y+=1.0;
                }
                else if(m==(-1.0)) {
                    x+=1.0;
                    y-=1.0;
                }
            }
        }                                        //When increment of x and y are same
    }
}