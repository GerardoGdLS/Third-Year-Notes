/*
File name: BubbleSorter.java
Lab 5 Exercise A
Oct 24th 2024
By: Gerardo Garcia de Leon
*/

import java.util.ArrayList;

class BubbleSorter<E extends Number & Comparable<E>> implements Sorter<E> {
    @Override
    public void sort(ArrayList<Item<E>> items) {
        for (int i = 0; i < items.size() - 1; i++) {
            for (int j = 0; j < items.size() - i - 1; j++) {
                if (items.get(j).getItem().compareTo(items.get(j + 1).getItem()) > 0) {
                    Item<E> temp = items.get(j);
                    items.set(j, items.get(j + 1));
                    items.set(j + 1, temp);
                }
            }
        }
    }
}