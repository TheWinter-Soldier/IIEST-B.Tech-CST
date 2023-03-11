package PACK1.CLIPPING_ALGORITHMS;

import java.awt.*;
import java.lang.Math;
import PACK1.*;
import PACK1.LINE_ALGORITHMS.*;
import PACK1.UTILITIES.*;

public class SutherlandCohen_Method {
    private int INSIDE = 0;     //0000  
    private int TOP = 8;        //1000 
    private int BOTTOM = 4;     //0100 
    private int RIGHT = 2;      //0010 
    private int LEFT = 1;       //0001

    private double s;
    
    public int generateCode(int x,int y) {
        int code = INSIDE;    // intially initializing as being inside

        if(x < ESS_VAR.Wx_Min) {	        //Lies to the left of window
            code |= LEFT;
        }
        else if(x > ESS_VAR.Wx_Max) {       //Lies to the right of window
            code |= RIGHT;
        }

        if(y < ESS_VAR.Wy_Min) {	        //Lies below the window
            code |= BOTTOM;
        }
        else if(y > ESS_VAR.Wy_Max) {       //Lies above the window
            code |= TOP;
        }
            
        return code;
    }

    public void clipLine(int Ex1,int Ey1,int Ex2,int Ey2,Graphics g) {
        if(Ex1 != Ex2) {
            s = (double)(Ey1-Ey2)/(Ex1-Ex2);
        }

        int E1 = generateCode(Ex1,Ey1);
        int E2 = generateCode(Ex2,Ey2);

        int[] a = new int[3];
        int[] b = new int[3];
        int[] c = new int[3];

        DDA J1 = new DDA();

        if((E1|E2) != 0) {
            if((E1&E2) == 0) {
                if((E1 != 0)&&(E2 != 0)) {
                    //Both points are outside but the line passes throuth the window
                    a = findIntersection(Ex1,Ey1,s);
                    b = findIntersection(Ex2,Ey2,s);

                    J1.makeLine(g,a[1],a[2],b[1],b[2],Color.RED);
                }
                else if(((E1==0) || (E2==0)) && !((E1==0) && (E2==0))) {
                    //One point lies inside the window and one outside
                    if(E1==0) {
                        c = findIntersection(Ex2,Ey2,s);

                        J1.makeLine(g,Ex1,Ey1,c[1],c[2],Color.RED);
                    }
                    else {
                        c = findIntersection(Ex1,Ey1,s);

                        J1.makeLine(g,c[1],c[2],Ex2,Ey2,Color.RED);
                    }
                }
            }
            else {
                //Both the points are outside and no part of line passes through the window
                //Nothing to do
            }
        }
        else {
            //Both points are inside the window
            J1.makeLine(g,Ex1,Ey1,Ex2,Ey2,Color.RED);
        }
    }

    public int[] findIntersection(int x,int y,double slope) {
        int E = generateCode(x,y);
        int[] result = new int[3];

        if((E & 0b0001) != 0) {
            //Intersection with left-clipper
            result[0] = 1;
            result[1] = ESS_VAR.Wx_Min;
            result[2] = y + (int)Math.round(slope*(result[1]-x));

            if((result[2]<=ESS_VAR.Wy_Max)&&(result[2]>=ESS_VAR.Wy_Min)) {
                return result;
            }
        }

        if((E & 0b0010) != 0) {
            //Intersection with right-clipper
            result[0] = 2;
            result[1] = ESS_VAR.Wx_Max;
            result[2] = y + (int)Math.round(slope*(result[1]-x));

            if((result[2]<=ESS_VAR.Wy_Max)&&(result[2]>=ESS_VAR.Wy_Min)) {
                return result;
            }
        }
        
        if((E & 0b1000) != 0) {
            //Intersection with top-clipper
            result[0] = 8;
            result[2] = ESS_VAR.Wy_Max;
            result[1] = x + (int)Math.round((result[2]-y)/slope);

            if((result[1]<=ESS_VAR.Wx_Max)&&(result[2]>=ESS_VAR.Wx_Min)) {
                return result;
            }
        }
        
        if((E & 0b0100) != 0) {
            //Intersection with bottom-clipper
            result[0] = 4;
            result[2] = ESS_VAR.Wy_Min;
            result[1] = x + (int)Math.round((result[2]-y)/slope);

            if((result[1]<=ESS_VAR.Wx_Max)&&(result[2]>=ESS_VAR.Wx_Min)) {
                return result;
            }
        }

        return result;
    }
}