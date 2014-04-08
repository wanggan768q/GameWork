package com.zrlh.tom.pkmmq;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;
import message.HSChannel.Channel; 
import android.app.Dialog;
import android.content.Context; 
import android.util.Log; 
import android.widget.Toast;

import com.tom.pkgame.apis.*;
 
public class HSChannelManager {
	static Channel channel;  

	/** 购买道具 **/
	public static void Buy(byte buffer[]) {
 
		try { 
			channel = Channel.parseFrom(buffer);
		} catch (Exception e) { 
			e.printStackTrace();
		}
		IAPHandler.sharedHandler().post(new Runnable() {
			@Override
			public void run() { 
				goumai(channel.getTom().getTitle(), channel.getTom()
						.getDescribe(), channel.getTom().getGameMoney(),
						channel.getTom().getPropID());

//				Log.d("zzx", "发出购买！");
			}

		});
	}

	public static void init(Context context) {
		Properties properties = new Properties();
		try {
			InputStream inputStream = context.getAssets().open(
					"tompkgame.properties");
			properties.load(inputStream);
		} catch (IOException e) {
			e.printStackTrace();
		}

		int freeCount = Integer.parseInt(properties.getProperty(
				"tompkgamefreecount", "0"));
		String cpId = properties.getProperty("tompkgamecpid", "00");
		String gameId = properties.getProperty("tompkgamegameid", "1");
		String channelId = properties.getProperty("tompkgamechannelid", "00");
		String version = properties.getProperty("tompkgameversion", "3");
		Apis.switch_push = properties.getProperty("switchpush", "0");

		Apis.getInstance().init(context, freeCount, cpId, gameId, channelId,
				version);
		Apis.getGreet(context);
		

//		Log.d("zzx", "初始化成功！");
	}

	public static void goumai(final String title, String info, int tem, final int id) {

		Apis.payUI(HSBalloon_a.mHSBalloon_a, tem, title, info,
				new com.tom.pkgame.apis.OnPayFinish() {
					public void onPayFinish(boolean payState) {
						if (payState) {  
//							Log.d("zzx", "购买成功！");
							CallBuy(id);
							Toast.makeText(HSBalloon_a.getContext(), "购买"+title+"成功！", Toast.LENGTH_LONG).show();
						} else { 
//							Log.d("zzx", "购买失败！");
							Toast.makeText(HSBalloon_a.getContext(), "购买失败！", Toast.LENGTH_LONG).show();
						}
					}
				}, id);
	}

	/** 购买成功 或者 失败 回调 **/
	public native static void CallBuy(int id);

}
 
