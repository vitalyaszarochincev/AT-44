package BuffonNeedle;

import java.awt.Graphics2D;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.geom.Line2D;
import java.util.ArrayList;
import BuffonNeedle.GUI;

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
		final int STATUS_OFFSET = 25;
		final int COORDINATE_X_LEFT = 100;
		final int COORDINATE_Y_LOW = 750;
		final int COORDINATE_X_RIGHT = 900;
		final int COORDINATE_Y_HIGH = COORDINATE_Y_LOW - 500;
		final int COORDINATE_OFFSET = 50;
		final int POINTER_OFFSET = 10;
		final int MARK_OFFSET = 5;
		final int SCALE = 100;
		final int SEGMET_NUM = 4;
		final int PIXIELS_IN_PERSENT = 15;
		final int SEGMENT_OFFSET = 100;
		
		repaint();
		
		Graphics2D graph2D = (Graphics2D) graph;
		graph2D.drawLine(LINE_X_LEFT, LINE_Y_LOW - needle.Y_MAX, LINE_X_RIGHT, LINE_Y_LOW - needle.Y_MAX);
		
		for(int i = 0; i < LINE_X_RIGHT; i += (STATUS_OFFSET * 2))
		{
			graph2D.drawLine(i, needle.Y_MAX, i + STATUS_OFFSET, needle.Y_MAX);
			graph2D.drawLine(i, needle.Y_MIN, i + STATUS_OFFSET, needle.Y_MIN);
		}
		
		needle.drop();
		Line2D needleLine = new Line2D.Double(needle.xLow, needle.yLow - needle.Y_MAX, needle.xHigh, needle.yHigh - needle.Y_MAX);
		graph2D.draw(needleLine);
		
		if (needleLine.intersectsLine(LINE_X_LEFT, LINE_Y_LOW - needle.Y_MAX, LINE_X_RIGHT, LINE_Y_LOW - needle.Y_MAX)) 
		{
			needle.hits++;
			graph2D.drawString("Hit", STATUS_X, STATUS_Y);
		}else
		{
			needle.miss++;
			graph2D.drawString("Miss", STATUS_X, STATUS_Y);
		}
		
		int totalDrops = needle.hits + needle.miss;
		double chance = (double)needle.hits / (double)totalDrops;
	
		graph2D.drawString("Total miss : " + needle.miss + "    Total drops : " + totalDrops, STATUS_X, STATUS_Y + STATUS_OFFSET);
		graph2D.drawString("Total hits : " + needle.hits + "    Chance : " + chance, STATUS_X, STATUS_Y + (STATUS_OFFSET * 2));
		
		graph2D.drawLine(COORDINATE_X_LEFT - COORDINATE_OFFSET, COORDINATE_Y_LOW, COORDINATE_X_RIGHT, COORDINATE_Y_LOW);
		graph2D.drawLine(COORDINATE_X_LEFT, COORDINATE_Y_LOW + COORDINATE_OFFSET, COORDINATE_X_LEFT, COORDINATE_Y_HIGH);
		graph2D.drawLine(COORDINATE_X_RIGHT, COORDINATE_Y_LOW, COORDINATE_X_RIGHT - POINTER_OFFSET, COORDINATE_Y_LOW - POINTER_OFFSET);
		graph2D.drawLine(COORDINATE_X_RIGHT, COORDINATE_Y_LOW, COORDINATE_X_RIGHT - POINTER_OFFSET, COORDINATE_Y_LOW + POINTER_OFFSET);
		graph2D.drawLine(COORDINATE_X_LEFT, COORDINATE_Y_HIGH, COORDINATE_X_LEFT + POINTER_OFFSET, COORDINATE_Y_HIGH + POINTER_OFFSET);
		graph2D.drawLine(COORDINATE_X_LEFT, COORDINATE_Y_HIGH, COORDINATE_X_LEFT - POINTER_OFFSET, COORDINATE_Y_HIGH + POINTER_OFFSET);
		
		char coordinateX[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
		
		for(int i = COORDINATE_X_LEFT; i < COORDINATE_X_RIGHT; i += SEGMENT_OFFSET)
		{
			graph2D.drawLine(i, COORDINATE_Y_LOW - MARK_OFFSET, i, COORDINATE_Y_LOW + MARK_OFFSET);
			graph2D.drawChars(coordinateX, (int)(i / SCALE) - 1, 1, i + MARK_OFFSET, COORDINATE_Y_LOW + (MARK_OFFSET * 4));
		}
		
		String coordinateY[] = {"0.25", "0.5", "0.75", "1"};
		
		for(int i = COORDINATE_Y_LOW; i > COORDINATE_Y_HIGH; i -= SEGMENT_OFFSET)
		{
			graph2D.drawLine(COORDINATE_X_LEFT - MARK_OFFSET, i, COORDINATE_X_LEFT + MARK_OFFSET, i);
			
			if(i < (COORDINATE_Y_LOW))
				graph2D.drawString(coordinateY[6 - (int)(i / SCALE)], COORDINATE_X_LEFT - (6 * MARK_OFFSET), i + (MARK_OFFSET * 3));
		}
		
		graph2D.drawString("X", COORDINATE_X_RIGHT - MARK_OFFSET, COORDINATE_Y_LOW + (2 * POINTER_OFFSET));
		graph2D.drawString("Y", COORDINATE_X_LEFT - (2 * POINTER_OFFSET), COORDINATE_Y_HIGH + POINTER_OFFSET);
		
		GUI.graphPointsX.add((int)(Math.log10(totalDrops) * SCALE + COORDINATE_X_LEFT));
		GUI.graphPointsY.add((int)(COORDINATE_Y_LOW - (chance * SCALE * PIXIELS_IN_PERSENT / SEGMET_NUM)));
		
		int pointsX[] = new int [GUI.graphPointsX.size()];
		int pointsY[] = new int [GUI.graphPointsY.size()];
				
		for(int i = 0; i < GUI.graphPointsX.size(); i++)
			pointsX[i] = GUI.graphPointsX.get(i);
		
		for(int i = 0; i < GUI.graphPointsY.size(); i++)
			pointsY[i] = GUI.graphPointsY.get(i);
		
		graph2D.setColor(Color.red);
		graph2D.drawPolyline(pointsX, pointsY, GUI.graphPointsX.size());
		
		graph2D.setColor(Color.black);
		
		for(int i = (int)(Math.log10(totalDrops) * SCALE + COORDINATE_X_LEFT); i > COORDINATE_X_LEFT; i -= (4 * MARK_OFFSET))
			graph2D.drawLine(i, (int)(COORDINATE_Y_LOW - (chance * SCALE * PIXIELS_IN_PERSENT / SEGMET_NUM)), i - MARK_OFFSET, (int)(COORDINATE_Y_LOW - (chance * SCALE * PIXIELS_IN_PERSENT / SEGMET_NUM)));
		
		for(int i = (int)(COORDINATE_Y_LOW - (chance * SCALE * PIXIELS_IN_PERSENT / SEGMET_NUM)); i < COORDINATE_Y_LOW; i+= (3 * MARK_OFFSET))
			graph2D.drawLine((int)(Math.log10(totalDrops) * SCALE + COORDINATE_X_LEFT), i, (int)(Math.log10(totalDrops) * SCALE + COORDINATE_X_LEFT), i + MARK_OFFSET);
		
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
}