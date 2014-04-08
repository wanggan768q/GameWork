package com.zrlh.tom.pkmmq;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.Context;
import android.telephony.TelephonyManager;

public class HSDeviceInfo {
	 
	public static TelephonyManager tm = ((TelephonyManager) Cocos2dxActivity.getContext().getSystemService(Context.TELEPHONY_SERVICE)); 
	public static String GetUUID()
	{
		String DEVICE_ID = tm.getDeviceId(); 
		return DEVICE_ID;
	}
	
	public static String GetSystemVersions()
	{
		return tm.getDeviceSoftwareVersion();
	}
	
	public static String GetNetType()
	{
		return String.valueOf(tm.getNetworkType()) ;
	}
	
	public static String GetOperator()
	{
		return tm.getSimOperatorName();
	}
	
	public static String GetCountryInfo()
	{
		return tm.getNetworkCountryIso();
	}
	
	public static String GetCityInfo()
	{
		return tm.getLine1Number();
	}
}
