/*
File name: InsertionSorter.java
Lab 5 Exercise A
Oct 24th 2024
By: Gerardo Garcia de Leon
*/

import java.util.ArrayList;

class InsertionSorter<E extends Number & Comparable<E>> implements Sorter<E> {
    @Override
    public void sort(ArrayList<Item<E>> items) {
        for (int i = 1; i < items.size(); i++) {
            Item<E> key = items.get(i);
            int j = i - 1;

            while (j >= 0 && items.get(j).getItem().compareTo(key.getItem()) > 0) {
                items.set(j + 1, items.get(j));
                j--;
            }
            items.set(j + 1, key);
        }
    }
}