package Homework3.Package1;
import Homework3.Package2.JavaContainer;
import java.util.Iterator;
import java.util.Scanner;
//including necessary operations
//ı tried my code and ı added user part you to try
public class JavaDriver {
    public static void main(String[] args) {
      
    	try {
    	JavaSet<Integer> object1 = new JavaSet<>(5);
    	JavaSet<Integer> object3 = new JavaSet<>(5);
        object1.addElements(1); // Use addElements instead of addElement
        object1.addElements(3); // Use addElements instead of addElement
        object1.addElements(8); // Use addElements instead of addElement
        object1.addElements(5); // Use addElements instead of addElement
        object1.addElements(4); // Use addElements instead of addElement
        object1.writeToFile();
        System.out.printf("%s",object1.toString());
        System.out.println(object1.Size());
        JavaVector<String> object2 = new JavaVector<>();
        object2.addElements("Ahmet"); // Use addElements instead of addElement
        object2.addElements("mehmet"); // Use addElements instead of addElement
        object2.addElements("Selin"); // Use addElements instead of addElement
        object2.addElements("zafer"); // Use addElements instead of addElement
        object2.addElements("mahmut"); // Use addElements instead of addElement
        object2.addElements("Selin"); // Use addElements instead of addElement
        object2.addElements("mahmut"); // Use addElements instead of addElement
        object2.writeToFile();
        System.out.printf("%s\n",object2.toString());
        object2.removeElements("mahmut");
        object2.writeToFile();
        System.out.printf("%s",object2.toString());
        System.out.println(object2.Size());
        Iterator<Integer> a = object1.getIterator();
        while (a.hasNext()) {
            System.out.println(a.next());
        }
       System.out.println("You are in the last element"); 
       System.out.printf("%s\n",object2.toString());
       object1.addElements(17); // Use addElements instead of addElement
       object1.writeToFile();
       object3.addElements(5); // Use addElements instead of addElement
       object3.addElements(4); // Use addElements instead of addElement
       object3.writeToFile();
       System.out.printf("%s\n",object3.toString());
      //****************USER PART*********************************//
       Scanner input = new Scanner(System.in);
       int number;
       do {
    	    System.out.println("How many elements will you enter: ");

    	    while (!input.hasNextInt()) {
    	        System.out.println("Invalid input! Please enter a valid integer.");
    	        input.next(); // Consume the invalid input
    	    }
    	    number = input.nextInt();
    	    if (number <= 0) {
    	        System.out.println("Invalid size! Please enter a positive integer.");
    	    }
    	} while (number <= 0);

       double value;

       JavaSet<Double> userObject = new JavaSet<>(number);
       for (int i = 0; i < number; i++) {
           System.out.printf("Please enter your %d. element: ", i + 1);

           while (!input.hasNextDouble()) {
               System.out.println("Invalid input! Please enter a valid double value.");
               input.next();
           }
           value = input.nextDouble();
           userObject.addElements(value);
       }
     System.out.println("You entered: ");
     System.out.printf("%s",userObject.toString());
     
       
       
    	}
    	catch(ArithmeticException e){
    		  System.out.println("Error occured. "+e.getMessage());
    	}
       
    }
}
