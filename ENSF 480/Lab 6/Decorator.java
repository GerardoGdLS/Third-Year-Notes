/*
 * File name: Decorator.java
 * Lab 6 Exercise A
 * Nov 1st 2024
 * By: Gerardo Garcia de Leon
 */

import java.awt.Graphics;

abstract class Decorator implements Component{
	Component cmp;
	int x, y, width;
	public
		int height; 
	
	public Decorator(Component cmp, int x, int y, int width, int height) {
        this.cmp = cmp;
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
    }

    @Override
    public void draw(Graphics g) {
        cmp.draw(g);
    }
}
