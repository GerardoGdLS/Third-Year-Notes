/*
 * File name: BorderDecorator.java
 * Lab 6 Exercise A
 * Nov 1st 2024
 * By: Gerardo Garcia de Leon
 */

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;

public class BorderDecorator extends Decorator{
	
	public BorderDecorator(Component t, int x, int y, int width, int height) {
		super(t, x, y, width, height);
	}

	    @Override
	    public void draw(Graphics g) {
	        super.draw(g);

	        Graphics2D g2d = (Graphics2D) g;
	        g2d.setColor(Color.BLACK);
	        g2d.setStroke(new BasicStroke(1, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[]{5}, 0)); // Dashed line
	        g2d.drawRect(x, y, width, height);
	    }
	}
