package PACK1.CURVE_ALGORITHMS;

import java.awt.*;
import java.lang.Math;
import PACK1.UTILITIES.*;

public class MidPointCDA {
    public void makeCircle(Graphics g,int Xc,int Yc,int r,Color C) {
        g.translate(Xc*Magnifier.delta,-(Yc*Magnifier.delta));

        double P = 0.0,x=0.0,y=0.0;
        
        P = (double)5/4 - (double)r;
        //P = (double)(1 - r);

        PlotPoint k = new PlotPoint();
        x = 0.0;
        y = (double)r;
        while(x<=y) {
            k.plot(g,x,y,C);
            k.plot(g,-x,y,C);
            k.plot(g,x,-y,C);
            k.plot(g,-x,-y,C);
            k.plot(g,y,x,C);
            k.plot(g,-y,x,C);
            k.plot(g,y,-x,C);
            k.plot(g,-y,-x,C);

            if(P<=0.0) {
                P += (2*x + 3);
            }
            else {
                P += (2*(x-y) + 5);

                y -= 1.0;
            }

            x+=1.0;
        }
    }
}