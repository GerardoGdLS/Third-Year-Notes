/*
File name: MyVector.java
Lab 5 Exercise A
Oct 24th 2024
By: Gerardo Garcia de Leon
*/

import java.util.ArrayList;

class MyVector<E extends Number & Comparable<E>> {
    private ArrayList<Item<E>> storageM;
    private Sorter<E> sorter;

    // Constructor to initialize MyVector with a specified capacity
    public MyVector(int n) {
        storageM = new ArrayList<>(n);
    }

    // Constructor to initialize MyVector with an ArrayList
    public MyVector(ArrayList<Item<E>> arr) {
        storageM = new ArrayList<>(arr);
    }

    // Method to add an Item<E> to storageM
    public void add(Item<E> value) {
        storageM.add(value);
    }

    // Method to set the sorting strategy
    public void setSortStrategy(Sorter<E> s) {
        sorter = s;
    }

    // Method to perform sorting using the current strategy
    public void performSort() {
        if (sorter != null) {
            sorter.sort(storageM);
        } else {
            System.out.println("Sorter strategy not set.");
        }
    }

    // Method to display items in storageM
    public void display() {
        for (Item<E> item : storageM) {
            System.out.print(item.getItem() + " ");
        }
        System.out.println();
    }
}

