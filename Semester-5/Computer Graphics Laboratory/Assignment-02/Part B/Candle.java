package INCENDIARY;

import java.awt.*;
import PACK1.LINE_ALGORITHMS.*;

public class Candle {
    public void makeCandle(Graphics g,int x,int y,int width,int height) {
        //Here, (x,y) is the co-ordinate of the left bottom corner of the candle
        MidPointLDA a = new MidPointLDA();
        for(int i=x;i < x+width;i++) {
            a.makeLine(g,i,y,i,y+height,Color.WHITE);
        }
        
        //The wick
        BresenhamLDA b = new BresenhamLDA();
        b.makeLine(g,x+((width-1)/2),y+height,x+((width-1)/2),y+height+4,Color.black);
    }
}