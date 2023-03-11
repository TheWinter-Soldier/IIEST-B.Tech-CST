import java.awt.*;
import java.awt.Color;

public class PlotPoint {
    public void plot(Graphics g,int x,int y,Color C) {
        g.setColor(C);
        g.fillOval(x-1,y-1,2,2);
    }
}