package jni;

import org.json.JSONException;






import org.json.JSONObject;
import android.os.Message;
import android.util.Log;

import com.LeTu.Main.HSBalloon_S3_a;
import com.LeTu.Main.R;
import com.letu.tweibo.SharedStorage;
import com.umeng.update.UmengUpdateAgent;

public class JniHelper 
{
	public static final String JNI_ID="JNI_ID";
	//计费
	
	//初始化
	public static final int JNI_ID_PAY_INIT = 1000;
	public static final int JNI_RID_PAY_INIT=61000;
	
	//计费
	public static final int JNI_ID_PAY_PAY = 1001;
	public static final int JNI_RID_PAY_PAY =61001;
	
	//社会化
	//授权
	public static final int JNI_ID_WEIBO_AUTH = 2000;
	public static final int JNI_RID_WEIBO_AUTH = 62000;
	
	//发微博
	public static final int JNI_ID_WEIBO_PUBLISH = 2002;
	public static final int JNI_RID_WEIBO_PUBLISH = 62002;
	
//	//注销微博
//	public static final int JNI_ID_WEIBO_LOGOUT = 2002;
//	public static final int JNI_RID_WEIBO_LOGOUT = 62002;
	
	//检查用户登录类型
	public static final int JNI_ID_CHECKUSER = 2003;
	public static final int JNI_RID_CHECKUSER =62003;
	
	public static final int JNI_ID_VERSIONCODE = 2004; 
	
	
	//创建分享圈
	public static final int JNI_ID_CREATESHARED = 3000;
	public static final int JNI_RID_CREATESHARED = 63000;
	
	//查找分享圈
	public static final int JNI_ID_SEARCHSHARED = 3001;
	public static final int JNI_RID_SEARCHSHARED = 63001;
	
	//加入分享圈
	public static final int JNI_ID_ENTRYSHARED = 3002;
	public static final int JNI_RID_ENTRYSHARED = 63002;
	
	public static String exec(String json)
	{
		try 
		{
			Log.i("cocos2d-x debug info", json);
			
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
			{
				Message msg = Message.obtain(HSBalloon_S3_a.mhandler, HSBalloon_S3_a.AUTH, response);
				
				HSBalloon_S3_a.mhandler.sendMessage(msg);
			}
				break;
			case JNI_ID_WEIBO_PUBLISH:
			{
				Message msg = Message.obtain(HSBalloon_S3_a.mhandler, HSBalloon_S3_a.FWEIBO, response);
				
				HSBalloon_S3_a.mhandler.sendMessage(msg);
			}
				break;
//			case JNI_ID_WEIBO_LOGOUT:
//				JniWeibo.deleteWeibo();
//				break;
			case JNI_ID_CHECKUSER:
				return JniWeibo.checkUser(response);
			case JNI_ID_VERSIONCODE:
				int code = response.getInt("NEW_VERSIONCODE");
				SharedStorage.getInstance().put(HSBalloon_S3_a.getInstance(), "NEW_VERSIONCODE", code);
				UmengUpdateAgent.forceUpdate(HSBalloon_S3_a.getInstance());
				break;
			case JNI_ID_CREATESHARED:
			{
				Message msg = Message.obtain(HSBalloon_S3_a.mhandler,HSBalloon_S3_a.CREATESHARED,response);
				
				HSBalloon_S3_a.mhandler.sendMessage(msg);
			}
				break;
			case JNI_ID_SEARCHSHARED:
			{
				//Message msg = Message.obtain(HSBalloon_S3_a.mhandler, HSBalloon_S3_a.c, obj);
			}
				break;
			case JNI_ID_ENTRYSHARED:
				break;
			}
		}
		catch (JSONException e) 
		{
			e.printStackTrace();
			
			Message msg = Message.obtain(HSBalloon_S3_a.mhandler, HSBalloon_S3_a.SHOWTOAST, R.string.parse_error);
			
			HSBalloon_S3_a.mhandler.sendMessage(msg);
		}
		
		return "";
	}
	
	public static native void execCallback(String json);
	
	public static native int gameEnd();
	
	
	public static native int getProductId();
	
	/**
	 * 显示toast文字 c++调用java函数
	 * @param text
	 * @param toastType 0 shorter 1 longer
	 */
	public static void showToast(String text)
	{
		Log.i("cocos2d-x debug info", "showToast text="+text);
		
		Message msg = Message.obtain(HSBalloon_S3_a.mhandler, HSBalloon_S3_a.SHOWTOAST, text);
		
		HSBalloon_S3_a.mhandler.sendMessage(msg);
	}
	
	

	public static int  getVersion()
	{
		return HSBalloon_S3_a.versionCode;
	}
	
	public static int getChannel()
	{
		return HSBalloon_S3_a.umengchannel;
	}
	
	public static String getVersionName()
	{
		return HSBalloon_S3_a.versionName;
	}
	
	public static String getAppKey()
	{
		return HSBalloon_S3_a.umengkey;
	}
	
	public static String getPhoneModel()
	{
		return android.os.Build.MODEL;
	}
	
	/**
	 * 杀死程序 c++调用java函数
	 */
	public static void killProcess()
	{
		Message msg = Message.obtain(HSBalloon_S3_a.mhandler, HSBalloon_S3_a.KILLPROCESS, null);
		
		HSBalloon_S3_a.mhandler.sendMessage(msg);
	}
	
	public static void OpenURL(String url)
	{
		Message msg = Message.obtain(HSBalloon_S3_a.mhandler, HSBalloon_S3_a.OPENURL, url);
		
		HSBalloon_S3_a.mhandler.sendMessage(msg);
	}
	
}
