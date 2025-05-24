/*
File name: Subject.java
Lab 5 Exercise C
Oct 26th 2024
By: Gerardo Garcia de Leon
*/

interface Subject {
	void registerObserver(Observer o);
	void remove(Observer o);
	void notifyAllObservers();
}
