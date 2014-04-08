package jni;

import com.LeTu.Main.HSBalloon_S3_a;
import com.chainton.dankeshare.ShareCircleClient;
import com.chainton.dankeshare.data.ClientInfo;
import com.chainton.dankeshare.service.DefaultServiceManager;
import com.letu.baselib.util.JsonBuilder;

public  class ShareCircleClientImpl extends  ShareCircleClient
{

	public ShareCircleClientImpl()
	{
		
	}
	
	@Override
	protected void onDataReceived(byte[] arg0) {
		// TODO Auto-generated method stub
		JniEggshell.onHandleDistributeReceived(arg0);
	}

	@Override
	protected void onDisconnectedByException() {
		// TODO Auto-generated method stub

		if (JniEggshell.isCreateShared) {

			DefaultServiceManager.getInstance(HSBalloon_S3_a.getInstance()).destroyShareCircle();
		} 
		JsonBuilder build = new JsonBuilder();
		build.put(JniHelper.JNI_ID, JniHelper.JNI_ID_SESSIONCLOSE);
		build.put(JniEggshell.JNI_EGG_USER_NAME, this.myInfo.name);
		JniHelper.execCallback(build.toJsonString());
	}

	//
	@Override
	protected void onDisconnectedByServer() {
		// TODO Auto-generated method stub
		if (JniEggshell.isCreateShared) {

			DefaultServiceManager.getInstance(HSBalloon_S3_a.getInstance()).destroyShareCircle();
		}
		JsonBuilder build = new JsonBuilder();
		build.put(JniHelper.JNI_ID, JniHelper.JNI_ID_ONSERVER_EXIT);
		JniHelper.execCallback(build.toJsonString());
	}

	@Override
	protected void onDisconnectedByUser() {
		// TODO Auto-generated method stub

		if (JniEggshell.isCreateShared) {

			DefaultServiceManager.getInstance(HSBalloon_S3_a.getInstance()).destroyShareCircle();
		}
		JsonBuilder build = new JsonBuilder();
		build.put(JniHelper.JNI_ID, JniHelper.JNI_ID_WIFI_CLOSE);
		build.put(JniEggshell.JNI_EGG_WIFI_CLOSE, 0);
		JniHelper.execCallback(build.toJsonString());
	}

	@Override
	protected void onJoinRequestAccepted() {
		// TODO Auto-generated method stub
		JniEggshell.entrySuccess();
	}

	@Override
	protected void onJoinRequestRejected() {
		// TODO Auto-generated method stub
		HSBalloon_S3_a.showToast("房间已经人数已满");
		JniEggshell.entryFail(JniEggshell.JNI_EGG_ROOM_ENOUGH);
	}

	@Override
	protected void onKickedOff() {
		// TODO Auto-generated method stub
		
	}

	@Override
	protected void onOtherClientExited(ClientInfo arg0) {
		// TODO Auto-generated method stub
		JsonBuilder build = new JsonBuilder();
		build.put(JniHelper.JNI_ID, JniHelper.JNI_ID_ONCLIENT_EXIT);
		JniHelper.execCallback(build.toJsonString());
	}

	@Override
	protected void onOtherClientJoined(ClientInfo arg0) {
		// TODO Auto-generated method stub
		JsonBuilder build = new JsonBuilder();

		String uid = arg0.uid;
		String name = arg0.name;
		int iconIdx = arg0.headIconIndex;
		String ip = arg0.ip;

		build.put(JniHelper.JNI_ID, JniHelper.JNI_RID_GETOTHERINFO);
		build.put(JniEggshell.JNI_EGG_UID, uid);
		build.put(JniEggshell.JNI_EGG_USER_NAME, name);
		build.put(JniEggshell.JNI_EGG_ICONID, iconIdx);
		build.put(JniEggshell.JNI_EGG_IP, ip);
		JniHelper.execCallback(build.toJsonString());
	}
	
}

