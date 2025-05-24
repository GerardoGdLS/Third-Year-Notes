/*
 * File name: Text.java
 * Lab 6 Exercise A
 * Nov 1st 2024
 * By: Gerardo Garcia de Leon
 */

import java.awt.Color;
import java.awt.Graphics;

public class Text implements Component{
		int x, y;
		String text;
	
		@Override
	    public void draw(Graphics g) {
	        g.setColor(Color.GREEN);
	        g.drawString(text, x, y);
	    }
		
		Text(String txt, int x, int y){
			this.text = txt;
			this.x = x;
			this.y = y;
		}
}