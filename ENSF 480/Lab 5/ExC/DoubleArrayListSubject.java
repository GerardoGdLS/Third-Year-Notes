/*
File name: DoubleArrayListSubject.java
Lab 5 Exercise C
Oct 26th 2024
By: Gerardo Garcia de Leon
*/

import java.util.ArrayList;

public class DoubleArrayListSubject implements Subject {
	public ArrayList<Double> data;
	public ArrayList<Observer> observers;
	
	public DoubleArrayListSubject() {
		data = new ArrayList<Double>(50);
		observers = new ArrayList<Observer>(50);
	}
	
	public void addData(Double val) {
		data.add(val);
		notifyAllObservers();
	}
	
	public void setData(int pos, Double val) {
		if (pos >= 0 && pos < data.size()) {
			data.set(pos, val);
			notifyAllObservers();
		} else {
			System.out.println("Index is out of bounds");
		}
	}
	
	public void populate(double[] arr) {
		for (Double r : arr) {
			data.add(r);
		}
		notifyAllObservers();
	}
	
	@Override
    public void registerObserver(Observer o) {
        if (!observers.contains(o)) {
            observers.add(o);
        }
    }

    @Override
    public void remove(Observer o) {
        observers.remove(o);
    }

    @Override
    public void notifyAllObservers() {
        for (Observer observer : observers) {
            observer.update(data);
        }
    }
    
    public void display() {
    	if(data.size() == 0) {
    		System.out.println("Empty List...");
    		return;
    	}
    	
    	for(Double val : data) {
    		System.out.println(val + " ");
    	}
    }
}
