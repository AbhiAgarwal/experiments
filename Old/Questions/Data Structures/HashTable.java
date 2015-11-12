import java.util.*;
import java.io.*;

/*
Demonstrates Hash Tables, Initializing & then Using Functions:
- Put, Values, isEmpty, etc.
Just for remembering / notes purposes
*/

public class HashTable
{
	public static HashMap<Integer, Student> Hash(Student[] students){
		HashMap<Integer, Student> map = new HashMap<Integer, Student>();
		for (Student s : students) map.put(s.getID(), s);
		return map;
	}
	public static void main(String[] args){
		// Creating new Instances of Students
		HashMap map = new HashMap();
		System.out.println("Map is Empty? " + map.isEmpty());
    	Student[] student = new Student[3];
		student[0] = new Student(0);
    	student[1] = new Student(1);
    	student[2] = new Student(2);
    	map = Hash(student);
    	System.out.println("Values in Map: " + map.values()); // Values
    	System.out.println("Get student[0]? " + map.get(0));
    	//System.out.print();
  	}
}