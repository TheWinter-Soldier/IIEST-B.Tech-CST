package PACK1.CURVE_ALGORITHMS;

import java.awt.*;
import java.lang.Math;
import PACK1.UTILITIES.*;

public class MidPointEDA {
    public void makeEllipse(Graphics g,int Xc,int Yc,int rX,int rY,double angle,Color C) {
        g.translate(Xc*Magnifier.delta,-(Yc*Magnifier.delta));
        
        double pi=3.14159;
        double rot = 3.14159*(angle%360)/180;

        double P1 = 0.0,P2 = 0.0,x=0.0,y=0.0;
        double a = (((rX*rX)*(rY*rY))/(rX*rX + rY*rY));
        
        P1 = (double)((rX*rX)/4 + rY*rY - rX*rX*rY);
        PlotPoint k1 = new PlotPoint();
        x = 0.0;
        y = (double)rY;
        while(x*rY*rY <= y*rX*rX) {
            k1.plot(g,(x*Math.cos(rot) - y*Math.sin(rot)),(x*Math.sin(rot) + y*Math.cos(rot)),C);
            k1.plot(g,((-x)*Math.cos(rot) - y*Math.sin(rot)),((-x)*Math.sin(rot) + y*Math.cos(rot)),C);
            k1.plot(g,(x*Math.cos(rot) - (-y)*Math.sin(rot)),(x*Math.sin(rot) + (-y)*Math.cos(rot)),C);
            k1.plot(g,((-x)*Math.cos(rot) - (-y)*Math.sin(rot)),((-x)*Math.sin(rot) + (-y)*Math.cos(rot)),C);

            if(P1 > 0.0) {
                P1 += ((2*x + 3)*rY*rY - 2*(y-1)*rX*rX);

                y-=1.0;
            }
            else {
                P1 += ((2*x + 3)*rY*rY);
            }

            x+=1.0;
        }                              //For Region-I

        P2 = (double)(rY*rY*(x + 0.5)*(x + 0.5) + rX*rX*(y - 1.0)*(y - 1.0) - rX*rX*rY*rY);
        PlotPoint k2 = new PlotPoint();
        /*x = (double)rX;
        y = 0.0;*/
        while(y>=0) {
            k2.plot(g,(x*Math.cos(rot) - y*Math.sin(rot)),(x*Math.sin(rot) + y*Math.cos(rot)),C);
            k2.plot(g,((-x)*Math.cos(rot) - y*Math.sin(rot)),((-x)*Math.sin(rot) + y*Math.cos(rot)),C);
            k2.plot(g,(x*Math.cos(rot) - (-y)*Math.sin(rot)),(x*Math.sin(rot) + (-y)*Math.cos(rot)),C);
            k2.plot(g,((-x)*Math.cos(rot) - (-y)*Math.sin(rot)),((-x)*Math.sin(rot) + (-y)*Math.cos(rot)),C);

            if(P2 <= 0.0) {
                P2 += (2*rY*rY*(x + 1) - (2*y - 3)*rX*rX);

                x+=1.0;
            }
            else {
                P2 -= (rX*rX*(2*y - 3));
            }

            y-=1.0;
        }                              //For Region-II
    }
}