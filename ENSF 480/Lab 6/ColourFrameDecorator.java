/*
 * File name: ColourFrameDecorator.java
 * Lab 6 Exercise A
 * Nov 1st 2024
 * By: Gerardo Garcia de Leon
 */

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Stroke;

public class ColourFrameDecorator extends Decorator{
	private int thickness;
	
	public void draw(Graphics g) {
		super.draw(g);
		Graphics2D g2d = (Graphics2D) g;
		Stroke oldStroke = g2d.getStroke();
		Color oldColor = g2d.getColor();
		g2d.setStroke(new BasicStroke(thickness));
		g2d.setColor(Color.red);
		g2d.drawRect(x,  y, width, height);
		g2d.setStroke(oldStroke);
		g2d.setColor(oldColor);
		
	}
	
	public ColourFrameDecorator(Component t, int x, int y, int width, int height, int thickness) {
		super(t, x, y, width, height);
        this.thickness = thickness;
	}
}