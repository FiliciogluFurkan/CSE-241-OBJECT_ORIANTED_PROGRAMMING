package Homework3.Package1;
import Homework3.Package2.JavaContainer;
import java.util.Objects;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Iterator;
//almost the same with set.The differences is adds same element 
//also removes first element if there exist second one
public class JavaVector<T> implements JavaContainer<T> {
	private int index;
	private int size;
	private int used;
	private T[] array;
	public JavaVector() {
		this(5);
	}
	public JavaVector(int _size) {
	size=_size;
	used=0;
	index=0;
	//@SuppressWarnings("unchecked")
	 array = (T[]) new Object[size];
	}
	public int Size() {
		return used;
	}
	
	public void addElements(T value) {
		if(used+1<size) {
			array[used]=value;
			used++;
		}else {
		@SuppressWarnings("unchecked")
			 T[] newArray = (T[]) new Object[size*2];
		   for(var i=0;i<size;i++) {
			   newArray[i]=array[i];
		   }
		   size=size*2;
			array=newArray;	
			addElements(value);	
		}
	}
	public void removeElements(T value){
	
	int temp=0,flag=0;	
	for(var i=0;i<used;i++) {
		if(array[i]==value) {
			flag=1;
			temp=i;
			break;
		}
	}
	if(flag==0)
		throw new ArithmeticException("Element cannot be founded in vector");
	else {
	@SuppressWarnings("unchecked")
	 T[] newArray = (T[]) new Object[size-1];
	for(int i=0,j=0;i<size-1;i++) {
	if((i)!=temp) {
		newArray[j++]=array[i];
	}
	}
	 size=size-1;
	 writeToFile();
	 if(index+1==used) {
     	index--;
     }
	used--;
	array=newArray;	
	}		
	}
	
	  public Iterator<T> getIterator() {
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
	        if (hasNext()) {
	            index++;
	            return (T) array[index]; // Explicit cast to T
	        } else {
	            throw new ArithmeticException("There is no element to show.");
	        }
	    }
	}
	return new Iterator();
	  }
	
	public boolean equals(JavaVector<T> other)
	{
		int flag=0;
		if (this == other) {
		    return true;  // Same reference, so they are equal
		}

		for(var i=0;i<used;i++) {
		if(array[i]==other.array[i]) {
			flag=1;
		}else {
			flag=0;
			break;
		}
		}
		return (flag==0)?true:false;	
	} 

	
	public String toString() {
	    if (used == 0) {
	        return "the array is empty";
	    }

	    String sentence = array[0].toString(); // Convert the first element to String
	    for (int i = 1; i < used; i++) {
	        sentence += ", " + array[i].toString(); // Convert each element to String
	    }

	    return String.format("the elements of the Vector are [%s]", sentence);
	}
	  public void writeToFile() {
	        try {
	            if (array == null) {
	                return;
	            }

	            File file1 = new File("vectorfile.txt");
	            FileWriter fwriter = new FileWriter(file1, true);
	            BufferedWriter bwriter = new BufferedWriter(fwriter);

	            bwriter.write("The elements of the Vector are: ");
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

	            bwriter.newLine(); // Yeni satıra geç
	            bwriter.close();
	        } catch (IOException e) {
	            System.err.println("Error writing to file: " + e.getMessage());
	        }
	    }

}
