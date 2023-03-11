import javax.swing.*;
import java.awt.*;

public class plot extends Canvas {
	private int ox,oy,block,x,y;
	Graphics g1;
	Color C1;
	public void plot(int ox1,int oy1,int block1,int x1,int y1,Graphics g,Color C){
		g1=g;
		ox=ox1;
		oy=oy1;
		block=block1;
		x=x1;
		y=y1;
		C1=C;
		g.setColor(C1);

		g1.fillRect(ox+x*block-block/2,oy+y*block-block/2,block,block);
	}
}