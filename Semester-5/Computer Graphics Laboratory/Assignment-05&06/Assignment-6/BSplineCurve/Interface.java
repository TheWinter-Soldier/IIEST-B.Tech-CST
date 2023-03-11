package PACK1;

import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import PACK1.UTILITIES.*;
import PACK1.CURVE_ALGORITHMS.*;

public class Interface extends Applet implements ActionListener, MouseListener, MouseMotionListener, MouseWheelListener {
    String[] Coord;
    
    int MaxX;
    int MaxY;

    TextField T1 = new TextField(2);
    TextField T2 = new TextField(2);
    TextField T3 = new TextField(45);
    TextField T4 = new TextField(2);
    Label L1 = new Label("Number of control-points :");
    Label L2 = new Label("Order of the curve :");
    Label L3 = new Label("Give the control-points like 'x1,y1,x2,y2,...,xn,yn' :");
    Label L4 = new Label("Precision :");
    Label L5 = new Label("Change size of Point :");
    Button B1 = new Button("Generate curve");
	Button B2 = new Button("+");
    Button B3 = new Button("-");
    
    public void init() {
        MaxY= getHeight();
        MaxX= getWidth();

        Color mycolor = new Color(128,128,128);
        setBackground(mycolor);
        
        add(L1);
        T1.setText("13");
        add(T1);

        add(L2);
        T2.setText("10");
        add(T2);

        add(L3);
        T3.setText("0,4,3,8,9,8,11,2,5,-5,3,-9,0,-11,-3,-9,-5,-5,-11,2,-9,8,-3,8,0,4");
        add(T3);

        add(L4);
        T4.setText("0.025");
        add(T4);

        add(B1);

        add(L5);
        add(B2);
        add(B3);
    
		B1.addActionListener(this);
		B2.addActionListener(this);
		B3.addActionListener(this);

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

        Color mycolor1 = new Color(0,0,150);
        G.setColor(mycolor1);
        G.drawLine(-MaxX/2,0,MaxX/2,0);
        G.drawLine(0,MaxY/2,0,-MaxY/2);
        G.drawLine(-MaxX/2,1,MaxX/2,1);
        G.drawLine(-1,MaxY/2,-1,-MaxY/2);

        //Write shit here
        PlotPoint a = new PlotPoint();
        for(int i=0;i < (BSplineCurve.n + 1);i++) {
            a.plot(G,BSplineCurve.cX[i],BSplineCurve.cY[i],Color.YELLOW);
        }

        BSplineCurve b = new BSplineCurve();
        b.drawCurve(G);
        
        if(VaryPoint.sigma <= 0.2) showStatus("Can't make it any smaller.");
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

	public void actionPerformed(ActionEvent e) {
        BSplineCurve.n = (Integer.parseInt(T1.getText()) - 1);
        BSplineCurve.K = Integer.parseInt(T2.getText());
        BSplineCurve.Precision = Double.parseDouble(T4.getText());

        String str = T3.getText();
        Coord = str.split(",");
        for(int i=0;i < (BSplineCurve.n + 1);i++) {
            BSplineCurve.cX[i] = Integer.valueOf(Coord[2*i]);
            BSplineCurve.cY[i] = Integer.valueOf(Coord[(2*i)+1]);
        }

		if(e.getSource() == B1) {
            if(Coord.length != 2*(BSplineCurve.n + 1)) {
                T3.setText("Please check your imput format.");
                return;
            }
        }

        if(e.getSource()==B2) {
            VaryPoint.sigma += 0.2;
		}

		if(e.getSource()==B3) {
            VaryPoint.sigma -= 0.2;
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