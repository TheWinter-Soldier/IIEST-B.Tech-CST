package PACK1;

import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import PACK1.UTILITIES.*;
import INCENDIARY.*;

public class Interface extends Applet implements ActionListener, MouseListener, MouseMotionListener, MouseWheelListener {
    boolean candleExists = false;
    boolean candleGlowing = false;

    int MaxX;
    int MaxY;

	Button B1 = createButton("Make_candle",Color.GRAY);
    Button B2 = createButton("Destroy_candle",Color.GRAY);
	Button B3 = createButton("Light_candle",Color.yellow);
    Button B4 = createButton("Put-out_candle",Color.yellow);
	Button B5 = new Button("+");
    Button B6 = new Button("-");

    Label L1 = new Label("Change size of Point :");

    public void init() {
        MaxY = getHeight();
        MaxX = getWidth();

        Color mycolor = new Color(181,212,255);
        setBackground(mycolor);
        
		add(B1);
        add(B2);
		add(B3);
        add(B4);

        add(L1);
        B5.setBounds(1400,15,5,5);
		add(B5);
        B5.setBounds(1410,15,5,5);
		add(B6);
		
		B1.addActionListener(this);
		B2.addActionListener(this);
		B3.addActionListener(this);
        B4.addActionListener(this);
		B5.addActionListener(this);
        B6.addActionListener(this);

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

    private Button createButton(String label,Color c) {
        Button button = new Button(label);
        button.setCursor(new Cursor(Cursor.HAND_CURSOR));
        button.setBackground(c);
        button.setFont(Font.decode(Font.SANS_SERIF));
        return button;
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

        if(VaryPoint.sigma <= 0.2) showStatus("Can't make it any smaller.");

        Candle obj1 = new Candle();
        if(candleExists) {
            obj1.makeCandle(G,-12,-40,7,40);
        }

        Flame obj2 = new Flame();
        if(candleExists && candleGlowing) {
            try {
                obj2.lightCandle(G,-9,2);
                Thread.sleep(300);
            }
            catch(InterruptedException ie) {
				ie.printStackTrace();
	        } 
	        repaint();
        }
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
		if(e.getSource() == B1) {
            this.candleExists = true;
        }

		if(e.getSource() == B2) {
            this.candleExists = false;
        }

		if(e.getSource() == B3) {
            this.candleGlowing = true;
        }

        if(e.getSource() == B4) {
            this.candleGlowing = false;
        }

        if(e.getSource() == B5) {
            VaryPoint.sigma += 0.2;
		}

		if(e.getSource() == B6) {
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