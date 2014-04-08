
public class JavaTest {

	public native static int sum(int a,int b);
	
	public static void main(String[] args) {
		System.out.println("Sum: = " + sum(3,2));

	}

}
