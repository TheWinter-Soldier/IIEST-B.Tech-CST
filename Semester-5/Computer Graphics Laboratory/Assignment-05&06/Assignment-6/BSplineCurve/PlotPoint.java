package PACK1.UTILITIES;

import java.awt.*;

public class PlotPoint {
    public void plot(Graphics g,double x,double y,Color C) {
        g.setColor(C);
        g.fillOval((int)((x-(VaryPoint.sigma/5))*(double)Magnifier.delta),(int)((y+(VaryPoint.sigma/5))*(double)(-Magnifier.delta)),(int)(((VaryPoint.sigma*2)/5)*(double)Magnifier.delta),(int)(((VaryPoint.sigma*2)/5)*(double)Magnifier.delta));
    }
}