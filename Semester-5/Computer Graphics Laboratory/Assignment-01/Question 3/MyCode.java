import java.applet.*;
import java.awt.*;
import java.awt.event.*;

public class MyCode extends Applet implements MouseListener, MouseMotionListener {
        int s = 20;     //zooming scale
	int x;          //width of applet
	int y;          //height of applet

        public void init() {
                y = getHeight();
                x = getWidth();

                Color mycolor = new Color(255,210,207);   
                setBackground(mycolor);

		addMouseListener(this);
                addMouseMotionListener(this);
        }

        public void paint(Graphics g) {
                Color mycolor = new Color(0,0,255);
                g.setColor(mycolor);
                Graphics2D g_D = (Graphics2D) g;
                
                g_D.translate(x/2,y/2);                              //Moving the origin to centre of Applet screen

                for(int i=0;i<x/2;i+=s) {
                        g_D.drawLine(i,y/2,i,-y/2);
                }
		for(int i=0;i>-x/2;i-=s) {
                        g_D.drawLine(i,y/2,i,-y/2);
                }
                for(int i=0;i<y/2;i+=s) {
                        g_D.drawLine(-x/2,i,x/2,i);  
                }
		for(int i=0;i>-y/2;i-=s) {
                        g_D.drawLine(-x/2,i,x/2,i);  
                }                                                    //Drwaing of grid

                g.setColor(Color.black);
                g_D.drawLine(-x/2,0,x/2,0);
                g_D.drawLine(0,y/2,0,-y/2);

                g_D.scale(s,-s);

                mycolor = new Color(100,100,0);

		PlotPoint k1 = new PlotPoint();
                k1.plot(g_D,20,12,mycolor);                                  

                PlotPoint k2 = new PlotPoint();
                for(int i=6;i<=21;i++) {
                        k2.plot(g_D,i,-5,mycolor);
                        k2.plot(g_D,i,-20,mycolor);
                }
                for(int i=-19;i<-5;i++) {
                        k2.plot(g_D,6,i,mycolor);
                        k2.plot(g_D,21,i,mycolor);
                }                                                                   //Drawing a square using only plotpoint method

                PlotPoint k3 = new PlotPoint();
                for(int i = -12;i <= 7;i++) k3.plot(g_D,i,((i*i)+(6*i)),mycolor);   //Drawing some portion of the graph of a function using only plotpoint method
        }

        public void mouseEntered(MouseEvent m) {
                showStatus("Left click to zoom in. Right click to zoom out.");
	}

        public void mouseExited(MouseEvent m) {
                showStatus("Mouse Exited Applet Area.");
        }

	public void mousePressed(MouseEvent m) {
                switch(m.getModifiers()) {
                        case InputEvent.BUTTON1_MASK: {
                                s+=5;       //Zooming in for left-click
                                break;
                        }
                        case InputEvent.BUTTON3_MASK: {
                                s-=5;       //Zooming out for right-click
                                break;
                        }
                }

                repaint();
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