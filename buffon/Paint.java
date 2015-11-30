package BuffonNeedle;

import java.awt.Graphics2D;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.geom.Line2D;

import javax.swing.JComponent;

public class Paint extends JComponent
{
	private static final long serialVersionUID = 1L;
	private Needle needle;
	private final static int COORDINATE_Y_CENTER = 500;
	private final static int COORDINATE_X_CENTER = 100;
	private final static int SCALE = 50;
	private final static int STATUS_OFFSET = 25;
	private final static int STATUS_X = 25;
	private final static int STATUS_Y = 25;
	
	public Paint() 
	{
		this.needle = new Needle();
	}
	
	public void paintComponent(Graphics graph) 
	{
		final int LINE_X_LEFT = 0;
		final int LINE_Y_LOW = ((needle.Y_MAX + needle.Y_MIN) / 2) + needle.Y_MAX;
		
		repaint();
		needle.drop();
		
		Graphics2D graph2D = (Graphics2D) graph;		
		Line2D needleLine = new Line2D.Double(needle.xLow, needle.yLow - needle.Y_MAX, needle.xHigh, needle.yHigh - needle.Y_MAX);
		
		drawExperiment(graph2D, needle, needleLine);
		
		if (needleLine.intersectsLine(LINE_X_LEFT, LINE_Y_LOW - needle.Y_MAX, GUI.WINDOW_SIZE, LINE_Y_LOW - needle.Y_MAX)) 
		{
			needle.hits++;
			graph2D.drawString("Hit", STATUS_X, STATUS_Y);
		}else
		{
			needle.miss++;
			graph2D.drawString("Miss", STATUS_X, STATUS_Y);
		}
		
		drawStatus(graph2D, needle);
		drawGraphic(graph2D, needle);
		
//		try 
//		{
//			Thread.sleep(100);
//		} catch (InterruptedException e) 
//		{
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
	}
	
	private static int scalingX(int drops)
	{	
		return (int)(Math.log10(drops) * SCALE + COORDINATE_X_CENTER);
	}
	
	private static int scallingY(double chance)
	{
		final int PIXIELS_IN_PERSENT = 16;
		final int SEGMET_NUM = 4;
		
		return (int)(COORDINATE_Y_CENTER - ((chance * SCALE * PIXIELS_IN_PERSENT) / SEGMET_NUM));
	}
	
	private static void drawGraphic(Graphics2D graph2D, Needle needle)
	{
		final int AXIS_X_START = COORDINATE_X_CENTER - 50;
		final int AXIS_Y_START = COORDINATE_Y_CENTER + 50;
		final int AXIS_X_END = GUI.WINDOW_SIZE - 100;
		final int AXIS_Y_END = needle.Y_MIN + 50;
		final int MARK_LEN = 5;
		final int AXIS_NAME_OFFSET = 10;
		
		graph2D.drawLine(AXIS_X_START, COORDINATE_Y_CENTER, AXIS_X_END, COORDINATE_Y_CENTER);
		graph2D.drawLine(COORDINATE_X_CENTER, AXIS_Y_START, COORDINATE_X_CENTER, AXIS_Y_END);
		graph2D.drawLine(AXIS_X_END, COORDINATE_Y_CENTER, AXIS_X_END - MARK_LEN, COORDINATE_Y_CENTER - MARK_LEN);
		graph2D.drawLine(AXIS_X_END, COORDINATE_Y_CENTER, AXIS_X_END - MARK_LEN, COORDINATE_Y_CENTER + MARK_LEN);
		graph2D.drawLine(COORDINATE_X_CENTER, AXIS_Y_END, COORDINATE_X_CENTER + MARK_LEN, AXIS_Y_END + MARK_LEN);
		graph2D.drawLine(COORDINATE_X_CENTER, AXIS_Y_END, COORDINATE_X_CENTER - MARK_LEN, AXIS_Y_END + MARK_LEN);
		
		final char coordinateXScale[] = {'0', '1', '2', '3', '4', '5', '6', '7'};
		
		for(int i = COORDINATE_X_CENTER; i < AXIS_X_END; i += SCALE)
		{
			graph2D.drawLine(i, COORDINATE_Y_CENTER - MARK_LEN, i, COORDINATE_Y_CENTER + MARK_LEN);
			graph2D.drawChars(coordinateXScale, (int)(i / SCALE) - 2, 1, i + MARK_LEN, COORDINATE_Y_CENTER + (MARK_LEN * 3));
		}
		
		final String coordinateYScale[] = {"0.25", "0.5", "0.75", "1"};
		
		for(int i = COORDINATE_Y_CENTER; i > AXIS_Y_END; i -= SCALE)
		{
			graph2D.drawLine(COORDINATE_X_CENTER - MARK_LEN, i, COORDINATE_X_CENTER + MARK_LEN, i);
			
			if(i < (COORDINATE_Y_CENTER))
				graph2D.drawString(coordinateYScale[9 - (int)(i / SCALE)], COORDINATE_X_CENTER - (6 * MARK_LEN), i + (MARK_LEN * 3));
		}
		
		graph2D.drawString("X", AXIS_X_END - (AXIS_NAME_OFFSET / 2), COORDINATE_Y_CENTER + (AXIS_NAME_OFFSET * 2));
		graph2D.drawString("Y", COORDINATE_X_CENTER - (AXIS_NAME_OFFSET * 2), AXIS_Y_END + AXIS_NAME_OFFSET);
		
		int graphicCoordinateX = scalingX(needle.drops);
		int graphicCoordinateY =  scallingY(needle.getChance());
		int graphicErrorCoordinateY = scallingY(needle.getError());
		
		GUI.graphChancePointsX.add(graphicCoordinateX);
		GUI.graphChancePointsY.add(graphicCoordinateY);
		GUI.graphErrorPointsY.add(graphicErrorCoordinateY);
		
		int pointsX[] = new int [GUI.graphChancePointsX.size()];
		int pointsY[] = new int [GUI.graphChancePointsY.size()];
		int errorPointsY[] = new int [GUI.graphErrorPointsY.size()];
				
		for(int i = 0; i < GUI.graphChancePointsX.size(); i++)
		{
			pointsX[i] = GUI.graphChancePointsX.get(i);
			pointsY[i] = GUI.graphChancePointsY.get(i);
			errorPointsY[i] = GUI.graphErrorPointsY.get(i);
		}
		
		graph2D.setColor(Color.blue);
		graph2D.drawPolyline(pointsX, pointsY, GUI.graphChancePointsX.size());
		
		graph2D.setColor(Color.red);
		graph2D.drawPolyline(pointsX, errorPointsY, GUI.graphChancePointsX.size());
	}
	
	private static void drawStatus(Graphics2D graph2D, Needle needle)
	{	
		graph2D.drawString("Total miss : " + needle.miss, STATUS_X, (STATUS_Y * 2));
		graph2D.drawString("Total hits : " + needle.hits, STATUS_X, (STATUS_Y * 3));		
		graph2D.drawString("Total drops : " + needle.drops, (STATUS_X * 6), (STATUS_Y * 2));
		graph2D.drawString("Chance : " + needle.getChance(), (STATUS_X * 6), (STATUS_Y * 3));		
		graph2D.drawString("Theoretical chance : " + needle.getTheoreticalChance(), (STATUS_X * 12), (STATUS_Y * 2));
		graph2D.drawString("Error : " + needle.getError(), (STATUS_X * 14), (STATUS_Y * 3));		
	}
	
	private static void drawExperiment(Graphics2D graph2D, Needle needle, Line2D needleLine)
	{
		final int LINE_X_LEFT = 0;
		final int LINE_Y_LOW = ((needle.Y_MAX + needle.Y_MIN) / 2) + needle.Y_MAX;
		
		graph2D.drawLine(LINE_X_LEFT, LINE_Y_LOW - needle.Y_MAX, GUI.WINDOW_SIZE, LINE_Y_LOW - needle.Y_MAX);
		
		for(int i = 0; i < GUI.WINDOW_SIZE; i += (STATUS_OFFSET * 2))
		{
			graph2D.drawLine(i, needle.Y_MAX, i + STATUS_OFFSET, needle.Y_MAX);
			graph2D.drawLine(i, needle.Y_MIN, i + STATUS_OFFSET, needle.Y_MIN);
		}
		
		graph2D.draw(needleLine);
	}
}