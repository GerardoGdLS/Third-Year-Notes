/*
 * File name: DemoDecoratorPattern.java
 * Lab 6 Exercise A
 * Nov 1st 2024
 * By: Gerardo Garcia de Leon
 */

import java.awt.Font;
import java.awt.Graphics;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class DemoDecoratorPattern extends JPanel {
	Component t;
	
    public DemoDecoratorPattern(){
   	 t = new Text ("Hello World", 60, 80);
   	 
   }
	
    public void paintComponent(Graphics g){
    	
    	int fontSize = 10;
    	g.setFont(new Font("TimesRoman", Font.PLAIN, fontSize));
    	// GlassFrameDecorator info: x = 25, y = 25, width = 110, and height = 110
    	t = new ColouredGlassDecorator(new ColourFrameDecorator(
    	new BorderDecorator(t, 30, 30, 99, 99), 25, 25, 110, 110, 10), 25, 25,
    	110, 110);
    	t.draw(g);
    }
	
	public static void main(String[] args) {	
        DemoDecoratorPattern panel = new DemoDecoratorPattern();
        JFrame frame = new JFrame("Learning Decorator Pattern");
        frame.getContentPane().add(panel);
        frame.setSize(400,400);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
	}
}