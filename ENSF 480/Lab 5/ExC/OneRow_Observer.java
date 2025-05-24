/*
File name: OneRow_Observer.java
Lab 5 Exercise C
Oct 26th 2024
By: Gerardo Garcia de Leon
*/

import java.util.ArrayList;

public class OneRow_Observer implements Observer {
    private DoubleArrayListSubject subject;

    public OneRow_Observer(DoubleArrayListSubject subject) {
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
        System.out.println("Notification to One-Row Table Observer: Data Changed: ");
        for (Double value : data) {
            System.out.print(value + " ");
        }
        System.out.println();
    }
}
