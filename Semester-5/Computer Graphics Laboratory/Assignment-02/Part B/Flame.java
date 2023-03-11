package INCENDIARY;

import java.awt.*;
import java.lang.Math;
import PACK1.UTILITIES.*;

public class Flame {
    static int flameHeight = 0;

    public void lightCandle(Graphics g,int x,int y) {
        
        g.translate(x*Magnifier.delta,-y*Magnifier.delta);
        
        DDAforFlame a = new DDAforFlame();
        for(int i = -3;i<4;i++) {
            a.makeLine(g,0,0,i,(int)Math.pow(i,4)/10);
        }

        DDAforFlame b = new DDAforFlame();
        for(int i = -3;i<4;i++) {
            b.makeLine(g,0,0,i,(int)((30 - Math.pow(i,4)/5) + flameHeight%10));
        }
        
        flameHeight++;
    }
}