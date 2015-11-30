package BuffonNeedle;

import java.util.Random;

public class Needle 
{
	private Random generator;
	public int hits;
	public int miss;
	public int drops;
	public int yLow;
	public int xLow;
	public double yHigh;
	public double xHigh;
	private double angle;
	public final int Y_MIN = 200;
	public final int Y_MAX = 100;
	private final double LEN_ATTITUDE = 0.13;
	private final int NEEDLE_LEN = (int)((double)(Y_MIN - Y_MAX) * LEN_ATTITUDE);

	public Needle() 
	{
		this.hits = 0;
		this.miss = 0;
		this.drops = 0;
		this.generator = new Random();
	}
	
	public void drop() 
	{
		final int MAX_ANGLE = 180;
		final int X_MAX = 500;
		final int X_MIN = 50;
		
		this.yLow = generator.nextInt(Y_MAX) + Y_MIN;
		this.xLow = generator.nextInt(X_MAX) + X_MIN;
		this.angle = MAX_ANGLE * generator.nextDouble();
		
		this.yHigh = yLow + (NEEDLE_LEN * Math.sin(Math.toRadians(angle)));
		this.xHigh = xLow + (NEEDLE_LEN * Math.cos(Math.toRadians(angle)));
		
		this.drops++;
	}
	
	public double getChance()
	{
		return (double)this.hits / (double)this.drops;
	}
	
	public double getTheoreticalChance()
	{
		return (2 * NEEDLE_LEN) / ((Y_MIN - Y_MAX) * Math.PI); 
	}
	
	public double getError()
	{
		return Math.abs(getTheoreticalChance() - getChance()) / getTheoreticalChance();
	}
}