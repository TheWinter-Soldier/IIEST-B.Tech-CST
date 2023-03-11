package PACK1;

import java.applet.*;
import java.awt.*;
import PACK1.PACK2.Cart;

public class Test extends Applet {
	public void init() {
		setBackground(Color.white);
        }
	
	public void paint(Graphics g) {
                g.setColor(Color.red);
                g.fillOval(100,250,130,180);

                Cart n = new Cart(10,10,50,50,g);
                n.setVisible();
	}
}