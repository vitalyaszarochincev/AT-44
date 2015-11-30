package BuffonNeedle;

import java.io.IOException;
import java.util.ArrayList;

import javax.swing.JFrame;

public class GUI extends JFrame
{
	private static final long serialVersionUID = 1L;
	public static ArrayList<Integer> graphChancePointsX = new ArrayList<Integer>();
	public static ArrayList<Integer> graphChancePointsY = new ArrayList<Integer>();
	public static ArrayList<Integer> graphErrorPointsY = new ArrayList<Integer>();
	public static final int WINDOW_SIZE = 600;
	
	public GUI() 
	{	
		setSize(WINDOW_SIZE, WINDOW_SIZE);
		setTitle("buffon");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		add(new Paint());
		setVisible(true);
	}
	
	public static void main(String[] args) throws IOException 
	{
		@SuppressWarnings("unused")
		GUI window = new GUI();
	}
}