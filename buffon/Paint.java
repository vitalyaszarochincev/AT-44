package BuffonNeedle;

import java.awt.Graphics2D;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.geom.Line2D;
import java.util.Random;
import javax.swing.JComponent;

public class Paint extends JComponent
{
	private static final long serialVersionUID = 1L;
	Needle needle;
	Random gen = new Random();
	
	public Paint() 
	{
		this.needle = new Needle();
		addMouseListener(new Click());
	}
	
	class Click implements MouseListener 
	{

		@Override
		public void mouseClicked(MouseEvent arg0) 
		{
			repaint();
		}

		public void mouseEntered(MouseEvent arg0) {}
		public void mouseExited(MouseEvent arg0) {}
		public void mousePressed(MouseEvent arg0) {}
		public void mouseReleased(MouseEvent arg0) {}
	}
	
	public void paintComponent(Graphics graph) 
	{
		final int LINE_X_LEFT = 0;
		final int LINE_X_RIGHT = 700;
		final int LINE_Y_HIGH = 150;
		final int LINE_Y_LOW = 250;
		final int STATUS_X = 150;
		final int STATUS_Y = 50;
		final int STATUS_OFFSET = 25;
		
		Graphics2D graph2D = (Graphics2D) graph;
		graph2D.drawLine(LINE_X_LEFT, LINE_Y_LOW, LINE_X_RIGHT, LINE_Y_LOW);
		graph2D.drawLine(LINE_X_LEFT, LINE_Y_HIGH, LINE_X_RIGHT, LINE_Y_HIGH);
		
		needle.drop();
		Line2D needleLine = new Line2D.Double(needle.xLow, needle.yLow, needle.xHigh, needle.yHigh);
		graph2D.draw(needleLine);
		
		if (needleLine.intersectsLine(LINE_X_LEFT, LINE_Y_LOW, LINE_X_RIGHT, LINE_Y_LOW) || needleLine.intersectsLine(LINE_X_LEFT, LINE_Y_HIGH, LINE_X_RIGHT, LINE_Y_HIGH)) 
		{
			needle.hits++;
			graph2D.drawString("Hit", STATUS_X, STATUS_Y);
		}
		else
		{
			graph2D.drawString("Miss", STATUS_X, STATUS_Y);
			needle.miss++;
		}
		
		graph2D.drawString("Total miss = " + needle.miss, STATUS_X, STATUS_Y + STATUS_OFFSET);
		graph2D.drawString("Total hits = " + needle.hits, STATUS_X, STATUS_Y + (STATUS_OFFSET * 2));
	}
}