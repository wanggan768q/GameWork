package jni;

import org.json.JSONException;


import org.json.JSONObject;
import org.json.JSONTokener;

import android.content.Intent;
import android.util.Log;
import android.widget.Toast;

import com.LeTu.Main.HSBalloon_S3_a;
import com.letu.iPay.LSDispatcherCallback;
import com.letu.iPay.LSPlatform;
import com.letu.baselib.io.LSProtocolConfigs;
import com.letu.baselib.io.LSProtocolKeys;
import com.letu.util.JsonBuilder;

public class JniPay {

	public static void init(JSONObject json)
	{
		boolean isLandScape;
		try 
		{
			isLandScape = json.getBoolean("LandScape");
			
			Log.i("cocos2d-x debug info", "LandScape="+isLandScape);
			
			LSPlatform.init(HSBalloon_S3_a.getInstance(), isLandScape, new LSDispatcherCallback() 
			{	
				@Override
				public void onFinish(String data) 

				{
					  JSONTokener jsonParser = new JSONTokener(data);
					  try 
					  {
						JSONObject response = (JSONObject) jsonParser.nextValue();
						
						int code = response.getInt(LSProtocolKeys.LS_FUNCTION_CODE); 
						
						if(code == LSProtocolConfigs.LS_FUNCTION_CODE_INIT)
						{
							int status = response.getInt(LSProtocolKeys.LS_FUNCTIONI_STATUS);
							String state = response.getString(LSProtocolKeys.LS_FUNCTION_STATE);
							
							if(status ==LSProtocolConfigs.LS_FUNCTION_STATUS_OK)
							{	 
								 finishInit(status,state);
							}
							else
							{
								Toast.makeText(HSBalloon_S3_a.getInstance(), "初始化错误，status="+status+",state=state",Toast.LENGTH_SHORT).show();
								finishInit(status,state);
							}
						}
						else
						{
							Toast.makeText(HSBalloon_S3_a.getInstance(), "初始化 返回code错误，code="+code+",应该是"+LSProtocolConfigs.LS_FUNCTION_CODE_INIT, Toast.LENGTH_SHORT).show();
							finishInit(LSProtocolConfigs.LS_FUNCTION_STATUS_ERROR,"");
						}
					}
					catch (JSONException e) 
					{
						Toast.makeText(HSBalloon_S3_a.getInstance(), "初始化错误，sdk返回数据解析错误", Toast.LENGTH_SHORT).show();
						e.printStackTrace();
					}  
				}
			});
		} 
		catch 
		(JSONException e1) 
		{
			
			e1.printStackTrace();
			HSBalloon_S3_a.showParseJsonErrorToast("pay_init");
		}
		
		
	}
	
	public static void finishInit(int status,String state)

	{
		 JsonBuilder build = new JsonBuilder();
		 build.put(JniHelper.JNI_ID, JniHelper.JNI_RID_PAY_INIT);
		 build.put(LSProtocolKeys.LS_FUNCTIONI_STATUS, status);
		 build.put(LSProtocolKeys.LS_FUNCTION_STATE, state);
		 JniHelper.execCallback(build.toJsonString());
	}
	
	public static void pay(JSONObject json)

	{
		
		String goodId=null;
		int size =0;
		int money =0;
		String uid ="";
		try {
			goodId = json.getString(LSProtocolKeys.LS_FUNCTION_GOOD_ID);
			size = json.getInt(LSProtocolKeys.LS_FUNCTION_GOOD_SIZE);
			money = json.getInt(LSProtocolKeys.LS_FUNCTION_GOOD_TOTAL);
			uid = json.getString(LSProtocolKeys.LS_FUNCTION_PAY_UID);
			
			Intent intent = new Intent();
			intent.putExtra(LSProtocolKeys.LS_FUNCTION_CODE, LSProtocolConfigs.LS_FUNCTION_CODE_PAY);
			
			intent.putExtra(LSProtocolKeys.LS_FUNCTION_GOOD_ID, goodId);
			intent.putExtra(LSProtocolKeys.LS_FUNCTION_GOOD_SIZE, size);
			intent.putExtra(LSProtocolKeys.LS_FUNCTION_GOOD_TOTAL, money);
			intent.putExtra(LSProtocolKeys.LS_FUNCTION_PAY_UID, uid);
			
			intent.putExtra(LSProtocolKeys.LS_FUNCTION_PRODUCTID, String.valueOf(JniHelper.getProductId()));
			intent.putExtra(LSProtocolKeys.LS_FUNCTION_CHANNELID, String.valueOf(JniHelper.getChannel()));
			
			LSPlatform.invokeActivity(HSBalloon_S3_a.getInstance(), intent, new LSDispatcherCallback() 
			{
				@Override
				public void onFinish(String data) 
				{
					// TODO Auto-generated method stub
					JSONTokener jsonParser = new JSONTokener(data);
					
					try {
						JSONObject response = (JSONObject) jsonParser.nextValue();
						
						int code = response.getInt(LSProtocolKeys.LS_FUNCTION_CODE); 
						
						if(code == LSProtocolConfigs.LS_FUNCTION_CODE_PAY)
						{
							int status = response.getInt(LSProtocolKeys.LS_FUNCTIONI_STATUS);
							
							String order = response.getString(LSProtocolKeys.LS_FUNCTIONI_ORDER);
							
							int money = response.getInt(LSProtocolKeys.LS_FUNCTION_MONEY);
							
							String state = response.getString(LSProtocolKeys.LS_FUNCTION_STATE);
							
							Toast.makeText(HSBalloon_S3_a.getInstance(), "购买成功 花费人民币"+money+"元", Toast.LENGTH_SHORT).show();
							
							finishPay(status,order,money,state);
						}
						else
						{
							Toast.makeText(HSBalloon_S3_a.getInstance(), "购买 返回code错误，code="+code+",应该是"+LSProtocolConfigs.LS_FUNCTION_CODE_PAY, Toast.LENGTH_SHORT).show();
							finishPay(LSProtocolConfigs.LS_FUNCTION_STATUS_ERROR,"",0,"");
						}
					} 
					catch (JSONException e) 
					{
						 Toast.makeText(HSBalloon_S3_a.getInstance(), "购买，sdk返回数据解析错误", Toast.LENGTH_SHORT).show();
						 e.printStackTrace();
					}
				}
			});
		}
		catch (JSONException e1) 
		{
			// TODO Auto-generated catch block
			e1.printStackTrace();
			HSBalloon_S3_a.showParseJsonErrorToast("pay_pay");
		}
	}
	
	
	public static void finishPay(int status,String order,int money,String state)
	{
		JsonBuilder build = new JsonBuilder();
		 build.put(JniHelper.JNI_ID, JniHelper.JNI_RID_PAY_PAY);
		 build.put(LSProtocolKeys.LS_FUNCTIONI_STATUS, status);
		 build.put(LSProtocolKeys.LS_FUNCTIONI_ORDER, order);
		 build.put(LSProtocolKeys.LS_FUNCTION_MONEY, money);
		 build.put(LSProtocolKeys.LS_FUNCTION_STATE, state);
		 JniHelper.execCallback(build.toJsonString());
	}

}
