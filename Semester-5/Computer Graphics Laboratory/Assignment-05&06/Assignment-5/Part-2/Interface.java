package PACK1;

import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import PACK1.LINE_ALGORITHMS.*;
import PACK1.UTILITIES.*;
import PACK1.CLIPPING_ALGORITHMS.*;

public class Interface extends Applet implements ActionListener, MouseListener, MouseMotionListener, MouseWheelListener {
    boolean view;

    String[] Coord;
    
    int MaxX;
    int MaxY;

	TextField T1 = new TextField(2);
    TextField T2 = new TextField(2);
	TextField T3 = new TextField(2);
	TextField T4 = new TextField(2);
    TextField T5 = new TextField(2);
    TextField T6 = new TextField(35);
    Label L1 = new Label("Maximum Y Co-ord. of Window :");
    Label L2 = new Label("Minimum X Co-ord. of Window :");
    Label L3 = new Label("Maximum X Co-ord. of Window :");
    Label L4 = new Label("Minimum Y Co-ord. of Window :");
    Label L5 = new Label("Number of sides of the polygon :");
    Label L6 = new Label("Give the vertices of polygon like 'x1,y1,x2,y2,...,xn,yn' :");
    Label L7 = new Label("Change size of Point :");
    Button B1 = new Button("View original");
	Button B2 = new Button("Clip and draw");
	Button B3 = new Button("+");
    Button B4 = new Button("-");
    
    public void init() {
        MaxY= getHeight();
        MaxX= getWidth();

        Color mycolor = new Color(128,128,128);
        setBackground(mycolor);
        
        add(L1);
        T1.setText("5");
        add(T1);
        add(L2);
        T2.setText("-3");
        add(T2);
        add(L3);
        T3.setText("4");
        add(T3);
        add(L4);
        T4.setText("-7");
        add(T4);

        add(L5);
        T5.setText("3");
        add(T5);

        add(L7);
		add(B3);
		add(B4);
        
        add(L6);
        T6.setText("0,0,0,0,0,0");
		add(T6);
        
		add(B1);
        add(B2);
		
		B1.addActionListener(this);
		B2.addActionListener(this);
		B3.addActionListener(this);
        B4.addActionListener(this);

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
        if(view) {
            DDA a = new DDA();
            for(int i=0;i<ESS_VAR.n-1;i++) {
                a.makeLine(G,ESS_VAR.X[i],ESS_VAR.Y[i],ESS_VAR.X[i+1],ESS_VAR.Y[i+1],Color.orange);
            }
            a.makeLine(G,ESS_VAR.X[ESS_VAR.n-1],ESS_VAR.Y[ESS_VAR.n-1],ESS_VAR.X[0],ESS_VAR.Y[0],Color.orange);
        }
        else {
            BresenhamLDA b = new BresenhamLDA();
            b.makeLine(G,ESS_VAR.Wx_Min,ESS_VAR.Wy_Min,ESS_VAR.Wx_Min,ESS_VAR.Wy_Max,Color.green);
            b.makeLine(G,ESS_VAR.Wx_Max,ESS_VAR.Wy_Min,ESS_VAR.Wx_Max,ESS_VAR.Wy_Max,Color.green);
        
            DDA c = new DDA();
            c.makeLine(G,ESS_VAR.Wx_Min,ESS_VAR.Wy_Max,ESS_VAR.Wx_Max,ESS_VAR.Wy_Max,Color.green);
            c.makeLine(G,ESS_VAR.Wx_Min,ESS_VAR.Wy_Min,ESS_VAR.Wx_Max,ESS_VAR.Wy_Min,Color.green);
        
            SutherlandCohen_Method d = new SutherlandCohen_Method();
            for(ESS_VAR.j = 0;ESS_VAR.j < ESS_VAR.n - 1;ESS_VAR.j++) {
                // System.out.println(ESS_VAR.X[ESS_VAR.j]);
                // System.out.println(ESS_VAR.Y[ESS_VAR.j]);
                // System.out.println(ESS_VAR.X[(ESS_VAR.j + 1)]);
                // System.out.println(ESS_VAR.Y[(ESS_VAR.j + 1)]);
                d.clipLine(ESS_VAR.X[ESS_VAR.j],ESS_VAR.Y[ESS_VAR.j],ESS_VAR.X[(ESS_VAR.j + 1)],ESS_VAR.Y[(ESS_VAR.j + 1)],G);
            }
            d.clipLine(ESS_VAR.X[ESS_VAR.n-1],ESS_VAR.Y[ESS_VAR.n-1],ESS_VAR.X[0],ESS_VAR.Y[0],G);  
        }
        
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
        ESS_VAR.Wy_Max = Integer.parseInt(T1.getText());
        ESS_VAR.Wx_Min = Integer.parseInt(T2.getText());
		ESS_VAR.Wx_Max = Integer.parseInt(T3.getText());
		ESS_VAR.Wy_Min = Integer.parseInt(T4.getText());

        ESS_VAR.n = Integer.parseInt(T5.getText());

        String str = T6.getText();
        Coord = str.split(",");
        for(int i=0;i<ESS_VAR.n;i++) {
            ESS_VAR.X[i] = Integer.valueOf(Coord[2*i]);
            ESS_VAR.Y[i] = Integer.valueOf(Coord[(2*i)+1]);
        }

		if(e.getSource() == B1) {
            if(Coord.length != 2*ESS_VAR.n) {
                T6.setText("Please check your imput format.");
                return;
            }

            view = true; 
        }

        if(e.getSource() == B2) {
            if(Coord.length != 2*ESS_VAR.n) {
                T6.setText("Please check your imput format.");
                return;
            }

            view = false; 
        }

        if(e.getSource() == B3) {
            VaryPoint.sigma += 0.2;
		}

		if(e.getSource() == B4) {
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