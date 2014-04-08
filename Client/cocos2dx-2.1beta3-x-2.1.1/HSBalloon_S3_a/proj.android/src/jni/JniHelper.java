package jni;

import org.json.JSONException;


import org.json.JSONObject;
import android.widget.Toast;

import com.LeTu.Main.HSBalloon_S3_a;
import com.LeTu.Main.R;

public class JniHelper 
{
	public static final String JNI_ID="JNI_ID";
	//计费
	
	//初始化
	public static final int JNI_ID_PAY_INIT = 1000;
	public static final int JNI_RID_PAY_INIT=61000;
	
	//计费
	public static final int JNI_ID_PAY_PAY = 10001;
	public static final int JNI_RID_PAY_PAY =61001;
	
	//社会化
	//授权
	public static final int JNI_ID_WEIBO_AUTH = 2000;
	public static final int JNI_RID_WEIBO_AUTH = 62000;
	
	//发微博
	public static final int JNI_ID_WEIBO_PUBLISH = 2001;
	public static final int JNI_RID_WEIBO_PUBLISH = 62001;
	
	//注销微博
	public static final int JNI_ID_WEIBO_LOGOUT = 2002;
	public static final int JNI_RID_WEIBO_LOGOUT = 62002;
	
	
	
	public static void exec(String json)
	{
		try 
		{
			JSONObject response = new JSONObject(json);
			
			int id = response.getInt(JNI_ID);
			
			switch(id)
			{
			case JNI_ID_PAY_INIT:
				JniPay.init(response);
				break;
			case JNI_ID_PAY_PAY:
				JniPay.pay(response);
				break;
			case JNI_ID_WEIBO_AUTH:
				JniWeibo.auth(response);
				break;
			case JNI_ID_WEIBO_PUBLISH:
				JniWeibo.addWeibo(response);
				break;
			case JNI_ID_WEIBO_LOGOUT:
				JniWeibo.deleteWeibo();
				break;
			}
		}
		catch (JSONException e) 
		{
			e.printStackTrace();
			Toast.makeText(HSBalloon_S3_a.getInstance(), R.string.parse_error, Toast.LENGTH_SHORT).show();
		}
	}
	
	public static native void execCallback(String json);
	
	/**
	 * 显示toast文字 c++调用java函数
	 * @param text
	 * @param toastType 0 shorter 1 longer
	 */
	public static void showToast(String text,int toastType)
	{
		Toast.makeText(HSBalloon_S3_a.getInstance(), text, toastType).show();
		//Toast.makeText(context, text, duration)
	}
	/**
	 * 杀死程序 c++调用java函数
	 */
	public static void killProcess()
	{
		android.os.Process.killProcess(android.os.Process.myPid());
	}
	
	
}
