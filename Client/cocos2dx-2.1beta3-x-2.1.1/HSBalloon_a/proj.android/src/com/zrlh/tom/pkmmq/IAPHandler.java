package com.zrlh.tom.pkmmq;

import android.os.Handler;
import android.os.Message;

public class IAPHandler extends Handler {
	public static IAPHandler handler;

	public static final int INIT_FINISH = 10000;
	public static final int BILL_FINISH = 10001;
	public static final int QUERY_FINISH = 10002;
	public static final int UNSUB_FINISH = 10003;

	public static IAPHandler sharedHandler() {
		if (handler == null) {
			handler = new IAPHandler();
		}
		return handler;
	} 
	
	public void handleMessage(Message msg) {
		super.handleMessage(msg);
		int what = msg.what;
		switch (what) {
		case INIT_FINISH:
			break;
		default:
			break;
		}
	}

}
