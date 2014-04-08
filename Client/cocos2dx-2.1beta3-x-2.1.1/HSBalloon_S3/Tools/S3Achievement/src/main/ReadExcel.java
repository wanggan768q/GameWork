package main;

import java.io.DataOutputStream;


import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import message.S3AchievementInfo.AchievementInfo;

import jxl.Cell;
import jxl.Sheet;
import jxl.Workbook;
import jxl.read.biff.BiffException;

public class ReadExcel {

	AchievementInfo.Builder achievement = AchievementInfo.newBuilder();
	public void OpenExcel(String file)
	{
		
		 
		 InputStream is;
		 try {
			is = new FileInputStream("ExcelData/"+file);
			
		    Workbook workBook = Workbook.getWorkbook(is);
		    
		    Sheet sheets[] = workBook.getSheets();
		    
		    readAchievement(sheets[0]);
		    
		 // 关闭
		 this.Write(achievement.build());
		 workBook.close();
		 is.close();
			 
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		 catch (BiffException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void Write(AchievementInfo data) 
	{
		try {
			File file = new File("BinData/" + "Achievement" + ".data");
			if (file.exists() == false) {
				file.createNewFile();
			}
			FileOutputStream fileOutStream = null;

			fileOutStream = new FileOutputStream(file);
			DataOutputStream dos = new DataOutputStream(fileOutStream);
			Tools.write(dos, data.toByteArray());
//			dos.writeUTF("中国");
			//write(dos,data);
			
			dos.close();

			System.out.println("生成：" + "Achievement" + ".data");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	
	public void readAchievement(Sheet sheet)
	{
		String sheetName = sheet.getName();
		System.out.println("sheetName:"+sheetName);
		
		int column = sheet.getRows();
		int row = sheet.getRows();
		
		
		for(int i =1; i < row; i++)
		{
			int index = 0;
			Cell cell[] = sheet.getRow(i);
			AchievementInfo.AchievementItem.Builder item = AchievementInfo.AchievementItem.newBuilder();
			if(cell!= null && cell.length!=0)
			{
				int id = Tools.readNonEmptyInt(cell[index].getContents(), 0, Tools.getInfo(sheetName, row, index++));
				String name = Tools.readNonEmptyString(cell[index].getContents(), Tools.getInfo(sheetName, row, index++));
				String describ = Tools.readNonEmptyString(cell[index].getContents(), Tools.getInfo(sheetName, row, index++));
				
				item.setId(id);
				item.setName(name);
				item.setDescrib(describ);
				achievement.addAchievementArray(item);
			}
		}
		
		
	}

}
