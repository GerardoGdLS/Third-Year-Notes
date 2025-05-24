/*
File name: Sorter.java
Lab 5 Exercise A
Oct 24th 2024
By: Gerardo Garcia de Leon
*/

interface Sorter<E extends Number & Comparable<E>> {
    void sort(ArrayList<Item<E>> items);
}
