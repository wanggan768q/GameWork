package main;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ReadExcel readExcel = new ReadExcel();
		readExcel.OpenExcel("S3Achievement.xls");
		
		long s = System.currentTimeMillis();
		int a = 1;
	}

}
