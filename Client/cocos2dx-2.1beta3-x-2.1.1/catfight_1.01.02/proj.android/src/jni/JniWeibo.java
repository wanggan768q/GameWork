package jni;

import org.json.JSONException;
import org.json.JSONObject;

import android.os.Bundle;
import android.os.Message;

import com.LeTu.Main.HSBalloon_S3_a;
import com.LeTu.Main.R;
import com.letu.tweibo.SharedStorage;
import com.letu.tweibo.TWeibo;
import com.letu.tweibo.WeiboCallback;
import com.letu.util.JsonBuilder;

public class JniWeibo 
{
	public static void auth(JSONObject json)
	{
		try 
		{
			final int type = json.getInt(WeiboCallback.WEIBO_TYPE);
			
			String appId = json.getString(WeiboCallback.WEIBO_GAME_APPID);
			
			String uid = json.getString(WeiboCallback.WEIBO_GAME_UID);
			
			TWeibo.auth(HSBalloon_S3_a.getInstance(), type,appId,uid, new WeiboCallback() 
			{
				@Override
				public void onAuthResult(int result, Bundle bundle) 
				{
					if(result ==0)//成功了
					{
						SharedStorage.getInstance().put(HSBalloon_S3_a.getInstance(), WeiboCallback.WEIBO_TYPE, type);
					}
					
					authFinish(result,bundle);
				}
			});	
		}
		catch (JSONException e) 
		{
			e.printStackTrace();
			HSBalloon_S3_a.showParseJsonErrorToast("auth");
		}
		
	}
	
	public synchronized static void authFinish(int result,Bundle bundle)
	{
		JsonBuilder builder = new JsonBuilder();
		builder.put(JniHelper.JNI_ID, JniHelper.JNI_RID_WEIBO_AUTH);
		builder.put(WeiboCallback.WEIBO_OPENID, bundle.get(WeiboCallback.WEIBO_OPENID));
		builder.put(WeiboCallback.WEIBO_NAME, bundle.get(WeiboCallback.WEIBO_NAME));
		builder.put(WeiboCallback.WEIBO_RESULT, result);
		builder.put(WeiboCallback.WEIBO_ERR,bundle.get(WeiboCallback.WEIBO_ERR));
		
		JniHelper.execCallback(builder.toJsonString());
		
	}
	
	private static long lastTime = 0;
	
	public static void addWeibo(JSONObject json)
	{
		try 
		{
			String text = json.getString(WeiboCallback.WEIBO_TEXT);
			
			int type = json.getInt(WeiboCallback.WEIBO_TYPE);
			
			if(type ==99)
			{
				long cur = System.currentTimeMillis();
				if(cur-lastTime>3000)
				{
					Message msg = Message.obtain(HSBalloon_S3_a.mhandler, HSBalloon_S3_a.SHOWTOAST, "要使用分享功能，请用微博账号登录游戏");
					
					HSBalloon_S3_a.mhandler.sendMessage(msg);
					
					lastTime = cur;
				}
			}
			else
			{
				TWeibo.addWeibo(HSBalloon_S3_a.getInstance(), text, type);	
			}
			
		}
		catch (JSONException e) 
		{
			e.printStackTrace();
		}
	}
	
	public static void deleteWeibo()
	{
		
	}
	
	public static String  checkUser(JSONObject json)
	{
		int type =(int)SharedStorage.getInstance().getLong(HSBalloon_S3_a.getInstance(), WeiboCallback.WEIBO_TYPE);
		
		JsonBuilder builder = new JsonBuilder();
		JniHelper.execCallback(builder.toJsonString());
		builder.put(JniHelper.JNI_ID, JniHelper.JNI_RID_CHECKUSER);
		builder.put(WeiboCallback.WEIBO_TYPE, type);
		
		return builder.toJsonString();
	}
}
