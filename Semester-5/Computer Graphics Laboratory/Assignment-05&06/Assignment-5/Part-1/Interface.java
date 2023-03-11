package PACK1;

import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import PACK1.LINE_ALGORITHMS.*;
import PACK1.UTILITIES.*;
import PACK1.CLIPPING_ALGORITHMS.*;

public class Interface extends Applet implements ActionListener, MouseListener, MouseMotionListener, MouseWheelListener {
    int MaxX;
    int MaxY;

	TextField T1 = new TextField(2);
    TextField T2 = new TextField(2);
	TextField T3 = new TextField(2);
	TextField T4 = new TextField(2);
    TextField T5 = new TextField(2);
    TextField T6 = new TextField(2);
    TextField T7 = new TextField(2);
    TextField T8 = new TextField(2);
    Label L1 = new Label("Maximum Y Co-ord. of Window :");
    Label L2 = new Label("Minimum X Co-ord. of Window :");
    Label L3 = new Label("Maximum X Co-ord. of Window :");
    Label L4 = new Label("Minimum Y Co-ord. of Window :");
    Label L5 = new Label("Starting Co-ord. :");
	Label L6 = new Label("End Co-ord. :");
    Label L7 = new Label("Change size of Point :");
	Button B1 = new Button("Clip and draw");
	Button B2 = new Button("+");
    Button B3 = new Button("-");
    
    public void init() {
        MaxY = getHeight();
        MaxX = getWidth();

        Color mycolor = new Color(128,128,128);
        setBackground(mycolor);
        //setLayout(null);

        //L1.setBounds(30,438,20,5);
        add(L1);
        //T1.setBounds(55,438,5,5);
        T1.setText("0");
        add(T1);

        //L2.setBounds(10,448,20,5);
        add(L2);
        //T2.setBounds(35,448,5,5);
        T2.setText("0");
        add(T2);
        //L3.setBounds(50,448,20,5);
        add(L3);
        //T3.setBounds(75,448,5,5);
        T3.setText("0");
        add(T3);

        //L4.setBounds(30,458,20,5);
        add(L4);
        //T4.setBounds(55,458,5,5);
        T4.setText("0");
        add(T4);

        add(L5);
        T5.setText("0");
        add(T5);
        T6.setText("0");
		add(T6);
        
        add(L6);
        T7.setText("0");
        add(T7);
        T8.setText("0");
		add(T8);
        
		add(B1);

        add(L7);
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
        BresenhamLDA a = new BresenhamLDA();
        a.makeLine(G,ESS_VAR.Wx_Min,ESS_VAR.Wy_Min,ESS_VAR.Wx_Min,ESS_VAR.Wy_Max,Color.green);
        a.makeLine(G,ESS_VAR.Wx_Max,ESS_VAR.Wy_Min,ESS_VAR.Wx_Max,ESS_VAR.Wy_Max,Color.green);
        
        DDA b = new DDA();
        b.makeLine(G,ESS_VAR.Wx_Min,ESS_VAR.Wy_Max,ESS_VAR.Wx_Max,ESS_VAR.Wy_Max,Color.green);
        b.makeLine(G,ESS_VAR.Wx_Min,ESS_VAR.Wy_Min,ESS_VAR.Wx_Max,ESS_VAR.Wy_Min,Color.green);
        
        SutherlandCohen_Method c = new SutherlandCohen_Method();
        c.clipLine(ESS_VAR.X1,ESS_VAR.Y1,ESS_VAR.X2,ESS_VAR.Y2,G);

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

        ESS_VAR.X1 = Integer.parseInt(T5.getText());
        ESS_VAR.Y1 = Integer.parseInt(T6.getText());
		ESS_VAR.X2 = Integer.parseInt(T7.getText());
		ESS_VAR.Y2 = Integer.parseInt(T8.getText());

		if(e.getSource() == B1) {}

        if(e.getSource() == B2) {
            VaryPoint.sigma += 0.2;
		}

		if(e.getSource() == B3) {
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