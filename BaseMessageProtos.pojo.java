public class BaseMessageProtos {
	enum LoginResultEnum {
		LoginResultSuccess,
		LoginResultFail,
	}

	public static class LoginMessage {
		private java.lang.String servername;
		private int servertype;
		private int port;
		private java.lang.String host;
		private int id;
		public void setServername(java.lang.String servername) { this.servername=servername; }
		public java.lang.String getServername() { return this.servername; }
		public void setServertype(int servertype) { this.servertype=servertype; }
		public int getServertype() { return this.servertype; }
		public void setPort(int port) { this.port=port; }
		public int getPort() { return this.port; }
		public void setHost(java.lang.String host) { this.host=host; }
		public java.lang.String getHost() { return this.host; }
		public void setId(int id) { this.id=id; }
		public int getId() { return this.id; }
	}

	public static class LoginResult {
		private LoginResultEnum result;
		public void setResult(LoginResultEnum result) { this.result=result; }
		public LoginResultEnum getResult() { return this.result; }
	}

	public static class SuperServerLoginResult {
		private LoginResultEnum result;
		private java.lang.String ip;
		public void setResult(LoginResultEnum result) { this.result=result; }
		public LoginResultEnum getResult() { return this.result; }
		public void setIp(java.lang.String ip) { this.ip=ip; }
		public java.lang.String getIp() { return this.ip; }
	}

	public static class RequestServerIpInfo {
	}

	public static class ServerIpInfo {
		private int id;
		private java.lang.String name;
		private int type;
		private java.lang.String host;
		private int port;
		public void setId(int id) { this.id=id; }
		public int getId() { return this.id; }
		public void setName(java.lang.String name) { this.name=name; }
		public java.lang.String getName() { return this.name; }
		public void setType(int type) { this.type=type; }
		public int getType() { return this.type; }
		public void setHost(java.lang.String host) { this.host=host; }
		public java.lang.String getHost() { return this.host; }
		public void setPort(int port) { this.port=port; }
		public int getPort() { return this.port; }
	}

	public static class ReturnServerIpInfo {
		private int id;
		private ServerIpInfo connectToMe;
		private ServerIpInfo meToConnect;
		public void setId(int id) { this.id=id; }
		public int getId() { return this.id; }
		public void setConnectToMe(ServerIpInfo connectToMe) { this.connectToMe=connectToMe; }
		public ServerIpInfo getConnectToMe() { return this.connectToMe; }
		public void setMeToConnect(ServerIpInfo meToConnect) { this.meToConnect=meToConnect; }
		public ServerIpInfo getMeToConnect() { return this.meToConnect; }
	}

	public static class NotifyServerStartUp {
		private int id;
		public void setId(int id) { this.id=id; }
		public int getId() { return this.id; }
	}

	public static class AddOrder {
		private java.lang.String msg;
		private NotifyServerStartUp nssu;
		public void setMsg(java.lang.String msg) { this.msg=msg; }
		public java.lang.String getMsg() { return this.msg; }
		public void setNssu(NotifyServerStartUp nssu) { this.nssu=nssu; }
		public NotifyServerStartUp getNssu() { return this.nssu; }
	}

	public static class RpcTestRequest {
		private java.lang.String requestMsg;
		public void setRequestMsg(java.lang.String requestMsg) { this.requestMsg=requestMsg; }
		public java.lang.String getRequestMsg() { return this.requestMsg; }
	}

	public static class RpcTestResponse {
		private java.lang.String responseMsg;
		public void setResponseMsg(java.lang.String responseMsg) { this.responseMsg=responseMsg; }
		public java.lang.String getResponseMsg() { return this.responseMsg; }
	}

	public static class BaseMessage {
		private int cmd;
		private int param;
		private int test;
		public void setCmd(int cmd) { this.cmd=cmd; }
		public int getCmd() { return this.cmd; }
		public void setParam(int param) { this.param=param; }
		public int getParam() { return this.param; }
		public void setTest(int test) { this.test=test; }
		public int getTest() { return this.test; }
	}

}
