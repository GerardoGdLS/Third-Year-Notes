/*
File name: SelectionSorter.java
Lab 5 Exercise A
Oct 24th 2024
By: Gerardo Garcia de Leon
*/

import java.util.ArrayList;

class SelectionSorter<E extends Number & Comparable<E>> implements Sorter<E> {
    @Override
    public void sort(ArrayList<Item<E>> items) {
        int n = items.size();
        
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < n; j++) {
                if (items.get(j).getItem().compareTo(items.get(minIndex).getItem()) < 0) {
                    minIndex = j;
                }
            }
            
            Item<E> temp = items.get(minIndex);
            items.set(minIndex, items.get(i));
            items.set(i, temp);
        }
    }
}