import java.io.*;
import java.net.*;

class TCPClient {
public static void main(String argv[]) throws Exception
{

String sentence;
String modifiedSentence;

BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
System.out.println("Write a message and send it to server");
sentence = inFromUser.readLine();

Socket clientSocket = new Socket("localhost", 1024);
DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
outToServer.writeBytes(sentence + '\n');

BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
modifiedSentence = inFromServer.readLine();
System.out.println("FROM SERVER: " + modifiedSentence);

clientSocket.close();
	}
}
