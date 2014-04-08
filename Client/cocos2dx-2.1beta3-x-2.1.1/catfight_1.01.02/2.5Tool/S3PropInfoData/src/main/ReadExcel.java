package main;

import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.util.Vector;

import jxl.Cell;
import jxl.Sheet;
import jxl.Workbook;
import message.S3BuyGold.BuyGold;
import message.S3PropInfo.PropInfo;
import message.S3PropInfo.PropInfo.PropType;
import message.S3PropInfoData.PropInfoData;

public class ReadExcel 
{
	
	Vector<PropInfo> propInfoList = new Vector<PropInfo>();
	Vector<PropInfo> bufferInfoList = new Vector<PropInfo>();
	Vector<PropInfo> effectInfoList = new Vector<PropInfo>();
	Vector<PropInfo> lockInfoList = new Vector<PropInfo>();
	Vector<BuyGold> buyGoldList = new Vector<BuyGold>();
	Vector<PropInfo> headList = new Vector<PropInfo>();
	
	
	PropInfoData.Builder data = PropInfoData.newBuilder();
	
	public void OpenExcel(String fileName)
	{
		InputStream is;
		try 
		{
			is = new FileInputStream("ExcelData/" + fileName);
				
			Workbook work = Workbook.getWorkbook(is);
			 
			Sheet[] sheets = work.getSheets();
			
			for(int i =0; i < sheets.length; i++)
			{
				switch(i)
				{
				case 0:
					readPropInfoList(sheets[i]);
					break;
				case 1:
					readBufferInfoList(sheets[i]);
					break;
				case 2:
					readEffectInfoList(sheets[i]);
					break;
				case 3:
					readLockInfo(sheets[i]);
					break;
				case 4:
					readBuyGoldList(sheets[i]);
					break;
				case 5:
					readHeadList(sheets[i]);
					break;
				}
			}
			
			data.addAllManualPropInfoList(propInfoList);
			data.addAllBufferPropInfoList(bufferInfoList);
			data.addAllEffectPropInfoList(effectInfoList);
			data.addAllLockPropInfoList(lockInfoList);
			data.addAllBuyGoldList(buyGoldList);
			data.addAllHeadList(headList);
			
			// 关闭
			this.Write(data.build());
			work.close();
			is.close();
			 
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	
	
	public void readBuyGoldList(Sheet sheet)
	{
		String sheetName = sheet.getName();
		System.out.println("处理:  " + sheetName);
		if (sheet != null) 
		{
			// 获取表格总列数
			int rsColumns = sheet.getColumns();
			// 获取表格总行数
			int rsRows = sheet.getRows();
			
			BuyGold.Builder buyGold = BuyGold.newBuilder();
			for(int i=1; i < rsRows; i++)
			{
				int index =0;
				
				Cell cell[]=sheet.getRow(i);
				
				if(cell!= null && cell.length!=0)
				{
					int id = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					 
					String name = Tools.readNonEmptyString(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					String localName = Tools.readNonEmptyString(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					String describ = Tools.readNonEmptyString(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					int goldNumber = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					int money = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					 
					
					buyGold.setId(id);
					buyGold.setName(name);
					buyGold.setDescrib(describ);
					
					buyGold.setGoldNumber(goldNumber);
					buyGold.setMoney(money);
					buyGold.setLocalName(localName);
				 
					buyGoldList.addElement(buyGold.build());
				}
			}
		}
	}
	
	public void readLockInfo(Sheet sheet)
	{
		String sheetName = sheet.getName();
		System.out.println("处理:  " + sheetName);
		if (sheet != null) 
		{
			// 获取表格总列数
			int rsColumns = sheet.getColumns();
			// 获取表格总行数
			int rsRows = sheet.getRows();
			
			PropInfo.Builder propInfo = PropInfo.newBuilder();
			for(int i=1; i < rsRows; i++)
			{
				int index =0;
				
				Cell cell[]=sheet.getRow(i);
				
				if(cell!= null && cell.length!=0)
				{
					int id = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					 
					String name = Tools.readNonEmptyString(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					String describ = Tools.readNonEmptyString(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					int unLockLevel = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					int unLockgold = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					 
					
					propInfo.setId(id);
					propInfo.setName(name);
					propInfo.setDescrib(describ);
				 
					propInfo.setUnlockLevel(unLockLevel);
					 
					propInfo.setUnlockGold(unLockgold);
				 
					lockInfoList.addElement(propInfo.build());
				}
			}
		}
	}
	
	
	public void readBufferInfoList(Sheet sheet)
	{
		String sheetName = sheet.getName();
		System.out.println("处理:  " + sheetName);
		if (sheet != null) 
		{
			// 获取表格总列数
			int rsColumns = sheet.getColumns();
			// 获取表格总行数
			int rsRows = sheet.getRows();
			
			PropInfo.Builder propInfo = PropInfo.newBuilder();
			for(int i=1; i < rsRows; i++)
			{
				int index =0;
				
				Cell cell[]=sheet.getRow(i);
				
				if(cell!= null && cell.length!=0)
				{
					int id = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					PropInfo.BufferPropType bufferType =  getBufferPropType(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					String name = Tools.readNonEmptyString(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					String localName = Tools.readNonEmptyString(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					String describ = Tools.readNonEmptyString(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					int level = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					int unLockLevel = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					int useNumber = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					PropInfo.ActionObjectType actionType = getActionObjectType(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					int gold = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					int unlockGold = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					float ctTime = Tools.readNonEmptyFloat(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					float duration = Tools.readNonEmptyFloat(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					
					propInfo.setId(id);
					propInfo.setName(name);
					propInfo.setLocalname(localName);
					propInfo.setDescrib(describ);
					propInfo.setPropType(PropType.BufferProp);
					propInfo.setBufferPropType(bufferType);
					propInfo.setLevel(level);
					propInfo.setUnlockLevel(unLockLevel);
					propInfo.setUseNumber(useNumber);
					propInfo.setActionType(actionType);
					propInfo.setGold(gold);
					propInfo.setUnlockGold(unlockGold);
					propInfo.setCtTime(ctTime);
					propInfo.setDuration(duration);
					bufferInfoList.addElement(propInfo.build());
				}
			}
		}
	}
	
	public void readEffectInfoList(Sheet sheet)
	{
		String sheetName = sheet.getName();
		System.out.println("处理:  " + sheetName);
		if (sheet != null) 
		{
			// 获取表格总列数
			int rsColumns = sheet.getColumns();
			// 获取表格总行数
			int rsRows = sheet.getRows();
			
			PropInfo.Builder propInfo = PropInfo.newBuilder();
			for(int i=1; i < rsRows; i++)
			{
				int index =0;
				
				Cell cell[]=sheet.getRow(i);
				
				if(cell!= null && cell.length!=0)
				{
					int id = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					PropInfo.EffectPropType effectType =  this.getEffectPropType(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					
					String name = Tools.readNonEmptyString(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					String localName = Tools.readNonEmptyString(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					String describ = Tools.readNonEmptyString(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					int level = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					int unLockLevel = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					int useNumber = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					PropInfo.ActionObjectType actionType = getActionObjectType(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					int gold = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					int unlockGold = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					float ctTime = Tools.readNonEmptyFloat(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					float duration = Tools.readNonEmptyFloat(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					
					propInfo.setId(id);
					propInfo.setName(name);
					propInfo.setLocalname(localName);
					propInfo.setDescrib(describ);
					propInfo.setPropType(PropType.EffectProp);
					propInfo.setEffectPropType(effectType);
					propInfo.setLevel(level);
					propInfo.setUnlockLevel(unLockLevel);
					propInfo.setUseNumber(useNumber);
					propInfo.setActionType(actionType);
					propInfo.setGold(gold);
					propInfo.setUnlockGold(unlockGold);
					propInfo.setCtTime(ctTime);
					propInfo.setDuration(duration);
					effectInfoList.addElement(propInfo.build());
				}
			}
		}
	}

	
	public void readPropInfoList(Sheet sheet)
	{
		String sheetName = sheet.getName();
		System.out.println("处理:  " + sheetName);
		if (sheet != null) 
		{
			// 获取表格总列数
			int rsColumns = sheet.getColumns();
			// 获取表格总行数
			int rsRows = sheet.getRows();
			
			PropInfo.Builder propInfo = PropInfo.newBuilder();
			for(int i=1; i < rsRows; i++)
			{
				int index =0;
				
				Cell cell[]=sheet.getRow(i);
				
				if(cell!= null && cell.length!=0)
				{
					int id = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					PropInfo.ManualPropType manualType =  getManualPropType(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					String name = Tools.readNonEmptyString(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					String localName = Tools.readNonEmptyString(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					String describ = Tools.readNonEmptyString(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					int level = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					int unLockLevel = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					int useNumber = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					PropInfo.ActionObjectType actionType = getActionObjectType(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					int gold = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					int unlockGold = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					float ctTime = Tools.readNonEmptyFloat(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					
					propInfo.setId(id);
					propInfo.setName(name);
					propInfo.setLocalname(localName);
					propInfo.setDescrib(describ);
					propInfo.setPropType(PropType.ManualProp);
					propInfo.setManualPropType(manualType);
					propInfo.setLevel(level);
					propInfo.setUnlockLevel(unLockLevel);
					propInfo.setUseNumber(useNumber);
					propInfo.setActionType(actionType);
					propInfo.setGold(gold);
					propInfo.setUnlockGold(unlockGold);
					propInfo.setCtTime(ctTime);
					propInfoList.addElement(propInfo.build());
				}
			}
		}
	}
	
	public void readHeadList(Sheet sheet)
	{
		String sheetName = sheet.getName();
		System.out.println("处理:  " + sheetName);
		if (sheet != null) 
		{
			// 获取表格总列数
			int rsColumns = sheet.getColumns();
			// 获取表格总行数
			int rsRows = sheet.getRows();
			
			PropInfo.Builder propInfo = PropInfo.newBuilder();
			for(int i=1; i < rsRows; i++)
			{
				int index =0;
				
				Cell cell[]=sheet.getRow(i);
				
				if(cell!= null && cell.length!=0)
				{
					int id = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					String name = Tools.readNonEmptyString(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					String localName = Tools.readNonEmptyString(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					String describ = Tools.readNonEmptyString(cell[index].getContents(),Tools.getInfo(sheetName,i,index++));
					
					int gold = Tools.readNonEmptyInt(cell[index].getContents(), 0,Tools.getInfo(sheetName,i,index++));
					
					
					propInfo.setId(id);
					propInfo.setName(name);
					propInfo.setLocalname(localName);
					propInfo.setDescrib(describ);
					propInfo.setPropType(PropType.HeadProp);
					propInfo.setGold(gold);
					headList.addElement(propInfo.build());
				}
			}
		}
	}
	public PropInfo.BufferPropType getBufferPropType(String context,String message)
	{
		int d = Tools.readNonEmptyInt(context, 0,message);
		
		return PropInfo.BufferPropType.valueOf(d);
	}
	
	public PropInfo.EffectPropType getEffectPropType(String context,String message)
	{
		int d = Tools.readNonEmptyInt(context, 0,message);
		
		return PropInfo.EffectPropType.valueOf(d);
	}
	
	public PropInfo.ManualPropType getManualPropType(String context,String message)
	{
		int d = Tools.readNonEmptyInt(context, 0,message);
		
		return PropInfo.ManualPropType.valueOf(d);
	}
	
	public PropInfo.ActionObjectType getActionObjectType(String context,String message)
	{
		int d = Tools.readNonEmptyInt(context, 0, message);
		
		return PropInfo.ActionObjectType.valueOf(d);
	}
	
	
	public void Write(PropInfoData data) 
	{
		try {
			File file = new File("BinData/" + "PropInfo" + ".data");
			if (file.exists() == false) {
				file.createNewFile();
			}
			FileOutputStream fileOutStream = null;

			fileOutStream = new FileOutputStream(file);
			DataOutputStream dos = new DataOutputStream(fileOutStream);
			Tools.write(dos, data.toByteArray());
			
			dos.close();

			System.out.println("生成：" + "PropInfo" + ".data");
		}
		catch (Exception e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void Read()
	{
//		File file = new File("BinData/" + "PropInfo" + ".data");
//		
//		try 
//		{
//			FileInputStream fileInputStream = new FileInputStream(file);
//			
//			PropInfoData.Builder build = PropInfoData.newBuilder();
//			
//			try {
//				
//				 
//				PropInfoData propInfoData = PropInfoData.parseFrom(fileInputStream);
//			 
//				
//				int count = propInfoData.getBuyGoldListCount();
//				
//				for(int i =0; i<count; i++)
//				{
////					Method[] m = propInfoData.getBuyGoldList(i).getClass().getDeclaredMethods();
////					
////					String mm = m[0].getName();
////					
////					Field[] f = propInfoData.getBuyGoldList(i).getClass().getDeclaredFields();
////					
////					String ff = m[0].getName();
//					
//					System.out.println("id="+propInfoData.getBuyGoldList(i).getId()+",name="+propInfoData.getBuyGoldList(i).getName());
//				}
//			} catch (IOException e) {
//				// TODO Auto-generated catch block
//				e.printStackTrace();
//			}
//		} catch (FileNotFoundException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
		
		
	}

}
