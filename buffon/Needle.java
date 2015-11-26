package BuffonNeedle;

import java.util.Random;

public class Needle 
{
	private Random generator;
	public int hits;
	public int miss;
	public int yLow;
	public int xLow;
	public double yHigh;
	public double xHigh;
	private double angle;
	public final int Y_MIN = 200;
	public final int Y_MAX = 100;

	public Needle() 
	{
		this.hits = 0;
		this.miss = 0;
		this.generator = new Random();
	}
	
	public void drop() 
	{
		final int NEEDLE_LEN = (int)((double)(Y_MIN - Y_MAX) * 0.13);
		final int MAX_ANGLE = 180;
		final int X_MAX = 900;
		final int X_MIN = 50;
		
		this.yLow = generator.nextInt(Y_MAX) + Y_MIN;
		this.xLow = generator.nextInt(X_MAX) + X_MIN;
		this.angle = MAX_ANGLE * generator.nextDouble();
		
		this.yHigh = yLow + (NEEDLE_LEN * Math.sin(Math.toRadians(angle)));
		this.xHigh = xLow + (NEEDLE_LEN * Math.cos(Math.toRadians(angle)));
	}
}