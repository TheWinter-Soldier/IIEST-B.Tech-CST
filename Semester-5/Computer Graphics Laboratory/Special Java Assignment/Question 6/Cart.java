package PACK1.PACK2;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;

public class Cart {
    private int x1, x2, h, w;
    private Graphics G;
    
    public Cart(int a1,int a2,int a3,int a4,Graphics g) {
        G=g; 
        x1=a1; 
        x2=a2; 
        h=a3; 
        w=a4;
    }
    
    public void setVisible() {
        G.fillRect(x1,x2,h,w);
    }
    
    public void setInvisible() {}
    
    public void color_change(Color c) {}
}