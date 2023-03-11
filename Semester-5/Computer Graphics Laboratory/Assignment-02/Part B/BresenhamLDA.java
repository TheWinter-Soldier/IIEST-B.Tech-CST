package PACK1.LINE_ALGORITHMS;

import java.awt.*;
import java.lang.Math;
import PACK1.UTILITIES.*;

public class BresenhamLDA {
    public void makeLine(Graphics g,int X0,int Y0,int X1,int Y1,Color C) {
        double dx=0.0,dy=0.0,P=0.0,x=0.0,y=0.0;
        double m = (double)(Y1-Y0)/(X1-X0);
        
        PlotPoint k = new PlotPoint();
        if(Math.abs(m)<1.0) {
            x = (double)(Math.min(X0,X1));
            if(x==(double)X0) y = (double)Y0;
            else y = (double)Y1;
            
            dx = (double)(Math.max(X0,X1) - Math.min(X0,X1));
            if(x==(double)X0) dy = (double)(Y1-Y0);
            else dy = (double)(Y0-Y1);
            if(m>0) {
                P = 2*dy - dx;

                while((int)x<=Math.max(X0,X1)) {
                    k.plot(g,x,y,C);

                    if(P>=0.0) {
                        x+=1.0;
                        y+=1.0;

                        P = P + 2*(dy - dx);
                    }
                    else {
                        x+=1.0;

                        P = P + 2*dy;
                    }
                }
            }
            else if(m<0) {
                P = 2*dy - dx;

                while((int)x<=Math.max(X0,X1)) {
                    k.plot(g,x,y,C);

                    if(P>=0.0) {
                        x+=1.0;

                        P = P + 2*dy;
                    }
                    else {
                        x+=1.0;
                        y-=1.0;

                        P = P + 2*(dy + dx);
                    }
                }
            }
        }                                        //When Increment of x is greater than increment of y
        else if(Math.abs(m)>1.0) {
            y = (double)(Math.min(Y0,Y1));
            if(y==(double)Y0) x = (double)X0;
            else x = (double)X1;
            
            dy = (double)(Math.max(Y0,Y1) - Math.min(Y0,Y1));
            if(y==(double)Y0) dx = (double)(X1-X0);
            else dx = (double)(X0-X1);
            
            if(m>0) {
                P = 2*dx - dy;

                while((int)y<=Math.max(Y0,Y1)) {
                    k.plot(g,x,y,C);

                    if(P>=0.0) {
                        x+=1.0;
                        y+=1.0;

                        P = P + 2*(dx - dy);
                    }
                    else {
                        y+=1.0;

                        P = P + 2*dx;
                    }
                }
            }
            else if(m<0) {
                P = 2*dx + dy;

                while((int)y<=Math.max(Y0,Y1)) {
                    k.plot(g,x,y,C);

                    if(P>=0.0) {
                        y+=1.0;

                        P = P + 2*dx;
                    }
                    else {
                        x-=1.0;
                        y+=1.0;

                        P = P + 2*(dx + dy);
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