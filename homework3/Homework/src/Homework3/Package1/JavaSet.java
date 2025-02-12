package Homework3.Package1;
import Homework3.Package2.JavaContainer;
import java.util.Objects;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Iterator;
public class JavaSet<T> implements JavaContainer<T> {
    private int used;//the number of elements
    private int size;//the size of array
    private int index;//this is iterator
    private T[] array;//keeps the array
    public JavaSet() {
    	this(5);
    }//this is a Constructor
    public JavaSet(int _size) {
        if (_size < 0) {
            throw new ArithmeticException("Size cannot be smaller than zero");
        }
        size = _size;
       //@SuppressWarnings("unchecked")
          array = (T[]) new Object[size];
        index = 0;
        used=0;
    }
    public int Size() {
        return used;
    }//returns number of elements
    //Override
    public void addElements(T value) {  // Match the method name in the interface
        int flag = 0;
        if (used+1< size) {
        	for (Object current : array) {
        	    if (current != null && current.equals(value)) {
        	        flag = 1;
        	        break;
        	    }//controls there is element or not
        	}

            if (flag == 0) {
                array[used] = value;
                used++;
            } else {
                throw new ArithmeticException("The value has already been added");
            }
        } else {
            // Resize the array and copy elements to the new array
              @SuppressWarnings("unchecked")
        	 T[] newArray = (T[]) new Object[size*2];//makes new array and assign old array to new array 
           System.arraycopy(array, 0, newArray, 0, size);
            array = newArray;
            size = size * 2;
            addElements(value); // Recursive call after resizing the array
        }
    }
    //override
    public void removeElements(T value) {
        int flag = 0;
         // Check if the value exists in the array
        for (Object current : array) {
            if (current==value) {
                flag = 1;
                break;
            }//controls there is element or not
        }
        if (flag == 0) {
            throw new ArithmeticException("There is no value to remove in the set");
        } else {
            // Create a new array without the element to be removed
            @SuppressWarnings("unchecked")
        	 T[] newArray = (T[]) new Object[size-1];
            int newArrayIndex = 0;

            for (int i = 0; i < size; i++) {
                if (!(array[i]==value)) {
                    newArray[newArrayIndex] = array[i];
                    newArrayIndex++;
                }
            }
            // Update the array and size
            array = newArray;
            size = size - 1;
            if(index==used) {
            	index--;
            }
            used--;
        }
    }
    public Iterator<T> getIterator() {//this is for getiterator
     class Iterator implements java.util.Iterator<T> {
        public boolean hasNext() {
            int temp = index + 1;

            if (temp < size) {
                return array[temp] != null;
            } else {
                throw new ArithmeticException("You are at the last element");
            }
        }

        public T next() {
            if (hasNext()) {//if there is next return index number
                index++;//increases iterator
                return (T) array[index]; // Explicit cast to T
            } else {
                throw new ArithmeticException("There is no element to show.");
            }
        }
    }
    return new Iterator();
    }//return the iterator object
    

public String toString() {
    if (used == 0) {
        return "the array is empty";
    }

    String sentence = array[0].toString(); // Convert the first element to String
    for (int i = 1; i < used; i++) {
        sentence += ", " + array[i].toString(); // Convert each element to String
    }

    return String.format("the elements of the Set are [%s]", sentence);
}

public boolean equals(JavaSet<T> other) {
    if (this == other) {
        return true;  // Aynı referansa sahipler, bu yüzden eşittirler
    }
    if (size != other.size) {
        return false; // Boyutları farklı, bu yüzden eşit değiller
    }
    
    // Elemanlar arasında eşitlik kontrolü
    for (var i = 0; i < used; i++) {
        boolean found = false;
        for (var j = 0; j < other.used; j++) {
            // T tipindeki elemanlar için cast ekleniyor
            if (Objects.equals((T) array[i], other.array[j])) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false; //they are not equal
        }
    }
    
    return true; // Tüm elemanlar eşleşti, bu yüzden eşittirler
}
public void writeToFile() {//writes arrays to the file
    try {
        File file1 = new File("setfile.txt");
        FileWriter fwriter = new FileWriter(file1,true);
        BufferedWriter bwriter = new BufferedWriter(fwriter);

        bwriter.write("The elements of the Sets are: ");
        boolean firstElement = true;
        for (Object current : array) {
            if (current != null) {
                if (!firstElement) {
                    bwriter.write(", ");
                } else {
                    firstElement = false;
                }
                bwriter.write(current.toString());
            }
        }

        bwriter.newLine();
        bwriter.close();
    } catch (IOException e) {
        System.err.println("Error writing to file: " + e.getMessage());
    }
}
}
