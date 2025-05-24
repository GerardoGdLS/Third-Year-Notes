/*
File name: ThreeColumnTable_Observer.java
Lab 5 Exercise C
Oct 26th 2024
By: Gerardo Garcia de Leon
*/

import java.util.ArrayList;

public class ThreeColumnTable_Observer implements Observer {
    private DoubleArrayListSubject subject;

    public ThreeColumnTable_Observer(DoubleArrayListSubject subject) {
        this.subject = subject;
        subject.registerObserver(this);
        update(subject.data);
        System.out.println();
    }

    @Override
    public void update(ArrayList<Double> data) {
        display(data);
    }

    public void display(ArrayList<Double> data) {
        System.out.println("Notification to Three-Column Table Observer: Data Changed: ");
        for (int i = 0; i < data.size(); i++) {
            System.out.print(data.get(i) + " ");
            if ((i + 1) % 3 == 0) {
                System.out.println(); 
            }
        }
        System.out.println();
    }
}
