package main;

import java.io.*;
import java.util.Vector;

import message.HSLanguageData.LanguageData;
import message.HSLanguageData.LanguageData.Language;
import message.HSLanguageData.LanguageData.Statement;

import jxl.*;

public class ReadExcel {

	LanguageData.Builder lauguageDataBuild = LanguageData.newBuilder();
	
	boolean isSuccess = true;

	public void OpenExcel(String fileName) {
		try {
			InputStream is = new FileInputStream("ExcelData/" + fileName);
			Workbook work = Workbook.getWorkbook(is);
			Sheet[] sheets = work.getSheets();
			
			for(int i=0;i<sheets.length;++i)
			{
				this.handle(sheets[i]);
			}
			work.close();
			is.close();
			
			Write(lauguageDataBuild.build());

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void handle(Sheet sheet) 
	{
		String sheetName = sheet.getName();
		System.out.println("处理: " + sheetName);
		if (sheet != null) {
			int rsColumns = sheet.getColumns();
			int rsRows = sheet.getRows();

			Cell[] countrys = sheet.getRow(1);
			
			for (int i = 2; i < rsRows; i++) {
				
				Language.Builder languageBuiild = Language.newBuilder();
				Cell[] c = sheet.getRow(i);
				
				int cIndex = 0;
				int countrysIndex = 1;
				
				if(c.length != 0)
				{
					String key = c[cIndex++].getContents();
					if(key.equals(""))
						continue;
					languageBuiild.setKey(key);
					
					for(int j=countrysIndex;j<countrys.length - 1;++j)
					{
						Statement.Builder statementBuild = Statement.newBuilder();
						String country = countrys[countrysIndex++].getContents();
						if(country.equals(""))
						{
							MessageBox.Show("国家不能为空");
							return;
						}
						statementBuild.setCountry(country);
						
						String v = c[cIndex++].getContents();
						statementBuild.setTalk(v);
						languageBuiild.addStatement(statementBuild.build());
					}
					lauguageDataBuild.addLanguage(languageBuiild.build());
				}				
			}
		}
	}

	public void Write(LanguageData data) {
		try {
			File file = new File("BinData/" + "LanguageData" + ".data");
			if (file.exists() == false) {
				file.createNewFile();
			}
			FileOutputStream fileOutStream = null;

			fileOutStream = new FileOutputStream(file);
			DataOutputStream dos = new DataOutputStream(fileOutStream);
			Tools.write(dos, data.toByteArray());			
			dos.close();

			System.out.println("生成" + "LanguageData" + ".data");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
