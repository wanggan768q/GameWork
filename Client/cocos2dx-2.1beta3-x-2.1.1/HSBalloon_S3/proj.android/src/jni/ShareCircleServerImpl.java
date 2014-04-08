package jni;


import com.chainton.dankeshare.ShareCircleServer;
import com.chainton.dankeshare.data.ClientInfo;
import com.letu.baselib.util.JsonBuilder;

public class ShareCircleServerImpl extends  ShareCircleServer
{

	public ShareCircleServerImpl()
	{
		
	}
	
	@Override
	protected void onClientRequestSynchronize(ClientInfo arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	protected void onDataReceived(ClientInfo arg0, byte[] arg1) {
		// TODO Auto-generated method stub
		
	}
	
	@Override
	protected void onServerStopped() {
		// TODO Auto-generated method stub
		super.onServerStopped();
		
		JniEggshell.restoreWifiState();
	}

	// 另外一个人退出
	@Override
	protected void onAcceptedClientExited(ClientInfo arg0) {
		
		super.onAcceptedClientExited(arg0);
//		
//		JsonBuilder build = new JsonBuilder();
//		build.put(JniHelper.JNI_ID, JniHelper.JNI_ID_SESSIONCLOSE);
//		build.put(JniEggshell.JNI_EGG_USER_NAME, arg0.name);
//		JniHelper.execCallback(build.toJsonString());

	}
	
}