import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.lang.Math;

public class Shapes extends Canvas {
	int x,y,x0,y0,x1,y1,a=1;
	static int originX,originY,offX=0,offY=0,grid=500,block=10,parent1[]={0,0,0,0,0,0,0,2,0},parent2[]={1,1,1,1,1,1,1,1,1},child[]={0,0,0,0,0,0,0,0,0},var[]={0,0,0,0,0,0,0,0,0};
	
	public static void childset(int arr[],int arr2[]) {
		for(int i=0;i<9;i++) {
            var[i] = ((int)(Math.random()*100+i))%2;
		}
		for(int i=0;i<9;i++) {
            child[i] = var[i]*arr[i] + (1-var[i])*arr2[i];
		}	
	}

	public void plotpoint(Graphics g,int x,int y) {
		plot a = new plot();
		Color mycolor;
		mycolor = new Color(0,0,0);
		a.plot(originX,originY,block,x,y*-1,g,mycolor);
	}

	public void plotellipse(Graphics g,int rx, int ry,int xc ,int yc,int angle) {
		double dx, dy, d1, d2, x, y;
		double rot = 3.14*(angle%360)/180;
		x = 0;
		y = ry;
		// Initial decision parameter of region 1
		d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);

		dx = 2 * ry * ry * x;
		dy = 2 * rx * rx * y;
		// For region 1
		while(dx<dy) {
            // Print points based on 4-way symmetry
			plotpoint(g,(int)((x*Math.cos(rot)-y*Math.sin(-rot))+xc),(int)((x*Math.sin(-rot)+y*Math.cos(rot))+yc));
			plotpoint(g,(int)(-(x*Math.cos(rot)-y*Math.sin(rot))+xc),(int)((x*Math.sin(rot)+y*Math.cos(rot))+yc));
			plotpoint(g,(int)((x*Math.cos(rot)-y*Math.sin(rot))+xc),(int)(-(x*Math.sin(rot)+y*Math.cos(rot))+yc));
			plotpoint(g,(int)(-(x*Math.cos(rot)-y*Math.sin(-rot))+xc),(int)(-(x*Math.sin(-rot)+y*Math.cos(rot))+yc));
 
			// Checking and updating value of
			// decision parameter based on algorithm
			if(d1 < 0) {
                x++;
				dx = dx + (2 * ry * ry);
				d1 = d1 + dx + (ry * ry);
			}
			else {
				x++;
				y--;
				dx = dx + (2 * ry * ry);
				dy = dy - (2 * rx * rx);
				d1 = d1 + dx - dy + (ry * ry);
			}
		}
 
		// Decision parameter of region 2
		d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) + ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);
		// Plotting points of region 2
		while(y>=0) {
 
			// printing points based on 4-way symmetry
			plotpoint(g,(int)((x*Math.cos(-rot)-y*Math.sin(-rot))+xc),(int)((x*Math.sin(-rot)+y*Math.cos(-rot))+yc));
			plotpoint(g,(int)(-(x*Math.cos(rot)-y*Math.sin(rot))+xc),(int)((x*Math.sin(rot)+y*Math.cos(rot))+yc));
			plotpoint(g,(int)((x*Math.cos(rot)-y*Math.sin(rot))+xc),(int)(-(x*Math.sin(rot)+y*Math.cos(rot))+yc));
			plotpoint(g,(int)(-(x*Math.cos(-rot)-y*Math.sin(-rot))+xc),(int)(-(x*Math.sin(-rot)+y*Math.cos(-rot))+yc));

			// Checking and updating parameter
			// value based on algorithm
			if(d2>0) {
                y--;
                dy = dy - (2 * rx * rx);
				d2 = d2 + (rx * rx) - dy;
			}
			else {
				y--;
				x++;
				dx = dx + (2 * ry * ry);
				dy = dy - (2 * rx * rx);
				d2 = d2 + dx - dy + (rx * rx);
			}
		}
	}

	public void plothair(Graphics g,int rx, int ry,int xc ,int yc,int angle) {
		double dx, dy, d1, d2, x, y;
		int p1,p2,p3,p4,p5,p6,p7,p8;
		double rot = 3.14*(angle%360)/180;
		x = 0;
		y = ry;
		// Initial decision parameter of region 1
		d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);

		dx = 2 * ry * ry * x;
		dy = 2 * rx * rx * y;
		// For region 1
		while(dx<dy) {
			// Print points based on 4-way symmetry
			p1=(int)((x*Math.cos(-rot)-y*Math.sin(-rot))+xc);
			p2=(int)((x*Math.sin(-rot)+y*Math.cos(-rot))+yc);
			p3=(int)(-(x*Math.cos(rot)-y*Math.sin(rot))+xc);
			p4=(int)((x*Math.sin(rot)+y*Math.cos(rot))+yc);
			p5=(int)((x*Math.cos(rot)-y*Math.sin(rot))+xc);
			p6=(int)(-(x*Math.sin(rot)+y*Math.cos(rot))+yc);
			p7=(int)(-(x*Math.cos(-rot)-y*Math.sin(-rot))+xc);
			p8=(int)(-(x*Math.sin(-rot)+y*Math.cos(-rot))+yc);
 
			plotline(p1,p2,(int)(Math.random()*5)+p1-2,(int)(Math.random()*5)+p2-2,g);
			plotline(p3,p4,(int)(Math.random()*5)+p3-2,(int)(Math.random()*5)+p4-2,g);
			plotline(p5,p6,(int)(Math.random()*5)+p5-2,(int)(Math.random()*5)+p6-2,g);
			plotline(p7,p8,(int)(Math.random()*5)+p7-2,(int)(Math.random()*5)+p8-2,g);
			
			// Checking and updating value of
			// decision parameter based on algorithm
			if(d1<0) {
				x++;
				dx = dx + (2 * ry * ry);
				d1 = d1 + dx + (ry * ry);
			}
			else {
				x++;
				y--;
				dx = dx + (2 * ry * ry);
				dy = dy - (2 * rx * rx);
				d1 = d1 + dx - dy + (ry * ry);
			}
		}
 
		// Decision parameter of region 2
		d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) + ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);
		// Plotting points of region 2
		while(y>=0) {
			// printing points based on 4-way symmetry
			p1=(int)((x*Math.cos(-rot)-y*Math.sin(-rot))+xc);
			p2=(int)((x*Math.sin(-rot)+y*Math.cos(-rot))+yc);
			p3=(int)(-(x*Math.cos(rot)-y*Math.sin(rot))+xc);
			p4=(int)((x*Math.sin(rot)+y*Math.cos(rot))+yc);
			p5=(int)((x*Math.cos(rot)-y*Math.sin(rot))+xc);
			p6=(int)(-(x*Math.sin(rot)+y*Math.cos(rot))+yc);
			p7=(int)(-(x*Math.cos(-rot)-y*Math.sin(-rot))+xc);
			p8=(int)(-(x*Math.sin(-rot)+y*Math.cos(-rot))+yc);
 
			plotline(p1,p2,(int)(Math.random()*5)+p1-2,(int)(Math.random()*5)+p2-2,g);
			plotline(p3,p4,(int)(Math.random()*5)+p3-2,(int)(Math.random()*5)+p4-2,g);
			plotline(p5,p6,(int)(Math.random()*5)+p5-2,(int)(Math.random()*5)+p6-2,g);
			plotline(p7,p8,(int)(Math.random()*5)+p7-2,(int)(Math.random()*5)+p8-2,g);
			// Checking and updating parameter
			// value based on algorithm
			if(d2>0) {
				y--;
				dy = dy - (2 * rx * rx);
				d2 = d2 + (rx * rx) - dy;
			}
			else {
				y--;
				x++;
				dx = dx + (2 * ry * ry);
				dy = dy - (2 * rx * rx);
				d2 = d2 + dx - dy + (rx * rx);
			}
	    }
	}

	public void plotcircle(int r,int x,int y,Graphics g) {
		double p0,pk;
		int xk,yk;
		xk=0;
		yk=r;
		p0=(5/4) - r;
		pk = p0;

		while(xk<=yk) {
            plotpoint(g,x+xk,-y+yk);
			plotpoint(g,x+xk,-y-yk);
			plotpoint(g,x-xk,-y+yk);
			plotpoint(g,x-xk,-y-yk);
			plotpoint(g,x+yk,-y+xk);
			plotpoint(g,x+yk,-y-xk);
			plotpoint(g,x-yk,-y+xk);
			plotpoint(g,x-yk,-y-xk);

			if(pk<0) {
				pk = pk + 2*xk + 1;
			}
			else {
				pk = pk + 2*xk + 1 - 2*yk;
				yk = yk - 1;
			}
			xk = xk + 1;	
		}
	}

	public void plotline(int x0,int y0,int x1,int y1,Graphics g) {
		int dy,dx,px,py,steps;
			double yt,xt,yk,xk;
			dy=y1-y0;dx=x1-x0;

			if(Math.abs(dy)>Math.abs(dx)){
				steps = Math.abs(dy);
			}
			else {
				steps = Math.abs(dx);
			}

			yk=(double)dy/steps;
			xk=(double)dx/steps;

			yt=y0;xt=x0;
			for(int temp = 0;temp <= steps;temp++) {	
				py=(int)Math.round(yt);
				px=(int)Math.round(xt);
				yt+=yk;
				xt+=xk;
				plotpoint(g,px,py);
			}
		}

	void plottri(Graphics g,int base,int height,int xc,int yc,int angle) {
		double rot = 3.14*(angle%360)/180;
		int xt1 = - base/2;
		int xt2 = base/2;
		int yt1 = - height/2;
		int yt2 =  height/2;

		plotline((int)((xt1*Math.cos(rot)- yt1*Math.sin(rot))+xc),(int)(( xt1*Math.sin(rot)+ yt1*Math.cos(rot))+yc),(int)((xt2*Math.cos(rot)- yt1*Math.sin(rot))+xc),(int)((xt2*Math.sin(rot)+ yt1*Math.cos(rot))+yc),g);
		plotline((int)(( xt1*Math.cos(rot)- yt1*Math.sin(rot))+xc),(int)(( xt1*Math.sin(rot)+ yt1*Math.cos(rot))+yc),(int)((- yt2*Math.sin(rot))+xc),(int)(( yt2*Math.cos(rot))+yc),g);
		plotline((int)(( xt2*Math.cos(rot)- yt1*Math.sin(rot))+xc),(int)(( xt2*Math.sin(rot)+ yt1*Math.cos(rot))+yc),(int)((- yt2*Math.sin(rot))+xc),(int)(( yt2*Math.cos(rot))+yc),g);
	}

	void plottri2(Graphics g,int base,int height,int xc,int yc,int angle) {
		double rot = 3.14*(angle%360)/180;
		int xt1 = 0;
		int xt2 = base/2;
		int yt1 = - height/2;
		int yt2 = height/2;

		plotline((int)((xt1*Math.cos(rot)- yt1*Math.sin(rot))+xc),(int)(( xt1*Math.sin(rot)+ yt1*Math.cos(rot))+yc),(int)((xt2*Math.cos(rot)- yt1*Math.sin(rot))+xc),(int)((xt2*Math.sin(rot)+ yt1*Math.cos(rot))+yc),g);
		plotline((int)(( xt1*Math.cos(rot)- yt1*Math.sin(rot))+xc),(int)(( xt1*Math.sin(rot)+ yt1*Math.cos(rot))+yc),(int)((- yt2*Math.sin(rot))+xc),(int)(( yt2*Math.cos(rot))+yc),g);
		plotline((int)(( xt2*Math.cos(rot)- yt1*Math.sin(rot))+xc),(int)(( xt2*Math.sin(rot)+ yt1*Math.cos(rot))+yc),(int)((- yt2*Math.sin(rot))+xc),(int)(( yt2*Math.cos(rot))+yc),g);
	}

	/*void spots(int rx,int ry,int xc,int yc,int angle,Graphics g) {
		int xz,yz;
		double rot = 3.14*(angle%360)/180;

		for(int i =0;i<r1;i++) {
			for(int j = 0;j<r2;j++) {
				if(i%8==0 && j %8 == 0) {
					xz = ox+i-r1;
					yz = -(oy+j-r2);
					plotcircle(1,xz,yz,g);
				}
			}
		}
	}*/

	public void plotanimal(int xr,int feat[],Graphics g) {
		//Imaginary animal 1
		
		//ears
		if(feat[2] == 0) {
            plotcircle(5,10+xr,-60,g);
		    plotcircle(5,12+xr,-58,g);
		}
		if(feat[2] == 1) {
            plottri(g,10,-10,4+xr,60,50);
		    plottri(g,10,-10,10+xr,54,0);		
		}
		
		//head
		plotcircle(10,0+xr,-50,g);
		plotcircle(2,-3+xr,-50,g);
		
		//body
		plotellipse(g,12,25,20+xr,25,-30);
		if(feat[4]==1) {
			plothair(g,12,25,20+xr,25,-30);
		}
		//spots(20,25,12,25,-30,g);
		//Hardcoded spots
		if(feat[3]==1) {
			plotcircle(2,20+xr,-25,g);
			plotcircle(2,12+xr,-38,g);
			plotcircle(1,24+xr,-30,g);
			plotcircle(1,10+xr,-30 ,g);
			plotcircle(1,28+xr,-21,g);
			plotcircle(1,12+xr,-21,g);
			plotcircle(2,28+xr,-15,g);
			plotcircle(2,15+xr,-15,g);
		}
			
		//beaks
		if(feat[0]==0) {
			plottri2(g,-30,-4,-8+xr,46,0);
			plottri2(g,-30,4,-8+xr,54,0);
			//teeth
			if(feat[1]==1) {
				for(int i=4;i<13;i++) {
					if(i%2 == 0) {
						plotline(-8-i+xr,52,-8-i+xr,51,g);
					}
					else if(i%2 == 1) {
						plotline(-8-i+xr,48,-8-i+xr,49,g);
					}
				}
			}
		}
		else if(feat[0]==1) {
			plottri2(g,-16,-4,-8+xr,46,0);
			plottri2(g,-16,4,-8+xr,54,0);
			//teeth
			if(feat[1]==1) {
				for(int i=4;i<9;i++) {
					if(i%2 == 0) {
						plotline(-8-i+xr,52,-8-i+xr,51,g);
					}
					else if(i%2 == 1) {
						plotline(-8-i+xr,48,-8-i+xr,49,g);
					}
				}
			}
		}
		
		//hand 1
		if(feat[7]==0) {
			plotellipse(g,5,8,0+xr,20,-120);
			plotellipse(g,3,5,-12+xr,16,-90); 
			if(feat[5]==1) {
				plotcircle(2,-12+xr,-16,g);
			}
			plotcircle(4,-22+xr,-16,g);
			plotellipse(g,1,3,-21+xr,22,0);
			plotellipse(g,1,3,-26+xr,24,-30);
			plotellipse(g,1,3,-30+xr,21,-45);
			plotellipse(g,1,3,-28+xr,15,90);
			plotellipse(g,1,2,-25+xr,12,-135);
			//hand 2
			int r=10,z=0;
			plotellipse(g,4,6,-3+xr,32,-120);
			plotellipse(g,3,5,-14+xr,30,-60);
			if(feat[5]==1) {
				plotcircle(2,-14+xr,-30,g);
			}
			plotcircle(5,-31+r+xr,-36-z,g);
			plotellipse(g,1,3,-27+r+xr,42+z,0);
			plotellipse(g,1,3,-32+r+xr,44+z,-30);
			plotellipse(g,1,3,-37+r+xr,42+z,-45);
			plotellipse(g,1,3,-38+r+xr,36+z,90);
			plotellipse(g,1,2,-34+r+xr,31+z,-135);
		    plotellipse(g,6,20,33+xr,-14,-10);
		    plotellipse(g,4,15,33+xr,-45,15);
		    //feet
		    plotellipse(g,3,6,7+xr,-53,50);
		    plotellipse(g,1,2,0+xr,-55,50);
		    plotellipse(g,1,2,2+xr,-57,50);
		    plotellipse(g,1,2,3+xr,-58,50);
		    //leg 2
		    plotellipse(g,6,18,15+xr,-9,30);
		    plotellipse(g,4,17,9+xr,-36,-10);
		    //feet
		    plotellipse(g,3,6,26+xr,-61,70);
		    plotellipse(g,1,2,25+xr,-65,70);
		    plotellipse(g,1,2,20+xr,-63,70);
		    plotellipse(g,1,2,22+xr,-64,70);
		}
		else if(feat[7] == 1) {
            //hand 1
			plotellipse(g,5,12,0+xr,20,-120);
			plotellipse(g,3,8,-18+xr,16,-90);
			if(feat[5]==1) {
				plotcircle(2,-18+xr,-16,g);
			}
			plotcircle(5,-31+xr,-18,g);
			plotellipse(g,1,3,-27+xr,24,0);
			plotellipse(g,1,3,-32+xr,26,-30);
			plotellipse(g,1,3,-37+xr,24,-45);
			plotellipse(g,1,3,-38+xr,18,90);
			plotellipse(g,1,2,-34+xr,13,-135);
			//hand 2
			plotellipse(g,5,10,-5+xr,32,-120);
			plotellipse(g,3,8,-20+xr,30,-60);
			if(feat[5]==1) {
				plotcircle(2,-20+xr,-30,g);
			}
			plotcircle(5,-31+xr,-36,g);
			plotellipse(g,1,3,-27+xr,42,0);
			plotellipse(g,1,3,-32+xr,44,-30);
			plotellipse(g,1,3,-37+xr,42,-45);
			plotellipse(g,1,3,-38+xr,36,90);
			plotellipse(g,1,2,-34+xr,31,-135);
			//leg 1
			plotellipse(g,6,20,33+xr,-14,-10);
			plotellipse(g,4,15,33+xr,-45,15);
			//feet
			plotellipse(g,3,6,7+xr,-53,50);
			plotellipse(g,1,2,0+xr,-55,50);
			plotellipse(g,1,2,2+xr,-57,50);
			plotellipse(g,1,2,3+xr,-58,50);
			//leg 2
			plotellipse(g,6,18,15+xr,-9,30);
			plotellipse(g,4,17,9+xr,-36,-10);
			//feet
			plotellipse(g,3,6,26+xr,-61,70);
			plotellipse(g,1,2,25+xr,-65,70);
			plotellipse(g,1,2,20+xr,-63,70);
			plotellipse(g,1,2,22+xr,-64,70);
		}
		else if(feat[7]==2) {
			int ax=-17,ay=3;
			plotellipse(g,5,15,-5+xr,20,-120);
			plotellipse(g,3,8,-27+xr,16,-90);
			if(feat[5]==1) {
				plotcircle(2,-27+xr,-16,g);
			}
			plotcircle(4,-22+xr+ax,-16-ay,g);
			plotellipse(g,1,3,-21+xr+ax,22+ay,0);
			plotellipse(g,1,3,-26+xr+ax,24+ay,-30);
			plotellipse(g,1,3,-30+xr+ax,21+ay,-45);
			plotellipse(g,1,3,-28+xr+ax,15+ay,90);
			plotellipse(g,1,2,-25+xr+ax,12+ay,-135);
			//hand 2
			int r = -4,z=0;
			plotellipse(g,4,10,-8+xr,32,-120);
			plotellipse(g,3,8,-22+xr,30,-60);
			if(feat[5]==1) {
				plotcircle(2,-22+xr,-30,g);
			}
			plotcircle(5,-31+r+xr,-38+ay-z,g);
			plotellipse(g,1,3,-27+r+xr,42+z,0);
			plotellipse(g,1,3,-32+r+xr,44+z,-30);
			plotellipse(g,1,3,-37+r+xr,42+z,-45);
			plotellipse(g,1,3,-38+r+xr,36+z,90);
			plotellipse(g,1,2,-34+r+xr,31+z,-135);
			//leg 1
			plotellipse(g,6,20,33+xr,-14,-10);
			plotellipse(g,4,15,33+xr,-45,15);
			//feet
			plotellipse(g,3,6,7+xr,-53,50);	
			plotellipse(g,1,2,0+xr,-55,50);
			plotellipse(g,1,2,2+xr,-57,50);
			plotellipse(g,1,2,3+xr,-58,50);
			//leg 2
			plotellipse(g,6,18,15+xr,-9,30);
			plotellipse(g,4,17,9+xr,-36,-10);
			//feet
			plotellipse(g,3,6,26+xr,-61,70);
			plotellipse(g,1,2,25+xr,-65,70);
			plotellipse(g,1,2,20+xr,-63,70);
			plotellipse(g,1,2,22+xr,-64,70);
		}

		//leg spots
		if(feat[5]==1) {
			plotellipse(g,2,2,18+xr,-2, 0);
			plotellipse(g,2,2,12+xr,-12,0);
			plotellipse(g,2,2,8+xr,-30, 0);
			plotellipse(g,2,2,9+xr,-40, 0);
			plotellipse(g,2,2,30+xr,-5, 0);
			plotellipse(g,2,2,34+xr,-20, 0);
			plotellipse(g,2,2,34+xr,-40, 0);
			plotellipse(g,2,2,31+xr,-52, 0);
		}
		
		//body hair
		if(feat[6]==1) {
			if(feat[7] == 1) {
				plothair(g,5,12,0+xr,20,-120);
				plothair(g,3,8,-18+xr,16,-90);
				plothair(g,5,10,-5+xr,32,-120);
				plothair(g,3,8,-20+xr,30,-60);
				plothair(g,6,20,33+xr,-14,-10);
				plothair(g,4,15,33+xr,-45,15);
				plothair(g,6,18,15+xr,-9,30);
				plothair(g,4,17,9+xr,-36,-10);
			}
			else if(feat[7] == 0) {
				plothair(g,5,8,0+xr,20,-120);
				plothair(g,3,5,-12+xr,16,-90); 
				plothair(g,4,6,-3+xr,32,-120);
				plothair(g,3,5,-14+xr,30,-60);
				plothair(g,6,20,33+xr,-14,-10);
				plothair(g,4,15,33+xr,-45,15);
				plothair(g,6,18,15+xr,-9,30);
				plothair(g,4,17,9+xr,-36,-10);
			}
			else if(feat[7] == 2) {
				plothair(g,5,15,-5+xr,20,-120);
				plothair(g,3,8,-27+xr,16,-90);
				plothair(g,4,10,-8+xr,32,-120);
				plothair(g,3,8,-22+xr,30,-60);
				plothair(g,6,20,33+xr,-14,-10);
				plothair(g,4,15,33+xr,-45,15);
				plothair(g,6,18,15+xr,-9,30);
				plothair(g,4,17,9+xr,-36,-10);
			}
		}
		
		//tail
		if (feat[8] == 0){
			plotellipse(g,5,10,45+xr,13,50);
			if(feat[6]==1){
				plothair(g,5,10,45+xr,13,50);
			}
		}
		if (feat[8] == 1){
			plottri2(g,40,5,35+xr,13,45);
		}
		if (feat[8] == 2){
			plotcircle(5,42+xr,-10,g);
			plotcircle(3,42+xr,-10,g);
			plotline(45+xr,10,48+xr,20,g);
			plotline(45+xr,10,48+xr,0,g);
			plotline(42+xr,13,42+xr,20,g);
			plotline(42+xr,7,42+xr,0,g);
			plotline(45+xr,10,55+xr,10,g);
		}
	}

	public void graph(Graphics g) {
		//Central Point
		g.setColor(Color.blue);
		g.fillRect(originX-block/4,originY-block/4,block/2,block/2);
		//Principal Axes
		g.setColor(Color.red);
		g.drawLine(0,originY,getWidth(),originY);
		g.drawLine(originX,0,originX,getHeight());
		//Grid Lines
		for(int i=1;i<grid;i++) {
			block=(getX()+getWidth())/grid;
			g.setColor(Color.white);
			g.drawLine(originX+i*block,0,originX+i*block,getHeight());//Positive X
			g.drawLine(originX+i*block*(-1),0,originX+i*block*(-1),getHeight());//Negative X
			g.drawLine(0,originY+i*block,getWidth(),originY+i*block);//Negative Y
			g.drawLine(0,originY+i*block*(-1),getWidth(),originY+i*block*(-1));//Positive Y
		}
	}

	public static void init() {
		childset(parent1,parent2);
	}

	public void paint(Graphics g) {
		
		block=(getX()+getWidth())/grid;
		originX = (getX()+getWidth()+offX)/2;
		originY = (getY()+getHeight()+offY)/2;
		
		graph(g);

		plotanimal(-150,parent1,g);
		plotanimal(150,parent2,g);
		plotanimal(0,child,g);
		g.drawString("Parent 1",originX-150*block,originY - 100*block);
		g.drawString("Parent 2",originX+150*block,originY - 100*block);
		g.drawString("Child",originX,originY);
	}

	public static void main(String[] args) {
        init();

		JFrame f= new JFrame();
        f.setSize(1920,1024);

		JPanel p = new JPanel();
        p.setBounds(10,100,270,200);
		JPanel p2 = new JPanel();
        p2.setBounds(10,400,270,400);

	    Shapes s= new Shapes();
				
		JButton b1= new JButton("Zoom In");
        b1.setBounds(30,60,100,20);
		
		JButton b2= new JButton("Zoom Out");
        b2.setBounds(140,60,100,20);
		
		JButton b3= new JButton("Move Left");
        b3.setBounds(30,90,100,20);
		
		JButton b4= new JButton("Move Right");
        b4.setBounds(140,90,100,20);
		
		JButton b5= new JButton("Move Up");
        b5.setBounds(30,120,100,20);
		
		JButton b6= new JButton("Move Down");
        b6.setBounds(140,120,100,20);
		
		JButton b7= new JButton("Tri Tail");
        b7.setBounds(30,60,65,20);
		
		JButton b8= new JButton("Round Tail");
        b8.setBounds(100,60,65,20);
		
        JButton b9= new JButton("Triangle Ears");
        b9.setBounds(30,90,100,20);
		
		JButton b10= new JButton("Round Ears");
        b10.setBounds(140,90,100,20);
		
		JButton b11= new JButton("Big Beak");
        b11.setBounds(30,120,100,20);
		
		JButton b12= new JButton("Small Beak");
        b12.setBounds(140,120,100,20);
		
		JButton b13= new JButton("Toothed");
        b13.setBounds(30,150,100,20);
		
		JButton b14= new JButton("Toothless");
        b14.setBounds(140,150,100,20);
		
		JButton b15= new JButton("Body Spotted");
        b15.setBounds(30,180,100,20);
		
		JButton b16= new JButton("Body Spotless");
        b16.setBounds(140,180,100,20);
		
		JButton b17= new JButton("Body Hairy");
        b17.setBounds(30,210,100,20);
		
		JButton b18= new JButton("Body Hairless");
        b18.setBounds(140,210,100,20);
		
		JButton b19= new JButton("A/L Spotted");
        b19.setBounds(30,240,100,20);
		
		JButton b20= new JButton("A/L Spotless");
        b20.setBounds(140,240,100,20);
		
		JButton b21= new JButton("A/L Hairy");
        b21.setBounds(30,270,100,20);
		
		JButton b22= new JButton("A/L Hairless");
        b22.setBounds(140,270,100,20);
		
		JButton b23= new JButton("Arm Medium");
        b23.setBounds(30,300,100,20);
		
		JButton b24= new JButton("Arm Short");
        b24.setBounds(140,300,100,20);
		
		JButton b25= new JButton("Arm Tall");
        b25.setBounds(85,330,100,20);
		
		JButton b26= new JButton("Spiky Tail");
        b26.setBounds(170,60,65,20);

        p.add(b1);
		p.add(b2);	
		p.add(b3);	
		p.add(b4);
		p.add(b5);	
		p.add(b6);

		p2.add(b7);
		p2.add(b8);
		p2.add(b9);
		p2.add(b10);
		p2.add(b11);
		p2.add(b12);
		p2.add(b13);
		p2.add(b14);
		p2.add(b15);
		p2.add(b16);
		p2.add(b17);
		p2.add(b18);
		p2.add(b19);
		p2.add(b20);
		p2.add(b21);
		p2.add(b22);
		p2.add(b23);
		p2.add(b24);
		p2.add(b25);
		p2.add(b26);
		
		b1.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                grid=(int)(grid-20);
				s.repaint();
		    }
        });
		b2.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				grid=(int)(grid+20);
				s.repaint();
		    }
        });
		b3.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e){
				offX-=20;
				s.repaint();
		    }
        });
		b4.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				offX+=20;
				s.repaint();
		    }
        });
		b5.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				offY-=20;
				s.repaint();
		    }
        });
		b6.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				offY+=20;
				s.repaint();
		    }
        });
		b7.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				parent1[8] = 1;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b8.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				parent1[8] = 0;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b9.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				parent1[2] = 1;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b10.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				parent1[2] = 0;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b11.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				parent1[0] = 0;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b12.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				parent1[0] = 1;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b13.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				parent1[1] = 1;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b14.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				parent1[1] = 0;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b15.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				parent1[3] = 1;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b16.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e){
				parent1[3] = 0;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b17.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				parent1[4] = 1;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b18.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				parent1[4] = 0;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b19.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				parent1[5] = 1;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b20.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e){
				parent1[5] = 0;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b21.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				parent1[6] = 1;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b22.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				parent1[6] = 0;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b23.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				parent1[7] = 1;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b24.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				parent1[7] = 0;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b25.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				parent1[7] = 2;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		b26.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				parent1[8] = 2;
				childset(parent1,parent2);
				s.repaint();
		    }
        });
		
		p.setLayout(null);
		p2.setLayout(null);

		f.setVisible(true);

		f.add(p);
		f.add(p2);
		f.add(s);

		f.setDefaultCloseOperation(f.EXIT_ON_CLOSE); 
    }
}