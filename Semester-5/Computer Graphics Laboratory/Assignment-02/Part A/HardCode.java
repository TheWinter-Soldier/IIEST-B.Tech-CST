package PACK1;

import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import PACK1.LINE_ALGORITHMS.*;
import PACK1.UTILITIES.*;

public class HardCode extends Applet implements ActionListener, MouseListener, MouseMotionListener, MouseWheelListener {
    int MaxY = 0;
    int MaxX = 0;

    Label L1 = new Label("Change size of Point :");
	Button B1 = new Button("+");
    Button B2 = new Button("-");
        
    public void init() {
        MaxY = getHeight();
        MaxX = getWidth();
            
        Color mycolor = new Color(128,255,128);
        setBackground(mycolor);

        add(L1);
		add(B1);
		add(B2);

        B1.addActionListener(this);
		B2.addActionListener(this);
    
        addMouseListener(this);
        addMouseMotionListener(this);
        addMouseWheelListener(this);
    }
        
    public void makeGrid(Graphics2D G) {
        G.translate(MaxX/2,MaxY/2);
        G.setColor(Color.black);
    
        int yCoord=0;
        for(int i=0;i < MaxX/2;i += Magnifier.delta) {
            G.drawLine(i,MaxY/2,i,-MaxY/2);
            if(Magnifier.delta>20 && i != 0) {
                G.drawString(String.valueOf(yCoord),5,i+14);
            } 
            yCoord--;
        }
        yCoord=0;
        for(int i=0;i > -MaxX/2;i -= Magnifier.delta) {
            G.drawLine(i,MaxY/2,i,-MaxY/2);
            if(Magnifier.delta>20 && i != 0) {
                G.drawString(String.valueOf(yCoord),5,i+14);
            }
            yCoord++;
        }
    
        int xCoord=0;
        for(int i=0;i < MaxY/2;i += Magnifier.delta) {
            G.drawLine(-MaxX/2,i,MaxX/2,i);
            if(Magnifier.delta>20 && i != 0) {
                G.drawString(String.valueOf(xCoord),i-10,15);
            }
            xCoord++;
        }
        xCoord=0;
        for(int i=0;i > -MaxY/2;i -= Magnifier.delta) {
            G.drawLine(-MaxX/2,i,MaxX/2,i);
            if(Magnifier.delta>20 && i != 0) {
                G.drawString(String.valueOf(xCoord),i-15,15);
            }
            xCoord--;
        }
    
        Color mycolor = new Color(0,0,150);
        G.setColor(mycolor);
        G.fillOval(-Magnifier.delta/4,-Magnifier.delta/4,Magnifier.delta/2,Magnifier.delta/2);
        G.setColor(Color.blue);
        if(Magnifier.delta!=10) G.drawString("(0,0)",-(Magnifier.delta/2),Magnifier.delta/2);
    }
        
    public void paint(Graphics G) {
        Graphics2D G_D = (Graphics2D) G;
    
        makeGrid(G_D);
    
        Color mycolor = new Color(0,0,150);
        G.setColor(mycolor);
        G.drawLine(-MaxX/2,0,MaxX/2,0);
        G.drawLine(0,MaxY/2,0,-MaxY/2);
        G.drawLine(-MaxX/2,1,MaxX/2,1);
        G.drawLine(-1,MaxY/2,-1,-MaxY/2);
    
        PlotPoint k1 = new PlotPoint();
        Color mycolor1 = new Color(100,100,0);
        k1.plot(G_D,9,7,mycolor1);                          

        DDA a = new DDA();
        Color mycolor2 = new Color(145,83,207);
        a.makeLine(G_D,8,-2,21,3,mycolor2);

        MidPointLDA b = new MidPointLDA();
        b.makeLine(G_D,-4,3,-8,-11,Color.red);

        BresenhamLDA c = new BresenhamLDA();
        Color mycolor3 = new Color(255,201,14);
        c.makeLine(G_D,-17,1,2,-3,mycolor3);

        if(VaryPoint.sigma <= 0.2) showStatus("Can't make it any smaller.");
    }

    public void actionPerformed(ActionEvent e) {
        if(e.getSource() == B1) {
            VaryPoint.sigma += 0.2;
		}

		if(e.getSource() == B2) {
            VaryPoint.sigma -= 0.2;
        }
        
		repaint();
    }
        
    public void mouseWheelMoved(MouseWheelEvent e) {
        int notches = e.getWheelRotation();
    
        if(notches<0) {
            Magnifier.delta += 5;
            Magnifier.delta = Magnifier.delta > 80 ? 80 : Magnifier.delta;
        }
        else {
            Magnifier.delta -= 5;
            Magnifier.delta = Magnifier.delta < -10 ? -10 : Magnifier.delta;
        }
            
        repaint();
    }
    
    public void mouseEntered(MouseEvent m) {
        showStatus("This is an Intellectual Property of Kuldip Kundu. Mouse is in Applet window. Scroll up to Zoom-in and scroll down to Zoom-out.");
    }
    
    public void mouseExited(MouseEvent m) {
        showStatus("This is an Intellectual Property of Kuldip Kundu. Mouse exited Applet window.");
    }
    
    public void mousePressed(MouseEvent m) {
        return;
    }
    
    public void mouseMoved(MouseEvent m) {
        return;
    }
    
    public void mouseDragged(MouseEvent m) {
        return;
    }
    
    public void mouseReleased(MouseEvent m) {
        return;
    }
    
    public void mouseClicked(MouseEvent m) {
        return;
    }
}