package main;

import java.io.*;
import java.util.Vector;

import message.HSGameGuide;
import message.HSGameGuide.GameGuide;
import message.HSGameGuide.GameGuide.Guide;
import message.HSGameGuide.GameGuide.Guide.ModeType;
import message.HSGameGuide.GameGuide.Guide.Point;
import message.HSGameGuide.GameGuide.Guide.Rect;
import message.HSGameGuide.GameGuide.Guide.TouchType;
import jxl.*;

public class ReadExcel {

	GameGuide.Builder gameGuideDataBuild = GameGuide.newBuilder();

	boolean isSuccess = true;

	public void OpenExcel(String fileName) {
		try {
			InputStream is = new FileInputStream("ExcelData/" + fileName);
			Workbook work = Workbook.getWorkbook(is);
			Sheet[] sheets = work.getSheets();

			this.handle(sheets[0]);

			work.close();
			is.close();

			Write(gameGuideDataBuild.build());

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void handle(Sheet sheet) {
		String sheetName = sheet.getName();
		System.out.println("处理: " + sheetName);
		if (sheet != null) {
			int rsColumns = sheet.getColumns();
			
			int rsRows = sheet.getRows();
			
			for (int i = 1; i < rsRows; i++) {

				Guide.Builder guide = Guide.newBuilder();

				Cell[] c = sheet.getRow(i);
				int index = 0;
				
				
				
				//步骤ID
				String id = c[index++].getContents();
				if(!id.equals("")){
					guide.setId(Integer.valueOf(id));
				}else{
					MessageBox.Show("第 " + i + " 行 ID不能等NULL");
				}
				
				
				//模板图片(圆 0  方形 1)
				String modeType = c[index++].getContents();
				if(!modeType.equals("")){
					int type = Integer.valueOf(modeType);
					if(type == 0){
						guide.setModeType(ModeType.ModeType_Round);
					}else if(type == 1){
						guide.setModeType(ModeType.ModeType_Rect);
					}else{
						MessageBox.Show("第 " + id + " 行  模板类型不能识别");
					}
				}else{
					MessageBox.Show("第 " + id + " 行  模板类型不能为NULL");
				}
				
				
				//坐标(x,y#x,y)
				String posList = c[index++].getContents();
				if(posList.equals("")){
					MessageBox.Show("第 " + id + " 行  坐标不能为NULL");
				}
				String[] posItems = posList.split("#\\s*");
				for(int j=0;j<posItems.length;++j){
					String item = posItems[j];
					String[] pos = item.split(",\\s*");
					if(pos.length != 2){
						MessageBox.Show("第 " + id + " 行  坐标错误");
					}
					float x = Float.valueOf(pos[0]);
					float y = Float.valueOf(pos[1]);
					
					Point.Builder pointBuild = Point.newBuilder();
					pointBuild.setX(x);
					pointBuild.setY(y);
					guide.addPointList(pointBuild.build());
				}
				
				//方形(w,h) && 直径(d#d)
				switch (guide.getModeType()) 
				{
				case ModeType_Round:
					index++;
					//直径(d#d)
					String RoundList = c[index++].getContents();
					if(RoundList.equals("")){
						MessageBox.Show("第 " + id + " 行  直径不能为NULL 因为模板类型是 圆");
					}
					String[] roundItems = RoundList.split("#\\s*");
					if(roundItems.length != posItems.length){
						MessageBox.Show("第 " + id + " 行  直径 的个数 和 坐标 个数不一致");
					}
					for(int j=0;j<roundItems.length;++j){
						float d = Float.valueOf(roundItems[j]);						
						guide.addDiameter(d);
					}
					break;
				case ModeType_Rect:
					
					//方形(w,h)
					String RectList = c[index++].getContents();
					if(RectList.equals("")){
						MessageBox.Show("第 " + id + " 行  方形不能为NULL 因为模板类型是 方形");
					}
					String[] rectItems = RectList.split("#\\s*");
					if(rectItems.length != posItems.length){
						MessageBox.Show("第 " + id + " 行  方形的个数和 坐标 个数不一致");
					}
					for(int j=0;j<rectItems.length;++j){
						String item = rectItems[j];
						String[] wh = item.split(",\\s*");
						if(wh.length != 2){
							MessageBox.Show("第 " + id + " 行  方形错误");
						}
						
						float w = Float.valueOf(wh[0]);
						float h = Float.valueOf(wh[1]);
						float x = 0.f - w / 2.f;
						float y = 0.f - h / 2.f;
						
						Rect.Builder rectBuild = Rect.newBuilder();
						rectBuild.setX(x);
						rectBuild.setY(y);
						rectBuild.setW(w);
						rectBuild.setH(h);
						guide.addRect(rectBuild.build());
					}
					
					index++;
					
					break;
				default:
					break;
				}
				
				int touchType = Integer.parseInt(c[index++].getContents());
				
				guide.setTouchType(TouchType.valueOf(touchType));
				
				//触摸范围增加倍数(m#m)
				String multiple = c[index++].getContents();
				if(!multiple.equals("")){
					String[] multipleItems = posList.split("#\\s*");
					if(multipleItems.length != posItems.length){
						MessageBox.Show("第 " + i + " 行  触摸范围增加倍数 的 个数 和 坐标  个数不一致");
					}
					for(int j=0;j<multipleItems.length;++j){
						float m = Float.valueOf(multipleItems[j]);
						guide.addMultiple(m);
					}
					
				}
				
				//描述信息框的位置(x,y)
				String describePos = c[index++].getContents();
				if(describePos.equals("")){
					//MessageBox.Show("第 " + i + " 行  描述信息框的位置 不能为NULL");
					gameGuideDataBuild.addGuideList(guide.build());
					System.out.println(id + " OK");
					continue;
				}
				String[] describePosXY = describePos.split(",\\s*");
				if(describePosXY.length != 2)
				{
					MessageBox.Show("第 " + i + " 行  描述信息框的位置 错误");
				}
				float describePosX = Float.valueOf(describePosXY[0]);
				float describePosY = Float.valueOf(describePosXY[1]);
				Point.Builder describePosBuild = Point.newBuilder();
				describePosBuild.setX(describePosX);
				describePosBuild.setY(describePosY);
				guide.setDescribePos(describePosBuild.build());
				
				
				
				
				//描述信息
				String describe = c[index++].getContents();
				if(!describe.equals("")){
					guide.setDescribe(describe);
				}
				
				
				gameGuideDataBuild.addGuideList(guide.build());
				
				System.out.println(id + " OK");
				
			}
		}
	}

	public void Write(GameGuide data) {
		try {
			File file = new File("BinData/" + "GameGuideData" + ".data");
			if (file.exists() == false) {
				file.createNewFile();
			}
			FileOutputStream fileOutStream = null;

			fileOutStream = new FileOutputStream(file);
			DataOutputStream dos = new DataOutputStream(fileOutStream);
			Tools.write(dos, data.toByteArray());
			dos.close();

			System.out.println("生成" + "GameGuideData" + ".data");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
