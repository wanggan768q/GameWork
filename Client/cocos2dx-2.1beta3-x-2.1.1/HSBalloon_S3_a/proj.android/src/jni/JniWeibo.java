package jni;

import org.json.JSONException;
import org.json.JSONObject;

import com.LeTu.Main.HSBalloon_S3_a;
import com.letu.tweibo.TWeibo;
import com.letu.tweibo.WeiboCallback;
import com.letu.util.JsonBuilder;

public class JniWeibo 
{
	
	public static final String WEIBO_RESULT ="WEIBO_RESULT";
	public static final String WEIBO_ERR = "WEIBO_ERR";
	
	public static final String WEIBO_TYPE ="WEIBO_TYPE";
	public static final String WEIBO_TEXT ="WEIBO_TEXT";
	public static void auth(JSONObject json)
	{
		try 
		{
			int type = json.getInt(WEIBO_TYPE);
			
			TWeibo.auth(HSBalloon_S3_a.getInstance(), type, new WeiboCallback() 
			{
				@Override
				public void onAuthResult(int result, String err) 
				{
					authFinish(result,err);
				}
			});	
		}
		catch (JSONException e) 
		{
			e.printStackTrace();
			HSBalloon_S3_a.showParseJsonErrorToast("auth");
		}
		
	}
	
	public static void authFinish(int result,String err)
	{
		JsonBuilder builder = new JsonBuilder();
		builder.put(JniHelper.JNI_ID, JniHelper.JNI_RID_WEIBO_AUTH);
		builder.put(WEIBO_RESULT, result);
		builder.put(WEIBO_ERR,err);
		JniHelper.execCallback(builder.toJsonString());
	}
	
	public static void addWeibo(JSONObject json)
	{
		try 
		{
			String text = json.getString(WEIBO_TEXT);
			
			int type = json.getInt(WEIBO_TYPE);
			
			TWeibo.addWeibo(HSBalloon_S3_a.getInstance(), text, type);	
		}
		catch (JSONException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		//
		
	}
	
	public  static void deleteWeibo()
	{
		//TWeibo.deleteWeibo();
	}
}
