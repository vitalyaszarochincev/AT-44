package BuffonNeedle;

import javax.swing.JFrame;

public class GUI extends JFrame
{
	private static final long serialVersionUID = 1L;
	
	public GUI() 
	{
		final int WINDOW_SIZE = 1000;
		final int EXCESS = 150;
		
		setSize(WINDOW_SIZE, WINDOW_SIZE - EXCESS);
		setTitle("buffon");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		add(new Paint());
		setVisible(true);
	}
	
	public static void main(String[] args) 
	{
		@SuppressWarnings("unused")
		GUI window = new GUI();
	}
}