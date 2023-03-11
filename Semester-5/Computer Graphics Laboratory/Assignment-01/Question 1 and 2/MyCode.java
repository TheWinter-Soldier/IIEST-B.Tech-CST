import java.applet.*;
import java.awt.*;
import java.awt.event.*;

public class MyCode extends Applet implements ActionListener, MouseListener, MouseMotionListener, MouseWheelListener {
    int MaxX = 0;    
    int MaxY = 0;
    int GridZoomer = 32;
    int PointZoomer = 8;

	int x = 0;         //X Co-ord. of point
	int y = 0;         //Y Co-ord. of point

	Color mycolor2;
	int r1, r2, g1, g2, b1, b2;
    
    Label L1 = new Label("BACKGROUND COLOR :");
    TextField T1 = new TextField(2);
	TextField T2 = new TextField(2);
	TextField T3 = new TextField(2);
	Button B1 = new Button("OK");
    
    Label L2 = new Label("GRID COLOR :");
    TextField T4 = new TextField(2);
    TextField T5 = new TextField(2);
    TextField T6 = new TextField(2);
	Button B2 = new Button("OK");
    
    Label L3 = new Label("X Co-ord. :");
    TextField T7 = new TextField(2);
    Label L4 = new Label("Y Co ord. :");
    TextField T8 = new TextField(2);
	Button B3 = new Button("OK");
	
	Label L5 = new Label("Change size of Point :");
	Button B4 = new Button("+");
    Button B5 = new Button("-");

    public void init() {
        MaxY = getHeight();
        MaxX = getWidth();

		add(L1);
        T1.setText("0");
		add(T1);
        T2.setText("0");
		add(T2);
        T3.setText("0");
		add(T3);
		add(B1);

		add(L2);
        T4.setText("0");
        add(T4);
        T5.setText("0");
        add(T5);
        T6.setText("0");
        add(T6);
		add(B2);

		add(L3);
        T7.setText("0");
        add(T7);
        add(L4);
        T8.setText("0");
        add(T8);
		add(B3);
                
        add(L5);
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

        G.setColor(mycolor2);

        int yCoord=0;
        for(int i=0;i < MaxX/2;i += GridZoomer) {
            G.drawLine(i,MaxY/2,i,-MaxY/2);
            if(GridZoomer>20 && i != 0) {
                G.drawString(String.valueOf(yCoord),5,i+14);
            } 
            yCoord--;
        }
        yCoord=0;
        for(int i=0;i > -MaxX/2;i -= GridZoomer) {
            G.drawLine(i,MaxY/2,i,-MaxY/2);
            if(GridZoomer>20 && i != 0) {
                G.drawString(String.valueOf(yCoord),5,i+14);
            }
            yCoord++;
        }

        int xCoord=0;
        for(int i=0;i < MaxY/2;i += GridZoomer) {
            G.drawLine(-MaxX/2,i,MaxX/2,i);
            if(GridZoomer>20 && i != 0) {
                G.drawString(String.valueOf(xCoord),i-10,15);
            }
            xCoord++;
        }
        xCoord=0;
        for(int i=0;i > -MaxY/2;i -= GridZoomer) {
            G.drawLine(-MaxX/2,i,MaxX/2,i);
            if(GridZoomer>20 && i != 0) {
                G.drawString(String.valueOf(xCoord),i-15,15);
            }
            xCoord--;
        }

        G.setColor(Color.black);
        G.fillOval(-GridZoomer/4,-GridZoomer/4,GridZoomer/2,GridZoomer/2);
        G.setColor(Color.blue);
        if(GridZoomer!=10) G.drawString("(0,0)",-(GridZoomer/2),GridZoomer/2);
    }
    
    public void paint(Graphics G) {
        Graphics2D G_D = (Graphics2D) G;

        makeGrid(G_D);

        G.setColor(Color.black);
        G.drawLine(-MaxX/2,0,MaxX/2,0);
        G.drawLine(0,MaxY/2,0,-MaxY/2);
        G.drawLine(-MaxX/2,1,MaxX/2,1);
        G.drawLine(-1,MaxY/2,-1,-MaxY/2);

        G_D.scale(PointZoomer,-PointZoomer);

		G.setColor(Color.red);
		if((GridZoomer/PointZoomer) >= 1) {
			G.drawLine(x*(GridZoomer/PointZoomer),y*(GridZoomer/PointZoomer),x*(GridZoomer/PointZoomer),y*(GridZoomer/PointZoomer));
		}
		else {
			showStatus("Can't get any larger!");
		}
    }

	public void actionPerformed(ActionEvent e) {
        r1 = Integer.parseInt(T1.getText());
        g1 = Integer.parseInt(T2.getText());
        b1 = Integer.parseInt(T3.getText());

        r2 = Integer.parseInt(T4.getText());
        g2 = Integer.parseInt(T5.getText());
        b2 = Integer.parseInt(T6.getText());

        x = Integer.parseInt(T7.getText());
        y = Integer.parseInt(T8.getText());

        if(e.getSource()==B1) {
            Color mycolor1 = new Color(r1,g1,b1);      //Background Color
            setBackground(mycolor1);
		}
		repaint();

		if(e.getSource()==B2) {
            mycolor2 = new Color(r2,g2,b2);            //Grid Color
        }
		repaint();

        if(e.getSource()==B4) {
            PointZoomer *= 2;         //Increase Point-size
        }
		else if(e.getSource()==B5) {
            PointZoomer /= 2;         //Decrease Point-size
        }
		repaint();
    }

    public void mouseWheelMoved(MouseWheelEvent e) {
        int notches = e.getWheelRotation();

        if(notches<0) {
            GridZoomer *= 2;
            GridZoomer = GridZoomer > 128 ? 128 : GridZoomer;
        }
        else {
            GridZoomer /= 2;
            GridZoomer = GridZoomer < 4 ? 4 : GridZoomer;
        }
        
        repaint();
    }

    public void mouseEntered(MouseEvent m) {
        showStatus("Mouse is in Applet window. Scroll up to Zoom-in and scroll down to Zoom-out.");
    }

    public void mouseExited(MouseEvent m) {
        showStatus("Mouse exited Applet window.");
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