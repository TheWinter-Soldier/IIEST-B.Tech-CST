package PACK1;

import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import PACK1.LINE_ALGORITHMS.*;
import PACK1.UTILITIES.*;

public class UserInput extends Applet implements ActionListener, MouseListener, MouseMotionListener, MouseWheelListener {
    int userInput = 0;

    int MaxX;
    int MaxY;

	int X0 = 0;   //starting X Co-ord. of line
	int Y0 = 0;   //starting Y Co-ord. of line
	int X1 = 0;   //Terminating X Co-ord. of line
	int Y1 = 0;   //Terminating Y Co-ord. of line

	TextField T1 = new TextField(2);
    TextField T2 = new TextField(2);
	TextField T3 = new TextField(2);
	TextField T4 = new TextField(2);
    Label L1 = new Label("Starting Co-ord. :");
	Label L2 = new Label("End Co-ord. :");
    Label L3 = new Label("Change size of Point :");
	Button B1 = new Button("DDA");
    Button B2 = new Button("Mid-PointLDA");
	Button B3 = new Button("Bresenham'sLDA");
	Button B4 = new Button("+");
    Button B5 = new Button("-");

    public void init() {
        MaxY = getHeight();
        MaxX = getWidth();

        Color mycolor = new Color(128,255,128);
        setBackground(mycolor);

        add(L1);
        T1.setText("0");
        add(T1);
        T2.setText("0");
		add(T2);
        
        add(L2);
        T3.setText("0");
        add(T3);
        T4.setText("0");
		add(T4);
        
		add(B1);
        add(B2);
		add(B3);

        add(L3);
		add(B4);
		add(B5);
		
		B1.addActionListener(this);
		B2.addActionListener(this);
		B3.addActionListener(this);
        B4.addActionListener(this);
		B5.addActionListener(this);

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

        DDA a = new DDA();
        Color mycolor2 = new Color(145,83,207);

        MidPointLDA b = new MidPointLDA();
        
        BresenhamLDA c = new BresenhamLDA();
        Color mycolor3 = new Color(255,201,14);
        
		switch(userInput) {
            case 1:
            a.makeLine(G_D,X0,Y0,X1,Y1,mycolor2);
			break;

			case 2:
            b.makeLine(G_D,X0,Y0,X1,Y1,Color.red);
			break;

			case 3:
            c.makeLine(G_D,X0,Y0,X1,Y1,mycolor3);
			break;
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
        X0 = Integer.parseInt(T1.getText());
        Y0 = Integer.parseInt(T2.getText());
		X1 = Integer.parseInt(T3.getText());
		Y1 = Integer.parseInt(T4.getText());

		if(e.getSource() == B1) {
            userInput = 1;
        }

		if(e.getSource() == B2) {
            userInput = 2;
        }

		if(e.getSource() == B3) {
            userInput = 3;
        }

        if(e.getSource() == B4) {
            VaryPoint.sigma += 0.2;
		}

		if(e.getSource()==B5) {
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