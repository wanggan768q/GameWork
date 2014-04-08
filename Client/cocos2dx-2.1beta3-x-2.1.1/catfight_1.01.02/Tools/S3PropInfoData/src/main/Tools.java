package main;

import java.io.DataOutputStream;
import java.io.IOException;

public class Tools 
{
	
	
	public static String getInfo(String sheetName,int row,int columns)
	{
		StringBuffer buffer = new StringBuffer();
		buffer.append(sheetName).append(":第").append(row).append("行，第").append(columns).append("列");
		return buffer.toString();
	}
	
	public static void write(DataOutputStream dos,byte[] b){
		try {
			dos.writeShort(b.length);
			dos.write(b);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	
	
	public static int readNonEmptyInt(String context,int defalut,String message)
	{
		int s = defalut;
		if(!checkEmpty(context))
		{
			try
			{
				s = Integer.parseInt(context);
			}
			catch (NumberFormatException e) 
			{
				MessageBox.Show(message+"应该是数字类型");
				e.printStackTrace();
			}
		}
		else
		{
			MessageBox.Show(message+"不能为空");
		}
		return s;
	}
	
	public static int readInt(String context,int defalut,String message)
	{
		int s = defalut;
		if(!checkEmpty(context))
		{
			try
			{
				s = Integer.parseInt(context);
			}
			catch (NumberFormatException e) 
			{
				MessageBox.Show(message+"应该是数字类型");
				e.printStackTrace();
			}
		}
		else
		{
			
		}
		return s;
	}
	
	public static long readNonEmptyLong(String context,long defalut,String message)
	{
		long s = defalut;
		
		if(!checkEmpty(context))
		{
			try
			{
				s = Long.parseLong(context);
			}
			catch (NumberFormatException e) 
			{
				MessageBox.Show(message+"应该是数字类型");
				e.printStackTrace();
			}
		}
		else
		{
			MessageBox.Show(message+"不能为空");
		}
		return s;
	}
	
	public static long readLong(String context,int defalut,String message)
	{
		long s = defalut;
		
		if(!checkEmpty(context))
		{
			try
			{
				s = Long.parseLong(context);
			}
			catch (NumberFormatException e) 
			{
				MessageBox.Show(message+"应该是数字类型");
				e.printStackTrace();
			}
		}
		else
		{
			MessageBox.Show(message+"不能为空");
		}
		return s;
	}
	
	public static float readNonEmptyFloat(String context,int defalut,String message)
	{
		float s = defalut;
		
		if(!checkEmpty(context))
		{
			try
			{
				s = Float.parseFloat(context);
			}
			catch (NumberFormatException e) 
			{
				MessageBox.Show(message+"应该是数字类型");
				e.printStackTrace();
			}
		}
		else
		{
			MessageBox.Show(message+"不能为空");
		}
		return s;
	}
	
	public static float readFloat(String context,int defalut,String message)
	{
		float s = defalut;
		
		if(!checkEmpty(context))
		{
			try
			{
				s = Float.parseFloat(context);
			}
			catch (NumberFormatException e) 
			{
				MessageBox.Show(message+"应该是数字类型");
				e.printStackTrace();
			}
		}
		else
		{
			 
		}
		return s;
	}
	
	public static String readNonEmptyString(String context,String message)
	{
		if(!checkEmpty(context))
		{
			
		}
		else
		{
			MessageBox.Show(message+"不能为空");
		}	
		return context;
	}
	
	
	
	public static boolean checkEmpty(String context)
	{
		if(context == null || context.equals(""))
		{
			return true;
		}
		return false;
	}
	
	 
}
