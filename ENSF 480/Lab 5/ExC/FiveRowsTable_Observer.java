/*
File name: FiveRowsTable_Observer.java
Lab 5 Exercise C
Oct 26th 2024
By: Gerardo Garcia de Leon
*/

import java.util.ArrayList;

public class FiveRowsTable_Observer implements Observer {
    private DoubleArrayListSubject subject;

    public FiveRowsTable_Observer(DoubleArrayListSubject subject) {
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
        if (data.isEmpty()) {
            System.out.println("Empty List ...");
            return;
        }
        
        System.out.println("Notification to Five-Rows Table Observer: Data Changed:");
        int numRows = 5;
        int numColumns = (int) Math.ceil((double) data.size() / numRows);

        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numColumns; j++) {
                int index = i + j * numRows;
                if (index < data.size()) {
                    System.out.print(data.get(index) + " ");
                }
            }
            System.out.println();
        }
    }
}