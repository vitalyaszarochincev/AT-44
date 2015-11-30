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
	
	public Paint() 
	{
		this.needle = new Needle();
	}
	
	public void paintComponent(Graphics graph) 
	{
		final int LINE_X_LEFT = 0;
		final int LINE_X_RIGHT = 1000;
		final int LINE_Y_LOW = ((needle.Y_MAX + needle.Y_MIN) / 2) + needle.Y_MAX;
		final int STATUS_X = 25;
		final int STATUS_Y = 25;
		
		repaint();
		needle.drop();
		
		Graphics2D graph2D = (Graphics2D) graph;		
		Line2D needleLine = new Line2D.Double(needle.xLow, needle.yLow - needle.Y_MAX, needle.xHigh, needle.yHigh - needle.Y_MAX);
		
		drawExperiment(graph2D, needle, needleLine);
		
		if (needleLine.intersectsLine(LINE_X_LEFT, LINE_Y_LOW - needle.Y_MAX, LINE_X_RIGHT, LINE_Y_LOW - needle.Y_MAX)) 
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
		
		/*try 
		{
			Thread.currentThread();
			Thread.sleep(1000);
		} catch (InterruptedException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}*/
	}
	
	private static int scalingX(int drops)
	{
		final int COORDINATE_X_LEFT = 100;
		final int SCALE = 100;
		
		return (int)(Math.log10(drops) * SCALE + COORDINATE_X_LEFT);
	}
	
	private static int scallingY(double d)
	{
		final int COORDINATE_Y_LOW = 750;
		final int SCALE = 100;
		final int PIXIELS_IN_PERSENT = 15;
		final int SEGMET_NUM = 4;
		
		return (int)(COORDINATE_Y_LOW - (d * SCALE * PIXIELS_IN_PERSENT / SEGMET_NUM));
	}
	
	private static void drawGraphic(Graphics2D graph2D, Needle needle)
	{
		final int COORDINATE_X_CENTER = 100;
		final int COORDINATE_Y_CENTER = 750;
		final int AXIS_X_START = COORDINATE_X_CENTER - 50;
		final int AXIS_Y_START = COORDINATE_Y_CENTER + 50;
		final int AXIS_X_END = 900;
		final int AXIS_Y_END = 250;
		final int POINTER_OFFSET = 10;
		final int MARK_OFFSET = 5;
		final int SCALE = 100;
		final int SEGMENT = 100;
		final int HATCH = 15;
		final int AXIS_NAME_OFFSET = 10;
		
		graph2D.drawLine(AXIS_X_START, COORDINATE_Y_CENTER, AXIS_X_END, COORDINATE_Y_CENTER);
		graph2D.drawLine(COORDINATE_X_CENTER, AXIS_Y_START, COORDINATE_X_CENTER, AXIS_Y_END);
		graph2D.drawLine(AXIS_X_END, COORDINATE_Y_CENTER, AXIS_X_END - POINTER_OFFSET, COORDINATE_Y_CENTER - POINTER_OFFSET);
		graph2D.drawLine(AXIS_X_END, COORDINATE_Y_CENTER, AXIS_X_END - POINTER_OFFSET, COORDINATE_Y_CENTER + POINTER_OFFSET);
		graph2D.drawLine(COORDINATE_X_CENTER, AXIS_Y_END, COORDINATE_X_CENTER + POINTER_OFFSET, AXIS_Y_END + POINTER_OFFSET);
		graph2D.drawLine(COORDINATE_X_CENTER, AXIS_Y_END, COORDINATE_X_CENTER - POINTER_OFFSET, AXIS_Y_END + POINTER_OFFSET);
		
		final char coordinateXScale[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
		
		for(int i = COORDINATE_X_CENTER; i < AXIS_X_END; i += SEGMENT)
		{
			graph2D.drawLine(i, COORDINATE_Y_CENTER - MARK_OFFSET, i, COORDINATE_Y_CENTER + MARK_OFFSET);
			graph2D.drawChars(coordinateXScale, (int)(i / SCALE) - 1, 1, i + MARK_OFFSET, COORDINATE_Y_CENTER + (MARK_OFFSET * 4));
		}
		
		final String coordinateYScale[] = {"0.25", "0.5", "0.75", "1"};
		
		for(int i = COORDINATE_Y_CENTER; i > AXIS_Y_END; i -= SEGMENT)
		{
			graph2D.drawLine(COORDINATE_X_CENTER - MARK_OFFSET, i, COORDINATE_X_CENTER + MARK_OFFSET, i);
			
			if(i < (COORDINATE_Y_CENTER))
				graph2D.drawString(coordinateYScale[6 - (int)(i / SCALE)], COORDINATE_X_CENTER - (6 * MARK_OFFSET), i + (MARK_OFFSET * 3));
		}
		
		graph2D.drawString("X", AXIS_X_END - (AXIS_NAME_OFFSET / 2), COORDINATE_Y_CENTER + (AXIS_NAME_OFFSET * 2));
		graph2D.drawString("Y", COORDINATE_X_CENTER - (AXIS_NAME_OFFSET * 2), AXIS_Y_END + AXIS_NAME_OFFSET);
		
		int graphicCoordinateX = scalingX(needle.drops);
		int graphicCoordinateY =  scallingY(needle.getChance());
		
		GUI.graphPointsX.add(graphicCoordinateX);
		GUI.graphPointsY.add(graphicCoordinateY);
		
		int pointsX[] = new int [GUI.graphPointsX.size()];
		int pointsY[] = new int [GUI.graphPointsY.size()];
				
		for(int i = 0; i < GUI.graphPointsX.size(); i++)
			pointsX[i] = GUI.graphPointsX.get(i);
		
		for(int i = 0; i < GUI.graphPointsY.size(); i++)
			pointsY[i] = GUI.graphPointsY.get(i);
		
		graph2D.setColor(Color.red);
		graph2D.drawPolyline(pointsX, pointsY, GUI.graphPointsX.size());
		
		graph2D.setColor(Color.black);
		
		for(int i = graphicCoordinateX; i > COORDINATE_X_CENTER; i -= HATCH)
			graph2D.drawLine(i, graphicCoordinateY, i - MARK_OFFSET, graphicCoordinateY);
		
		for(int i = graphicCoordinateY; i < COORDINATE_Y_CENTER; i+= HATCH)
			graph2D.drawLine(graphicCoordinateX, i, graphicCoordinateX, i + MARK_OFFSET);	
	}
	
	private static void drawStatus(Graphics2D graph2D, Needle needle)
	{
		final int STATUS_X = 25;
		final int STATUS_Y = 25;
		final int STATUS_OFFSET = 25;
		
		graph2D.drawString("Total miss : " + needle.miss + "    Total drops : " + needle.drops, STATUS_X, STATUS_Y + STATUS_OFFSET);
		graph2D.drawString("Total hits : " + needle.hits + "    Chance : " + needle.getChance(), STATUS_X, STATUS_Y + (STATUS_OFFSET * 2));		
	}
	
	private static void drawExperiment(Graphics2D graph2D, Needle needle, Line2D needleLine)
	{
		final int LINE_X_LEFT = 0;
		final int LINE_X_RIGHT = 1000;
		final int LINE_Y_LOW = ((needle.Y_MAX + needle.Y_MIN) / 2) + needle.Y_MAX;
		final int STATUS_OFFSET = 25;
		
		graph2D.drawLine(LINE_X_LEFT, LINE_Y_LOW - needle.Y_MAX, LINE_X_RIGHT, LINE_Y_LOW - needle.Y_MAX);
		
		for(int i = 0; i < LINE_X_RIGHT; i += (STATUS_OFFSET * 2))
		{
			graph2D.drawLine(i, needle.Y_MAX, i + STATUS_OFFSET, needle.Y_MAX);
			graph2D.drawLine(i, needle.Y_MIN, i + STATUS_OFFSET, needle.Y_MIN);
		}
		
		graph2D.draw(needleLine);
	}
}