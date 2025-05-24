/*
 * File name: ColouredGlassDecorator.java
 * Lab 6 Exercise B
 * Nov 2nd 2024
 * By: Gerardo Garcia de Leon
 */

import java.awt.Color;
import java.awt.Graphics;

public class ColouredGlassDecorator extends Decorator{
	ColouredGlassDecorator(Component cmp, int x, int y, int width, int height){
		super(cmp, x, y, width, height);
	}
	
	@Override
	public void draw(Graphics g) {
		super.draw(g);
        g.setColor(new Color(0, 255, 0, 30)); 
        g.fillRect(x, y, width, height);
	}
}
