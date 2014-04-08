package main;
import javax.swing.JOptionPane;

public class MessageBox {
	
	public static int Show(String Msg)
	{
		return JOptionPane.showConfirmDialog(null, Msg,"@About Ambition",JOptionPane.YES_NO_OPTION);
	}
	
	public static void AlwaysPrompt(String Msg)
	{
		int result = MessageBox.Show(Msg);
		while(result == 1)
		{
			result = MessageBox.Show(Msg);
		}
	}

}
