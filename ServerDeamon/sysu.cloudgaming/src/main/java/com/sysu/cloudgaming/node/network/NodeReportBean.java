package com.sysu.cloudgaming.node.network;

public class NodeReportBean {
	private String Hostname=null;
	private boolean runningFlag=false;
	private String runningApplication=null;
	private String runningApplicationVersion=null;
	private String runningApplicationPath=null;
	public String getHostname() {
		return Hostname;
	}
	public void setHostname(String hostname) {
		Hostname = hostname;
	}
	public boolean isRunningFlag() {
		return runningFlag;
	}
	public void setRunningFlag(boolean runningFlag) {
		this.runningFlag = runningFlag;
	}
	public String getRunningApplication() {
		return runningApplication;
	}
	public void setRunningApplication(String runningApplication) {
		this.runningApplication = runningApplication;
	}
	public String getRunningApplicationVersion() {
		return runningApplicationVersion;
	}
	
	public String getRunningApplicationPath() {
		return runningApplicationPath;
	}
	public void setRunningApplicationPath(String runningApplicationPath) {
		this.runningApplicationPath = runningApplicationPath;
	}
}
