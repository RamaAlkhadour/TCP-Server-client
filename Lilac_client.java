import java.net.*;
import java.io.*;
import java.util.Scanner;

class Lilac_client {
public static void main(String argv[]) throws Exception 
{

	Socket clientSocket = new Socket("localhost", 1024);
	InputStream input =clientSocket.getInputStream();
	OutputStream output=clientSocket.getOutputStream();
	BufferedReader bufread=new BufferedReader(new InputStreamReader(input));
	BufferedWriter bufwrite=new BufferedWriter(new OutputStreamWriter(output));
	Scanner scan=new Scanner(System.in);
	System.out.println("Write a message and send it to server");
	String message=scan.next();
	bufwrite.write(message+" \n");
	bufwrite.flush();
	String s= bufread.readLine();
	System.out.println("From Server  :"+s);
	clientSocket.close();
	bufread.close();
	bufwrite.close();
	input.close();
	output.close();
	
	}
}
