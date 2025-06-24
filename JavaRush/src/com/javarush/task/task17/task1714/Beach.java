package com.javarush.task.task17.task1714;

/* 
Comparable
*/

public class Beach implements Comparable<Beach> {
    private String name;      //название
    private float distance;   //расстояние
    private int quality;    //качество

    public Beach(String name, float distance, int quality) {
        this.name = name;
        this.distance = distance;
        this.quality = quality;
    }

    public synchronized String getName() {
        return name;
    }

    public synchronized void setName(String name) {
        this.name = name;
    }

    public synchronized float getDistance() {
        return distance;
    }

    public synchronized void setDistance(float distance) {
        this.distance = distance;
    }

    public synchronized int getQuality() {
        return quality;
    }

    public synchronized void setQuality(int quality) {
        this.quality = quality;
    }

    public static void main(String[] args) {
        Beach beach = new Beach("mai", 10, 50);
        Beach beach1 = new Beach("Nai", 12, 99);

        int res = beach.compareTo(beach1);
        if (res > 0) System.out.println(beach.getName());
        else System.out.println(beach1.getName());

    }

    @Override
    public synchronized int compareTo(Beach obj) {
        int firstBeach = 0;
        int secondBeach = 0;

        float resDist = distance - obj.getDistance();

        if (resDist > 0) {
            secondBeach++;
        } else if (resDist < 0){
            firstBeach++;
        }

        int resQua = quality - obj.getQuality();

        if (resQua > 0) {
            firstBeach++;
        } else if (resQua < 0){
            secondBeach++;
        }

        return firstBeach - secondBeach;
    }
}
