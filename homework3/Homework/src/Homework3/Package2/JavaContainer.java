package Homework3.Package2;
import java.util.Iterator;
public interface JavaContainer<T> {
    void addElements(T value);
    void removeElements(T value);
    int Size();
    Iterator<T> getIterator();
    boolean equals(Object other);
}//interface of set and vector classes.I implemented in different classes
