/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.LeTu.Main;

import httpClient.HttpCoreAsync;
import jni.JniEggshell;
import jni.JniHelper;
import jni.JniWeibo;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.json.JSONException;
import org.json.JSONObject;

import com.LeTu.Main.R;
import com.chainton.dankeshare.service.DefaultServiceManager;
import com.letu.iPay.LSStatistics;
import com.letu.tweibo.SharedStorage;
import com.letu.util.JsonBuilder;
import com.umeng.update.UmengDialogButtonListener;
import com.umeng.update.UmengUpdateAgent;
import com.umeng.update.UpdateStatus;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;

public class HSBalloon_S3_a extends Cocos2dxActivity{

	private static Activity instance;
	
	public static MyHandler mhandler;
	
	public static int versionCode =0;
	
	public static String versionName="";    
	
	public static int umengchannel = 0;
	
	public static String umengkey = "";
	
	public static Activity getInstance()
	{
		return instance;
	}
	
	public static Context STATIC_REF = null;
	
	public static Context getContext(){
	    return STATIC_REF;
	}
	
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		STATIC_REF = this;
		instance = this;
		DefaultServiceManager.getInstance(HSBalloon_S3_a.getInstance()).saveWifiState();
		//Log.d("cocos2d-x debug info123456", "===================================="+System.currentTimeMillis());
		
		LSStatistics.update(this);
		
		PackageInfo pi;
		try 
		{
			pi = this.getPackageManager().getPackageInfo(this.getPackageName(), 0);
			versionCode = pi.versionCode;
			versionName = pi.versionName;
		} 
		catch (NameNotFoundException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		ApplicationInfo appInfo;
		try {
			appInfo = this.getPackageManager()
			        .getApplicationInfo(getPackageName(),
			PackageManager.GET_META_DATA);
			umengchannel=appInfo.metaData.getInt("UMENG_CHANNEL");
			umengkey = appInfo.metaData.getString("UMENG_APPKEY");
		} catch (NameNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		HttpCoreAsync.getInstance().init(this);
		//初始化一定要写到主线程里面
		JsonBuilder builder = new JsonBuilder();
		builder.put("JNI_ID", 1000);
		builder.put("LandScape", false);
		
		mhandler = new MyHandler();
		
		JniHelper.exec(builder.toJsonString());
		
		UmengUpdateAgent.setDialogListener(new UmengDialogButtonListener() {
		
			    @Override
			    public void onClick(int status) {
			        switch (status) {
			        case UpdateStatus.Update:
			            Toast.makeText(HSBalloon_S3_a.getInstance(), "User chooses update." , Toast.LENGTH_SHORT).show();
			            break;
			        case UpdateStatus.Ignore:
			        case UpdateStatus.NotNow:
			        	
			        	int newCode = 0;
			        	
						try 
						{
							int code  = (int)(SharedStorage.getInstance().getLong(HSBalloon_S3_a.this, "NEW_VERSIONCODE"));
							newCode = code;
						}
						catch (NumberFormatException ex) 
						{
							ex.printStackTrace();
						}
						catch(Exception e)
						{
							e.printStackTrace();
						}
			        	
			        	Log.i("cocos2d-x debug info", "newcode = "+newCode);
			        	Log.i("cocos2d-x debug info", "versionCode ="+versionCode);
			        	
			        	if(versionCode!=0)
			        	{
			        		if(newCode-versionCode>100)//强制更新，如果这个时候选择不更新，就要强关客户端
			        		{
			        			JniHelper.killProcess();
			        		}
			        		else
			        		{
			        			
			        		}
			        	}
			        	else//强制更新，如果这个时候选择不更新，就要强关客户端
			        	{
			        		//UmengUpdateAgent.forceUpdate(HSBalloon_S3_a.getInstance());
			        		JniHelper.killProcess();
			        	}
			            Toast.makeText(HSBalloon_S3_a.getInstance(), "User chooses ignore." , Toast.LENGTH_SHORT).show();
			            break;
			        }
			    }
			});
	}
	
    static 
    {
    	System.loadLibrary("game");
    } 
    
    public static void showParseJsonErrorToast(String str)
    {
    	String string = HSBalloon_S3_a.getInstance().getResources().getString(R.string.parse_error);
    	StringBuffer builder = new StringBuffer();
    	builder.append(string).append("-->").append(str);
		Toast.makeText(HSBalloon_S3_a.getInstance(), builder.toString(), Toast.LENGTH_SHORT).show();
		builder.delete(0, builder.length());
    }
	@Override
	protected void onResume() 
	{
		super.onResume();
		//LSStatistics.onResume(this);
	}
	@Override
	protected void onPause() 
	{
		super.onPause();
		//LSStatistics.onPause(this);
	}
	
	
    
	
	protected void onDestroy() 
	{
		JniEggshell.stopSearchingShareCircle();
		JniEggshell.restoreWifiState();
		super.onDestroy();
		
		//android.os.Process.killProcess(android.os.Process.myPid());
	}

	public static final int SHOWTOAST = 1;
	public static final int AUTH = 2;
	public static final int FWEIBO = 3;
	public static final int KILLPROCESS = 4;
	public static final int CREATESHARED = 5;
	public static final int SEARCHSHARED = 6;
	public static final int ENTRYSHARED = 7;
	public static final int AUTODISTRIBUTE = 8;
	public static final int HANDLEDISTRIBUTE = 9;
	public static final int DISTRIBUTE = 10;
	
	public static final int GETMYINFO = 11;
	public static final int GETOTHERINFO = 12;
	public static final int DISCOONECTION = 13;
	public static final int CLOSE = 14;
	public static final int RESTOREWIFI = 15;
	
	public static final int STOPSEARCHINGSHARECIRCLE = 16;
	public static final int OPENURL = 17;
	
	
	
	public static void showToast(String str)
	{
		Message msg = Message.obtain(mhandler, SHOWTOAST, str);
		mhandler.sendMessage(msg);
	}
	
	public void goWifiSeting()
	{
		if (android.os.Build.VERSION.SDK_INT > 10) {
			// 3.0以上打开设置界面，也可以直接用ACTION_WIRELESS_SETTINGS打开到wifi界面
			startActivity(new Intent(android.provider.Settings.ACTION_SETTINGS));
		} else {
			startActivity(new Intent(android.provider.Settings.ACTION_WIRELESS_SETTINGS));
		}
	}
	
    @SuppressLint("HandlerLeak")
	public class MyHandler extends Handler
    {
		@Override
		public void handleMessage(Message msg) 
		{
			switch(msg.what)
			{
			case SHOWTOAST:
				Toast.makeText(HSBalloon_S3_a.this,String.valueOf(msg.obj),Toast.LENGTH_LONG).show();
				break;
			case AUTH:
				JniWeibo.auth((JSONObject)msg.obj);
				break;
			case FWEIBO:
				JniWeibo.addWeibo((JSONObject)msg.obj);
				break;
			case KILLPROCESS:
				android.os.Process.killProcess(android.os.Process.myPid());
				break;
			case CREATESHARED:
				try
				{
					JniEggshell.createShared((JSONObject)msg.obj);
				} 
				catch (JSONException e) 
				{
					e.printStackTrace();
				}
				break;
			case SEARCHSHARED:
				try
				{
					JniEggshell.searchShardList((JSONObject)msg.obj);
				}
				catch (JSONException e) 
				{
					e.printStackTrace();
				}
				break;
			case ENTRYSHARED:
				try 
				{
					JniEggshell.entryShared((JSONObject)msg.obj);
				} 
				catch (JSONException e) 
				{
					e.printStackTrace();
				}
				break;
			case GETMYINFO:
				JniEggshell.getMyInfo();
				break;
			case GETOTHERINFO:
				JniEggshell.getOtherInfo();
				break;
			case DISCOONECTION:
				JniEggshell.disconnect((Boolean)msg.obj);
				break;
			case CLOSE:
				android.os.Process.killProcess(android.os.Process.myPid());
				break;
			case RESTOREWIFI:
				JniEggshell.restoreWifiState();
				break;
				
			case STOPSEARCHINGSHARECIRCLE:
				DefaultServiceManager.getInstance(HSBalloon_S3_a.getInstance()).stopSearchingShareCircle();
				break;
			case OPENURL:
				openURL(String.valueOf(msg.obj));
				break;
			}
		}
    }
    
    public void openURL(String url)
    {
    	Uri uri = Uri.parse(url);  
	    Intent it = new Intent(Intent.ACTION_VIEW, uri);  
	    startActivity(it);
    }
}
