import java.applet.*;
import java.awt.*;

public class Test extends Applet {
	public void init() {
		setBackground(Color.green);
    }
	
	public void paint(Graphics g) {
        g.setColor(Color.red);
        g.fillOval(100,250,130,180);
	}
}