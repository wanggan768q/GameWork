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

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Activity;
import android.os.Bundle;
import android.widget.Toast;

public class HSBalloon_S3_a extends Cocos2dxActivity{

	private static Activity instance;
	
	public static Activity getInstance()
	{
		return instance;
	}
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		instance = this;
	}
	
    static {
    	//System.loadLibrary("iconv");
    	//System.loadLibrary("protobuf");
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
}
