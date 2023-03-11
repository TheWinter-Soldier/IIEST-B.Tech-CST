package INCENDIARY;

import java.awt.*;
import java.lang.Math;
import java.util.Arrays;
import java.util.List;
import PACK1.UTILITIES.*;

public class DDAforFlame {
    List<Color> Palette = Arrays.asList(new Color(7, 7, 7), new Color(31, 7, 7), new Color(47, 15, 7),
            new Color(71, 15, 7), new Color(87, 23, 7), new Color(103, 31, 7), new Color(119, 31, 7),
            new Color(143, 39, 7), new Color(159, 47, 7), new Color(175, 63, 7), new Color(191, 71, 7),
            new Color(199, 71, 7), new Color(223, 79, 7), new Color(223, 87, 7), new Color(223, 87, 7),
            new Color(215, 95, 7), new Color(215, 95, 7), new Color(215, 103, 15), new Color(207, 111, 15),
            new Color(207, 119, 15), new Color(207, 127, 15), new Color(207, 135, 23), new Color(207, 135, 23),
            new Color(199, 135, 23), new Color(199, 143, 23), new Color(199, 151, 31), new Color(191, 159, 31),
            new Color(191, 159, 31), new Color(191, 167, 39), new Color(191, 167, 39), new Color(191, 175, 47),
            new Color(183, 175, 47), new Color(183, 183, 47), new Color(183, 183, 55), new Color(207, 207, 111),
            new Color(223, 223, 159), new Color(239, 239, 199), new Color(255, 255, 255));

    public void makeLine(Graphics g,int X0,int Y0,int X1,int Y1) {
        int dx=0, dy=0, Steps=0, a=0;
        double incrementX=0, incrementY=0, x = (double)X0, y = (double)Y0;

        dx = X1-X0;
        dy = Y1-Y0;

        Steps = Math.max(Math.abs(dx),Math.abs(dy));

        incrementX = ((double)dx/Steps);
        incrementY = ((double)dy/Steps);

        PlotPoint k = new PlotPoint();
        while(a<=Steps) {
            Color c;
            if(a<38) {
                c = Palette.get(a);
            }
            else {
                c = Palette.get(37);
            }
            k.plot(g,Math.round(x),Math.round(y),c);

            x += incrementX;
            y += incrementY;

            a++;
        }
    }
}