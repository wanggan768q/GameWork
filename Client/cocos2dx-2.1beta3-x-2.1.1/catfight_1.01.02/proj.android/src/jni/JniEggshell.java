package jni;
import org.json.JSONException;
import org.json.JSONObject;
import com.letu.util.JsonBuilder;

public class JniEggshell {
	
	public static final String JNI_EGG_RESULT = "JNI_EGG_RESULT";
	
	public static void createShared(JSONObject json) throws JSONException
	{
		//String roomName = json.getString("JNI_EGGS_ROOMNAME");
		String userName = json.getString("JNI_EGGS_USERName");
		
//		WifiApShareCircleInfo circleInfo = new WifiApShareCircleInfo();
//		
//		circleInfo.setName(userName);
//		
//		//circleInfo
//		
//		ClientInfo selfInfo = createSelfInfo(userName);
//		
//		final long initTime = System.currentTimeMillis();
//		DefaultServiceManager.getInstance(HSBalloon_S3_a.getInstance()).createShareCircle(circleInfo, selfInfo, new CreateShareCircleCallback() {
//
//			@Override
//			public void onShareCircleCreateSuccess(ShareCircleManager shareCircleManager) 
//			{
//				if (System.currentTimeMillis() - initTime <= 1000) 
//				{
//					new Handler().postDelayed(new Runnable() {
//
//						@Override
//						public void run() 
//						{
//							Log.v("cocos2d-x debug info", "onShareCircleCreateSuccess 1");
//							createHotWifiSuccess();
//							//return "";
//						}
//					}, 1000);
//				} 
//				else 
//				{
//					Log.v("cocos2d-x debug info", "onShareCircleCreateSuccess 2");
//					createHotWifiSuccess();
//					//return "";
//				}
//			}
//
//			@Override
//			public void onShareCircleCreateFailed() 
//			{
//				Toast.makeText(HSBalloon_S3_a.getInstance(), com.LeTu.Main.R.string.create_share_circle_failed, Toast.LENGTH_SHORT).show();
//				createHotWifiFail();
//				//return "";
//			}
//		});
	}
	
//	private static ClientInfo createSelfInfo(String name) 
//	{
//		ClientInfo selfInfo = new ClientInfo();
//		selfInfo.setName(name);
//		selfInfo.setHeadIconIndex(1);
//		//selfInfo
//		
//		return selfInfo;
//	}
	
	private static void createHotWifiSuccess() 
	{
		JsonBuilder build = new JsonBuilder();
		build.put(JniHelper.JNI_ID, JniHelper.JNI_RID_CREATESHARED);
		build.put(JNI_EGG_RESULT, 0);
		JniHelper.execCallback(build.toJsonString());
	}
	
	private static void createHotWifiFail()
	{
		JsonBuilder build = new JsonBuilder();
		build.put(JniHelper.JNI_ID, JniHelper.JNI_RID_CREATESHARED);
		build.put(JNI_EGG_RESULT, 1);
		JniHelper.execCallback(build.toJsonString());
	}
	
	
	public static void entryShared()
	{
		
	}
	
	public static void SerrchShardList()
	{
//			DefaultServiceManager.getInstance(HSBalloon_S3_a.getInstance()).searchShareCircle(new SearchCircleCallback() {
//			@Override
//			public void onSearchTimeout()
//			{
//				// TODO Auto-generated method stub
//				Toast.makeText(HSBalloon_S3_a.getInstance(), com.LeTu.Main.R.string.create_share_circle_failed, Toast.LENGTH_SHORT).show();
//				
//				JsonBuilder build = new JsonBuilder();
//				//build.put(name, value);
//				
//			}
//			
//			@Override
//			public void onSearchResult(List<ShareCircleInfo> lists) 
//			{
//				
//				for(int i =0; i < lists.size(); i++)
//				{
//					ShareCircleInfo shareCircleInfo = lists.get(i);
//					
//				}
//				
//			}
//		});
	}
	
	
	
	
	
}
