package main;

import java.io.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import message.Figure.FigureData;
import message.Figure.FigureData.FigureBase;
import message.Figure.FigureData.FigureLevelTable;
import message.Figure.FigureData.FigureProperty;
import jxl.*;

public class ReadExcel {

	Vector<FigureBase.Builder> vBase = new Vector<FigureBase.Builder>();
	Map<Integer,Vector<FigureLevelTable>> mapTable = new HashMap<Integer,Vector<FigureLevelTable>>();
	Map<Integer,FigureProperty> mapProperty = new HashMap<Integer,FigureProperty>();
	
	
	FigureData.Builder figureDataBuid = FigureData.newBuilder();

	boolean isSuccess = true;

	public void OpenExcel(String fileName) {
		try {
			InputStream is = new FileInputStream("ExcelData/" + fileName);
			Workbook work = Workbook.getWorkbook(is);
			Sheet[] sheets = work.getSheets();

			this.handleFigureBase(sheets[0]);
			this.handleFigureLevelTable(sheets[1]);
			this.handleFigureProperty(sheets[2]);
			
			this.handle();

			work.close();
			is.close();

			Write(figureDataBuid.build());

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void handleFigureBase(Sheet sheet) {
		String sheetName = sheet.getName();
		System.out.println("处理: " + sheetName);
		if (sheet != null) {
			int rsColumns = sheet.getColumns();
			
			int rsRows = sheet.getRows();
			
			for (int i = 1; i < rsRows; i++) {
				Cell[] c = sheet.getRow(i);
				int index = 0;
				
				FigureBase.Builder base = FigureBase.newBuilder();
				
				//id
				String s = c[index++].getContents();
				base.setId(Integer.valueOf(s));
				
				//name
				s = c[index++].getContents();				
				base.setName(s);
				
				//describe
				s = c[index++].getContents();
				s = s.replace("#", "\n");	
				System.out.println(s + "\n");
				base.setDescribe(s);
				
				//buyDescribe
				s = c[index++].getContents();
				s = s.replace("#", "\n");	
				System.out.println(s + "\n");
				base.setBuyDescribe(s);
				
				//price(价格)
				s = c[index++].getContents();
				base.setPrice(Integer.valueOf(s));
				
				vBase.add(base);
			}
		}
	}
	
	private void handleFigureLevelTable(Sheet sheet) {
		String sheetName = sheet.getName();
		System.out.println("处理: " + sheetName);
		if (sheet != null) {
			int rsColumns = sheet.getColumns();
			
			int rsRows = sheet.getRows();
			
			for (int i = 1; i < rsRows; i++) {
				Cell[] c = sheet.getRow(i);
				int index = 0;
				
				FigureLevelTable.Builder table = FigureLevelTable.newBuilder();
				
				//id
				String s = c[index++].getContents();
				int id = Integer.valueOf(s);
				
				//level
				s = c[index++].getContents();
				table.setLevel(Integer.valueOf(s));
				
				//nextLevelGold
				s = c[index++].getContents();
				table.setNextLevelGold(Integer.valueOf(s));
				
				//property_0
				s = c[index++].getContents();
				table.setProperty0(Integer.valueOf(s));
				
				//property_1
				s = c[index++].getContents();
				table.setProperty1(Integer.valueOf(s));
				
				//property_2
				s = c[index++].getContents();
				table.setProperty2(Integer.valueOf(s));
				
				Vector<FigureLevelTable> v = mapTable.get(id);
				if(v == null)
				{
					v = new Vector<FigureLevelTable>();
					v.add(table.build());
					mapTable.put(id, v);
				}else{
					v.add(table.build());
				}
			}
		}
	}
	
	private void handleFigureProperty(Sheet sheet) {
		String sheetName = sheet.getName();
		System.out.println("处理: " + sheetName);
		if (sheet != null) {
			int rsColumns = sheet.getColumns();
			
			int rsRows = sheet.getRows();
			
			for (int i = 1; i < rsRows; i++) {
				Cell[] c = sheet.getRow(i);
				int index = 0;
				
				FigureProperty.Builder p = FigureProperty.newBuilder();
				
				//id
				String s = c[index++].getContents();
				int id = Integer.valueOf(s);
				
				//X_连线距离
				s = c[index++].getContents();
				p.setXLianXianJuLi(Float.valueOf(s));
				s = c[index++].getContents();
				p.setYLianXianJuLi(Float.valueOf(s));
				
				//X_掉落时间间隔
				s = c[index++].getContents();
				p.setXDiaoLuoShiJianJianGe(Float.valueOf(s));
				s = c[index++].getContents();
				p.setYDiaoLuoShiJianJianGe(Float.valueOf(s));
				
				//X_石化时间
				s = c[index++].getContents();
				p.setXShiHuaShiJian(Float.valueOf(s));
				s = c[index++].getContents();
				p.setYShiHuaShiJian(Float.valueOf(s));
				
				//X_弹性
				s = c[index++].getContents();
				p.setXTanXing(Float.valueOf(s));
				s = c[index++].getContents();
				p.setYTanXing(Float.valueOf(s));

				//X_掉落数量
				s = c[index++].getContents();
				p.setXDiaoLuoShuLiang(Float.valueOf(s));
				s = c[index++].getContents();
				p.setYDiaoLuoShuLiang(Float.valueOf(s));
				
				//X_石化球数量
				s = c[index++].getContents();
				p.setXShiHuaQiuShuLiang(Float.valueOf(s));
				s = c[index++].getContents();
				p.setYShiHuaQiuShuLiang(Float.valueOf(s));
				
				mapProperty.put(id, p.build());
			}
		}
	}

	private void handle()
	{
		for(FigureBase.Builder base : vBase)
		{
			Vector<FigureLevelTable> vTable = mapTable.get(base.getId());
			FigureProperty p = mapProperty.get(base.getId());
			if(vTable != null)
			{
				for(FigureLevelTable t : vTable)
				{
					base.addLevelTableList(t);
				}
			}
			if(p != null)
			{
				base.setProperty(p);
			}
			figureDataBuid.addFigureList(base.build());
		}
	}
	
	public void Write(FigureData data) {
		try {
			File file = new File("BinData/" + "FigureData" + ".data");
			if (file.exists() == false) {
				file.createNewFile();
			}
			FileOutputStream fileOutStream = null;

			fileOutStream = new FileOutputStream(file);
			DataOutputStream dos = new DataOutputStream(fileOutStream);
			Tools.write(dos, data.toByteArray());
			dos.close();

			System.out.println("生成" + "FigureData" + ".data");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
