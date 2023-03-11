package PACK1;

import java.lang.*;

public class ESS_VAR {
    public static int Wx_Max=0;        //Maximum X Co-ord. of clipping-window
    public static int Wy_Max=0;        //Maximum Y Co-ord. of clipping-window
    public static int Wx_Min=0;        //Minimum X Co-ord. of clipping-window
    public static int Wy_Min=0;        //Minimum Y Co-ord. of clipping-window   

    public static int n=3;        //Number of sides of polygon
    public static int j=0;
    
    public static int[] X = new int[n];     //X Co-ords. of vertices
    public static int[] Y = new int[n];     //Y Co-ords. of vertices

    public static int X1=X[j];
	public static int Y1=Y[j];
	public static int X2=X[j+1];
	public static int Y2=Y[j+1];       //Temporary variables for functioning of Clipping method
}