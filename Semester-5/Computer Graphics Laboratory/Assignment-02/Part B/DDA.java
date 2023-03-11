package PACK1.LINE_ALGORITHMS;

import java.awt.*;
import java.lang.Math;
import PACK1.UTILITIES.*;

public class DDA {
    public void makeLine(Graphics g,int X0,int Y0,int X1,int Y1,Color C) {
        int dx=0,dy=0,Steps=0,a=0;
        double incrementX=0,incrementY=0,x=(double)X0,y=(double)Y0;
        
        dx = X1-X0;
        dy = Y1-Y0;

        if(Math.abs(dy)>Math.abs(dx)) Steps = Math.abs(dy);
        else Steps = Math.abs(dx);

        incrementX = ((double)dx/Steps);
        incrementY = ((double)dy/Steps);
        
        PlotPoint k = new PlotPoint();
        while(a <= Steps) {
            k.plot(g,Math.round(x),Math.round(y),C);

            x = x + incrementX;
            y = y + incrementY;

            a++;
        }
    }
}