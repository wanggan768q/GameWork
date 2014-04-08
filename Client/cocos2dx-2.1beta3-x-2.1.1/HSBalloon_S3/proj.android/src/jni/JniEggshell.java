package jni;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.os.Handler;
import android.os.Message;
import android.util.Log;

import com.LeTu.Main.HSBalloon_S3_a;
import com.chainton.dankeshare.CreateShareCircleResult;
import com.chainton.dankeshare.OperationResult;
import com.chainton.dankeshare.SearchShareCircleCallback;
import com.chainton.dankeshare.ShareCircleClient;
import com.chainton.dankeshare.ShareCircleServer;
import com.chainton.dankeshare.data.ClientInfo;
import com.chainton.dankeshare.data.ShareCircleAppInfo;
import com.chainton.dankeshare.data.ShareCircleInfo;
import com.chainton.dankeshare.data.enums.ShareCircleServiceStatus;
import com.chainton.dankeshare.data.enums.ShareCircleType;
import com.chainton.dankeshare.exception.WrongServiceModeException;
import com.chainton.dankeshare.service.DefaultServiceManager;
import com.letu.baselib.util.JsonBuilder;

public class JniEggshell {

	public static final String JNI_EGG_RESULT = "JNI_EGG_RESULT";
	public static final String JNI_EGG_USER_NAME = "JNI_EGG_USER_NAME";
	public static final String JNI_EGG_ROOM_NAME = "JNI_EGG_ROOM_NAME";
	public static final String JNI_EGG_ROOM_MAXNUM = "JNI_EGG_ROOM_MAXNUM";
	public static final String JNI_EGG_ROOM_CURNUM = "JNI_EGG_ROOM_CURNUM";
	public static final String JNI_EGG_ROOM_LIST = "JNI_EGG_ROOM_LIST";
	public static final String JNI_EGG_STATUS = "JNI_EGG_STATUS";

	public static final String JNI_EGG_UID = "JNI_EGG_UID";
	public static final String JNI_EGG_ICONID = "JNI_EGG_ICONID";
	public static final String JNI_EGG_IP = "JNI_EGG_IP";
	public static final String JNI_EGG_SSID = "JNI_EGG_SSID";
	public static final String JNI_EGG_SEARCH_TYPE = "JNI_EGG_SEARCH_TYPE";

	public static final String JNI_EGG_WIFI_CLOSE = "JNI_EGG_WIFI_CLOSE";
	public static final String JNI_EGG_WIFI_RESTORE = "JNI_EGG_WIFI_RESTORE";

	public static final int JNI_EGG_EMPTY_USERNAME = 1;
	public static final int JNI_EGG_EMPTY_ROOMNAME = 2;
	public static final int JNI_EGG_REJECT = 3;
	public static final int JNI_EGG_CONNECTIONFAIL = 4;
	public static final int JNI_EGG_FIND_ROOM_FAIL = 5;
	public static final int JNI_EGG_EMPTY_ROOMLIST = 6;
	public static final int JNI_EGG_ROOM_ENOUGH = 7;
	
	//是否需要 kill 进程
	public static Boolean IsKill = false;
	
	public static final String[] Excptions = { "Excption_CreateShareCircle", "Excption_CreateClient", "Excption_SearchShard","Excption_SearchShardOuttime" };
	
	
	
	

	public static ShareCircleServer shareCircleManager;
	public static ShareCircleClient clientManager;
	public static ShareCircleAppInfo shareCircleAppInfo = new ShareCircleAppInfo();

	public static boolean isCreateShared = false;

	static {
		shareCircleAppInfo.appId = 3;
		shareCircleAppInfo.name = "catFight";
		shareCircleAppInfo.version = "1.01.03";
	}

	private static ClientInfo selfInfo;
	

	/**
	 * 创建分享圈
	 * 
	 * @param json
	 * @throws JSONException
	 */
	public static void createShared(JSONObject json) throws JSONException {
		// 得到c++传入的userName
		String userName = json.getString(JNI_EGG_USER_NAME);
		// 分享圈最大人数
		int max = json.getInt(JNI_EGG_ROOM_MAXNUM);
		// 创建clientInfo对象，创建分享圈的时候要作为参数传入
		selfInfo = createSelfInfo(userName);

		//final long initTime = System.currentTimeMillis();

		try {
			Log.i("cocos2dx debug info", "开始创建分享区");
			shareCircleManager = new ShareCircleServerImpl();
			clientManager = new ShareCircleClientImpl();
			// 创建分享圈
			DefaultServiceManager.getInstance(HSBalloon_S3_a.getInstance()).createShareCircle(userName, ShareCircleType.WIFIAP, shareCircleAppInfo, selfInfo, max, new CreateShareCircleResult() 
			{
				
				@Override
				public void onFailed() {
					// TODO Auto-generated method stub
					shareCircleManager = null;
					createHotWifiFail();
				}

				@Override
				public void onSucceed(ShareCircleInfo arg0) {
					// TODO Auto-generated method stub
					
					Log.v("cocos2d-x debug info", Thread.currentThread().getId() + " " + "onShareCircleCreateSuccess");
					// 通知c++创建成功
					JsonBuilder build = new JsonBuilder();
					build.put(JniHelper.JNI_ID, JniHelper.JNI_RID_CREATESHARED);
					build.put(JNI_EGG_RESULT, 0);
					JniHelper.execCallback(build.toJsonString());

					isCreateShared = true;
				}
			}, shareCircleManager,clientManager);
		} catch (WrongServiceModeException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			
			ShellExcption("Excption_CreateShareCircle");
		}
	}

	private static ClientInfo createSelfInfo(String name) {
		ClientInfo selfInfo = new ClientInfo();
		selfInfo.name = name;
		selfInfo.headIconIndex = 1;

		return selfInfo;
	}

	private static void createHotWifiFail() {
		String info = HSBalloon_S3_a.getInstance().getString(com.LeTu.Main.R.string.create_share_circle_failed);
		Message msg = Message.obtain(HSBalloon_S3_a.mhandler, HSBalloon_S3_a.SHOWTOAST, info);
		HSBalloon_S3_a.mhandler.sendMessage(msg);

		// 通知c++创建失败
		JsonBuilder build = new JsonBuilder();
		build.put(JniHelper.JNI_ID, JniHelper.JNI_RID_CREATESHARED);
		build.put(JNI_EGG_RESULT, 1);
		JniHelper.execCallback(build.toJsonString());
	}

	// 客户端加入方法
	public static void entryShared(JSONObject json) throws JSONException {
		Log.i("cocos2d-x debug info", "entry Shared");

		String userName = json.getString(JNI_EGG_USER_NAME);
		String ssid = json.getString(JNI_EGG_SSID);

		if (userName == null) {
			HSBalloon_S3_a.showToast("用户名称为空");

			entryFail(JNI_EGG_EMPTY_USERNAME);
			return;
		}

		// 通过ssid找到对应的分享圈
		final ShareCircleInfo shareCircleInfo = getRoom(ssid);

		if (shareCircleInfo != null) {
			// 通过用户名，创建ClientInfo对象
			final ClientInfo clientInfo = createSelfInfo(userName);

			Log.i("cocos2d-x debug info", "entry room");
			try {

				clientManager = new ShareCircleClientImpl();
				// 创建client端
				DefaultServiceManager.getInstance(HSBalloon_S3_a.getInstance()).createShareCircleClient(shareCircleInfo, clientInfo, new OperationResult() {

					@Override
					public void onFailed() {
						// TODO Auto-generated method stub
						entryFail(JNI_EGG_FIND_ROOM_FAIL);
					}

					@Override
					public void onSucceed() {
						// TODO Auto-generated method stub
						entrySuccess();
					}

				},clientManager);
			} catch (WrongServiceModeException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				ShellExcption("Excption_CreateClient");
			}

		} else {
			entryFail(JNI_EGG_FIND_ROOM_FAIL);
			return;
		}
	}

	public static void entrySuccess() {
		Log.i("cocos2d-x debug info", "entry Success");
		JsonBuilder build = new JsonBuilder();
		build.put(JniHelper.JNI_ID, JniHelper.JNI_RID_ENTRYSHARED);
		build.put(JNI_EGG_RESULT, 0);
		build.put(JNI_EGG_STATUS, 0);
		JniHelper.execCallback(build.toJsonString());
	}

	public static void entryFail(int status) {
		String info = HSBalloon_S3_a.getInstance().getString(com.LeTu.Main.R.string.entry_share_client_failed);
		Message msg = Message.obtain(HSBalloon_S3_a.mhandler, HSBalloon_S3_a.SHOWTOAST, info);
		HSBalloon_S3_a.mhandler.sendMessage(msg);

		JsonBuilder build = new JsonBuilder();
		build.put(JniHelper.JNI_ID, JniHelper.JNI_RID_ENTRYSHARED);
		build.put(JNI_EGG_RESULT, 1);
		build.put(JNI_EGG_STATUS, status);
		JniHelper.execCallback(build.toJsonString());
	}

	private static ShareCircleInfo getRoom(String ssid) {
		if (roomLists == null) {
			HSBalloon_S3_a.showToast("房间列表为空");
			entryFail(JNI_EGG_EMPTY_ROOMLIST);
			return null;
		} else {
			if (ssid == null) {
				HSBalloon_S3_a.showToast("房间名称为空");
				entryFail(JNI_EGG_EMPTY_ROOMNAME);
				return null;
			}

			for (int i = 0; i < roomLists.size(); i++) {
				ShareCircleInfo shareCircleInfo = roomLists.get(i);
				if (shareCircleInfo != null) {
					if (ssid.equals(shareCircleInfo.ssid)) {
						return roomLists.get(i);
					}
				}
			}
		}

		return null;

	}

	private static List<ShareCircleInfo> roomLists = null;

	private static JsonBuilder all;
	private static JSONArray roomList;

	public static void searchShardList(JSONObject json) throws JSONException {

		int type = 0;

		try {
			// 获取查找的类型
			type = json.getInt(JNI_EGG_SEARCH_TYPE);
		} catch (Exception e1) {
			e1.printStackTrace();
		}

		final int ftype = type;

		all = new JsonBuilder();

		roomList = new JSONArray();

		// 清空roomLists
		if (roomLists == null) {
			roomLists = new ArrayList<ShareCircleInfo>();
		} else {
			roomLists.clear();
		}

		
		new Thread(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				SearchRoomList(ftype);
			}
		}).start();
		
		
	}
	
	public static void SearchRoomList(final int ftype)
	{
		try {

			int outTime = 0;
			while (!DefaultServiceManager.getInstance(HSBalloon_S3_a.getInstance()).getServiceStatus().equals(ShareCircleServiceStatus.READY)) 
			{
				try {
					int sleepTime = 500;
					Thread.sleep(sleepTime);
					if(outTime / 1000 > 20){
						outTime = 0;
						ShellExcption("Excption_SearchShardOuttime");
						//HSBalloon_S3_a.getInstance().g
						return;
					}else{
						outTime += sleepTime;
					}
					
					
				} catch (Exception e) {
				}
			}
			

			// 查找
			DefaultServiceManager.getInstance(HSBalloon_S3_a.getInstance()).searchShareCircle(shareCircleAppInfo, new SearchShareCircleCallback() 
			{
				// 查找完成，返回room的集合，但是这里不用集合了，直接用roomList
				@Override
				public void onFoundShareCircle(Collection<ShareCircleInfo> arg0) {
					// TODO Auto-generated method stub
					
					Boolean isUpdate = false;
					if (roomLists == null) {
						roomLists = new ArrayList<ShareCircleInfo>();
						isUpdate = true;
					}
					Iterator<ShareCircleInfo> it = arg0.iterator();
					//
					int indexx = 0;
					while (it.hasNext()) 
					{
						ShareCircleInfo shareCircleInfo = it.next();
						Log.d("cocos2d-x debug info", indexx + "  name = " + shareCircleInfo.name);
					}
					
					if(arg0.size()  != roomLists.size())
					{
						
						roomLists.clear();
						isUpdate = true;
						
					}else{
						it = arg0.iterator();
						while (it.hasNext()) 
						{
							ShareCircleInfo shareCircleInfo = it.next();
							Boolean isEquals = false;
							for(int i=0;i<roomLists.size();++i)
							{
								if(shareCircleInfo.ssid.equals(roomLists.get(i).ssid))
								{
									isEquals = true;
									break;
								}
							}
							if(isEquals == false)
							{
								roomLists.clear();
								isUpdate = true;
								break;
							}
						}
						
					}
					if(isUpdate)
					{
						roomLists.clear();
						it = arg0.iterator();
						while (it.hasNext()) 
						{
							ShareCircleInfo shareCircleInfo = it.next();
							
							String name = shareCircleInfo.name;
							String ssid = shareCircleInfo.ssid;

							Log.d("cocos2d-x debug info", "name = " + name + ",ssid=" + ssid);

							JsonBuilder build = new JsonBuilder();
							build.put(JNI_EGG_ROOM_NAME, shareCircleInfo.name);
							build.put(JNI_EGG_SSID, shareCircleInfo.ssid);
							build.put(JNI_EGG_ROOM_MAXNUM, 2);
							build.put(JNI_EGG_ROOM_CURNUM, 1);
							roomList.put(build.getJsonObject());	
							
							roomLists.add(shareCircleInfo);
				        }

						all.put(JniHelper.JNI_ID, JniHelper.JNI_RID_SEARCHSHARED);
						all.put(JNI_EGG_SEARCH_TYPE, ftype);
						all.put(JNI_EGG_ROOM_LIST, roomList);
						JniHelper.execCallback(all.toJsonString());
					}
					
					
				}

				@Override
				public void onStartSearchingFailed() {
					// TODO Auto-generated method stub
					//开始搜索失败
					String info = HSBalloon_S3_a.getInstance().getString(com.LeTu.Main.R.string.search_share_timeout);
					HSBalloon_S3_a.showToast(info);

					JsonBuilder all = new JsonBuilder();

					all.put(JniHelper.JNI_ID, JniHelper.JNI_RID_SEARCHSHARED);
					all.put(JNI_EGG_SEARCH_TYPE, ftype);
					JSONArray roomList = new JSONArray();
					all.put(JNI_EGG_ROOM_LIST, roomList);

					JniHelper.execCallback(all.toJsonString());
					
				}
			});
		} catch (WrongServiceModeException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			ShellExcption("Excption_SearchShard");
		}
	}
		

	/**
	 * 客户端发送，要求服务器自动转发
	 * 
	 * @param bytes
	 */
	public static void autoDistribute(byte[] bytes) {
		if (clientManager != null) {
			Log.i("cocos2d-x debug info", Thread.currentThread().getId() + " " + "autoDistribute len =" + bytes.length);
			clientManager.sendAutoDistributeData(bytes);
			return;
		}
		Log.i("cocos2d-x debug info", Thread.currentThread().getId() + " " + "autoDistribute clientManager is null len =" + bytes.length);
	}

	public static void distributeDataToOthers(byte[] bytes, int len) {
		if (clientManager != null) {

			//if (bytes.length == len) {

			//} else {
				Log.i("cocos2d-x debug info", Thread.currentThread().getId() + " " + "distributeDataToOthers len =" + bytes.length + ",recLen =" + len);
			//}
			clientManager.distributeDataToOthers(bytes);
			return;
		}

		Log.i("cocos2d-x debug info", Thread.currentThread().getId() + " " + "distributeDataToOthers clientManager is null len =" + bytes.length + ",recLen =" + len);
	}

	/**
	 * 客户端发送，要求服务器处理转发,调用这个接口后，服务器端回回调onHandleDistribute
	 * 
	 * @param bytes
	 */
	public static void handleDistribute(byte[] bytes) {
		if (clientManager != null) {
			Log.i("cocos2d-x debug info", Thread.currentThread().getId() + " " + "handleDistribute len =" + bytes.length);
			clientManager.sendData(bytes);
			return;
		}
		Log.i("cocos2d-x debug info", "handleDistribute len =" + bytes.length);
	}

	/**
	 * 服务器接收到需要处理的数据，处理完成后调用distribute分发
	 * 
	 * @param clientInfo
	 */
	public static void onHandleDistribute(byte[] bytes) {
		Log.i("cocos2d-x debug info", Thread.currentThread().getId() + " " + "onHandleDistribute len =" + bytes.length);
		JniHelper.onHandleDistribute(bytes, bytes.length);

	}

	/**
	 * 服务器处理完数据后分发客户端数据
	 * 
	 * @param bytes
	 */
	public static void distribute(byte[] bytes) {
		if (shareCircleManager != null) {
			Log.i("cocos2d-x debug info", Thread.currentThread().getId() + " " + "shareCircleManager len =" + bytes.length);
			shareCircleManager.distributeDataToAllClients(bytes);

		}
		Log.i("cocos2d-x debug info", "shareCircleManager len =" + bytes.length);
	}

	// /**
	// * 当客户端收到服务端自动分发的数据时回调
	// */
	// public static void onAutoDistributeReceived(byte[] bytes)
	// {
	// JniHelper.onAutoDistributeReceived(bytes);
	// }
	/**
	 * 当客户端收到服务端处理后分发的数据时回调
	 */
	public static void onHandleDistributeReceived(byte[] bytes) {
		Log.i("cocos2d-x debug info", Thread.currentThread().getId() + " " + "onHandleDistributeReceived len =" + bytes.length);
		JniHelper.onHandleDistributeReceived(bytes, bytes.length);
	}

	public static void getMyInfo() {
		if (clientManager != null) {
			ClientInfo clientInfo = clientManager.getMyInfo();

			JsonBuilder build = new JsonBuilder();

			String uid = clientInfo.uid;
			String name = clientInfo.name;
			int iconIdx = clientInfo.headIconIndex;
			String ip = clientInfo.ip;

			build.put(JniHelper.JNI_ID, JniHelper.JNI_RID_GETMYINFO);
			build.put(JNI_EGG_UID, uid);
			build.put(JNI_EGG_USER_NAME, name);
			build.put(JNI_EGG_ICONID, iconIdx);
			build.put(JNI_EGG_IP, ip);
			JniHelper.execCallback(build.toJsonString());
		}
	}

	public static void getOtherInfo() {
		if (clientManager != null) {
			clientManager.getAllClients();
		}
	}

	public static void disconnect(boolean b)
	{
		
		if (clientManager != null) {
			clientManager.disconnect(b);
			clientManager = null;
		}
		
//		if (isCreateShared) {
//
//			DefaultServiceManager.getInstance(HSBalloon_S3_a.getInstance()).destroyShareCircle();
//		} else {
//			
//		}
		
	}

	public static void reconnect() {
		if (clientManager != null) {
			clientManager.reConnect(5);
		}
	}

//	public static void onClientDisconnected() {
////		if (isCreateShared) {
//////			if (shareCircleManager != null) {
//////				shareCircleManager.destroyServer();
//////			}
////			DefaultServiceManager.getInstance(HSBalloon_S3_a.getInstance()).destroyShareCircle();
////		} else {
////			restoreWifiState();
////		}
////		clientManager = null;
//	}
	
	public static void stopSearchingShareCircle()
	{
		Message msg = Message.obtain(HSBalloon_S3_a.mhandler, HSBalloon_S3_a.STOPSEARCHINGSHARECIRCLE, null);
		
		HSBalloon_S3_a.mhandler.sendMessage(msg);
	}

	public static void restoreWifiState() {
		DefaultServiceManager.getInstance(HSBalloon_S3_a.getInstance()).restoreWifiState(new OperationResult() {

			@Override
			public void onSucceed() {
				JsonBuilder build = new JsonBuilder();
				build.put(JniHelper.JNI_ID, JniHelper.JNI_RID_RESTORE_WIFI);
				build.put(JNI_EGG_WIFI_RESTORE, 0);
				JniHelper.execCallback(build.toJsonString());
				
				if(JniEggshell.IsKill)
				{
					android.os.Process.killProcess(android.os.Process.myPid());
				}
			}

			@Override
			public void onFailed()
			{
				JsonBuilder build = new JsonBuilder();
				build.put(JniHelper.JNI_ID, JniHelper.JNI_RID_RESTORE_WIFI);
				build.put(JNI_EGG_WIFI_RESTORE, 1);
				JniHelper.execCallback(build.toJsonString());
				
				if(JniEggshell.IsKill)
				{
					android.os.Process.killProcess(android.os.Process.myPid());
				}
			}
		});
	}
	
	public static void ShellExcption(String excption)
	{
		JsonBuilder build = new JsonBuilder();
		build.put(JniHelper.JNI_ID, JniHelper.JNI_RID_EXCPTION);
		for (String s : Excptions) 
		{
			if(s.equals(excption))
			{
				build.put(s, 1);
			}else{
				build.put(s, 0);
			}
		}
		JniHelper.execCallback(build.toJsonString());
	}
	
	public static void Stop()
	{
		isCreateShared = false;
		shareCircleManager = null;
		
		restoreWifiState();
		
	}

}





















