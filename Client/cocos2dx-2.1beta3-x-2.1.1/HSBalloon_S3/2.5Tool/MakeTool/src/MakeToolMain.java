import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Properties;
import java.util.Vector;

import javax.xml.crypto.Data;

public class MakeToolMain {

	//static Properties properties = null;
	
	public static String args0 ="/Users/yangzheng/Work/cocos2dx/HSBalloon_S3/Classes/";
	public static String args1 ="/Users/yangzheng/Work/cocos2dx/HSBalloon_S3/proj.android/jni/Android.mk";
	public static String args2 ="../../Classes/";
	
	public static void main(String[] args) 
	{	
		args0 = args[0];
		args1 = args[1];
		args2 = args[2];
		
		System.out.println(args[0]);
		System.out.println(args[1]);
		System.out.println(args[2]);
		
		
		MakeToolMain make = new MakeToolMain();
		//make.properties = make.getProperties();
		make.init();
	}

	public void mk(BufferedWriter output,Vector<String> allFileList_Cpp,Vector<String> folderList) throws IOException{
		
		Vector<String> pbcppList = new Vector<String>();
		Vector<String> cppList = new Vector<String>();
		
		for(int i = 0; i < allFileList_Cpp.size(); ++i) {
				String tempFileName = allFileList_Cpp.get(i);
				if(tempFileName.endsWith(".pb.cpp")){
					pbcppList.add(tempFileName);
				}else if(tempFileName.endsWith("cpp")){
					cppList.add(tempFileName);
				}
				else if(tempFileName.endsWith(".c"))
				{
					cppList.add(tempFileName);
				}
			
		}
		
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");//�������ڸ�ʽ
		
		output.write("LOCAL_PATH := $(call my-dir)\n");
		output.write("include $(CLEAR_VARS)\n");
		output.write("LOCAL_MODULE := game_shared\n");
		output.write("LOCAL_MODULE_FILENAME := libgame\n");
		output.write("\n");
		output.write("\n");
		output.write("################################################################ \n");
		output.write("#" + "\t\t Ambition  [FileCount:" + pbcppList.size() + cppList.size() + "]\t\t" + "Time:\t" + df.format(new Date()) + "\n");
		output.write("################################################################ \n");
		output.write("\n");
		output.write("\n");
		output.write("LOCAL_SRC_FILES := Main/main.cpp \\\n");
		output.write("Umeng/MobClickCpp.cpp \\\n");
		
		//String prefixStr = properties.getProperty("prefixStr");	
		String prefixStr = args2;
		
		for(int i=0;i<pbcppList.size();++i){
			System.out.println(pbcppList.get(i));
			output.write(prefixStr + pbcppList.get(i) +" \\\n");
		}
		for(int i=0;i<cppList.size();++i){
			System.out.println(cppList.get(i));
			String tempPrefixStr = " \\\n";
			if(i == cppList.size() - 1){
				tempPrefixStr = "\n";
			}
			output.write(prefixStr + cppList.get(i) + tempPrefixStr);
		}
		
		output.write("\n");
		output.write("\n");
		
		output.write("LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes" + " \\\n");
		output.write("					$(LOCAL_PATH)/../../../cocos2dx/jsoncpp/include" + " \\\n");
		output.write("					$(LOCAL_PATH)/../../../cocos2dx/jsoncpp/include/json" + " \\\n");
		output.write("					$(LOCAL_PATH)/../../../cocos2dx/google" + " \\\n");
//		output.write("					  $(LOCAL_PATH)/../../../extensions" + " \\\n");
//		output.write("					  $(LOCAL_PATH)/../../../extensions/physics_nodes" + " \\\n");
//		output.write("					  $(LOCAL_PATH)/../../../extensions/CCBReader" + " \\\n");
//		output.write("					  $(LOCAL_PATH)/../../../extensions/GUI" + " \\\n");
//		output.write("					  $(LOCAL_PATH)/../../../extensions/LocalStorage" + " \\\n");
//		output.write("					  $(LOCAL_PATH)/../../../extensions/network" + " \\\n");
//		output.write("					  $(LOCAL_PATH)/../../../extensions/network" + " \\\n");
		for(int i=0;i<folderList.size();++i)
		{
			String end = " \\\n";
			if(i == folderList.size() - 1)
			{
				end = " \n";
			}
			String folder = folderList.get(i);			
			output.write("					  $(LOCAL_PATH)/../../Classes/" + folder + end);
		}
		
		
		output.write("\n");
		output.write("\n");
		
		output.write("LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static protobuf_static jsoncpp_static" + " \n");
		output.write("LOCAL_CFLAGS += -std=c++11"+"\n");
		output.write("\n");
		output.write("\n");
		
		output.write("::LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../libs/libprotobuffull) -lprotobuf" + "\n");
		
		
		output.write("\n");
		output.write("\n");
		
		output.write("include $(BUILD_SHARED_LIBRARY)\n");
		
		output.write("include $(LOCAL_PATH)/prebuilt/Android.mk\n");
		output.write("include $(LOCAL_PATH)/AndroidMMcasdkjni.mk\n");
		output.write("include $(LOCAL_PATH)/AndroidMMidentifyapp.mk\n");
		
		output.write("\n");
		output.write("\n");
		
		output.write("$(call import-module,cocos2dx/jsoncpp)" + " \\\n");
		output.write("$(call import-module,cocos2dx/google)" + " \\\n");
		output.write("$(call import-module,CocosDenshion/android)" + " \\\n");
		output.write("$(call import-module,cocos2dx)" + " \\\n");
		output.write("$(call import-module,extensions)" + "\n");
		output.write("\n");
		
		
		cppList = null;
		pbcppList = null;
	}
	
	/*public void mk1(BufferedWriter output,Vector<String> allFileList_Cpp,Vector<String> folderList) throws IOException{
		
		Vector<String> pbcppList = new Vector<String>();
		Vector<String> cppList = new Vector<String>();
		
		for(int i = 0; i < allFileList_Cpp.size(); ++i) {
				String tempFileName = allFileList_Cpp.get(i);
				if(tempFileName.endsWith(".pb.cpp")){
					pbcppList.add(tempFileName);
				}else if(tempFileName.endsWith("cpp")){
					cppList.add(tempFileName);
				}
			
		}
		
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");//�������ڸ�ʽ
		
		output.write("LOCAL_PATH := $(call my-dir)\n");
		output.write("include $(CLEAR_VARS)\n");
		output.write("LOCAL_MODULE := game\n");
		//output.write("LOCAL_CFLAGS += -fexceptions\n");
		output.write("\n");
		output.write("\n");
		output.write("################################################################ \n");
		output.write("#" + "\t\t Ambition  [FileCount:" + pbcppList.size() + cppList.size() + "]\t\t" + "Time:\t" + df.format(new Date()) + "\n");
		output.write("################################################################ \n");
		output.write("\n");
		output.write("\n");
		output.write("LOCAL_SRC_FILES := main.cpp \\\n");
		
		String prefixStr = properties.getProperty("prefixStr");	
		
		
		for(int i=0;i<pbcppList.size();++i){
			System.out.println(pbcppList.get(i));
			output.write(prefixStr + pbcppList.get(i) +" \\\n");
		}
		for(int i=0;i<cppList.size();++i){
			System.out.println(cppList.get(i));
			String tempPrefixStr = " \\\n";
			if(i == cppList.size() - 1){
				tempPrefixStr = "\n";
			}
			output.write(prefixStr + cppList.get(i) + tempPrefixStr);
		}
		
		output.write("\n");
		output.write("\n");
		
		output.write("LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../cocos2dx" + " \\\n");
		output.write("					  $(LOCAL_PATH)/../../../../cocos2dx/platform" + " \\\n");
		output.write("					  $(LOCAL_PATH)/../../../../cocos2dx/include" + " \\\n");
		output.write("					  $(LOCAL_PATH)/../../../../CocosDenshion/include" + " \\\n");
		output.write("					  $(LOCAL_PATH)/../../../../cocos2dx/lua_support" + " \\\n");
		for(int i=0;i<folderList.size();++i)
		{
			output.write("					  $(LOCAL_PATH)/../Classes/" + folderList.get(i) + " \\\n");
		}
		output.write("					  $(LOCAL_PATH)/../Classes");
		
		output.write("\n");
		output.write("\n");
		
		output.write("LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../../libs/armeabi)" + " \\\n");
		output.write("                -lcocos2d -llog -lcocosdenshion" + " \\\n");
		output.write("                -L$(call host-path, $(LOCAL_PATH)/../../../../cocos2dx/platform/third_party/android/libraries/armeabi-v7a) -liconv" + " \\\n");
		output.write("                -L$(call host-path, $(LOCAL_PATH)/../../libs/libprotobuffull) -lprotobuf" + " \\\n");
		output.write("                -lGLESv2" + " \\\n");
		output.write("                -lGLESv1_CM");
		
		output.write("\n");
		output.write("\n");
		
		output.write("-include $(BUILD_SHARED_LIBRARY)");
		
		
		cppList = null;
		pbcppList = null;
	}*/

	public static String sourceFileName = "";
	public static String mkFilePath = "";
	public void init() {
//		Properties properties = getProperties();
//		sourceFileName = properties.getProperty("source");
		sourceFileName =args0;
		mkFilePath = args1;
		
		System.out.println("******************************************************");
		System.out.println("MakeToolInfo");
		System.out.println(sourceFileName);
		System.out.println(mkFilePath);
		System.out.println("HSBalloon_S3_a");
		System.out.println("******************************************************");

		File fileRead = new File(sourceFileName);
		File[] fileList = fileRead.listFiles();

		File file = new File(mkFilePath);
		if (file.exists()) {
			file.delete();
		}
		// try {
		// file.createNewFile();
		// BufferedWriter output = new BufferedWriter(new FileWriter(file));
		// this.mk(output, fileList);
		// fileRead = null;
		// output.close();
		// } catch (IOException e) {
		// e.printStackTrace();
		// }
		try {
			file.createNewFile();
			BufferedWriter output = new BufferedWriter(new FileWriter(file));
			Vector<String> allFileList_Cpp = new Vector<String>();
			Vector<String> folderList = new Vector<String>();
			this.GetFileList(allFileList_Cpp,folderList ,fileList, "");
			this.mk(output, allFileList_Cpp,folderList);
			fileRead = null;
			output.close();
		} catch (IOException e) {

		}
	}

	public void GetFileList(Vector<String> outList,Vector<String> folderList, File[] fileList,
			String folderName) {
		for (int i = 0; i < fileList.length; ++i) {
			if (!fileList[i].isDirectory()) {
				String fileName = folderName + fileList[i].getName();
				if(fileName.endsWith(".cpp") 
						|| fileName.endsWith(".h")
						){
					outList.add(fileName);
				}				
			} else {
				String path = fileList[i].getAbsolutePath();
				int index = path.indexOf(sourceFileName);
				path = path.substring(sourceFileName.length(), path.length());
				System.out.println(path);
				path = path.replaceAll("\\\\", "/");
				String folder = path;
				if(!folder.equals("doc") 
						&& !folder.equals("libs") 
						&& !folder.equals("Resources")
						&& !folder.equals("WinMain")
						&& !folder.equals("Debug.win32")
						&& !folder.equals("Release.win32")
						&& !folder.equals(".svn") 
						){
					folderList.add(folder);
					this.GetFileList(outList, folderList,fileList[i].getAbsoluteFile()
							.listFiles(), folder + "/");
				}
				
			}
		}
	}

//	public Properties getProperties() {
//		InputStream in = "a".getClass().getResourceAsStream(
//				"/project.properties");
//		Properties p = new Properties();
//		try {
//			p.load(in);
//			in.close();
//		} catch (IOException e) {
//			e.printStackTrace();
//		}
//		return p;
//	}

}
