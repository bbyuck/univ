package myData;

public class ArticleData {
	private String ctgr;
	private String reg_state;
	private String coverageDate;
	private String reporterName;
	private String reporterEmail;
	private String title;
	private String content;
	private String lastModifiedDay;

	public ArticleData() {
		ctgr = "";
		reg_state = "";
		coverageDate = "";
		reporterName = "";
		reporterEmail = "";
		title = "";
		content = "";
		lastModifiedDay = "";
	}

	public String getCtgr() {
		return ctgr;
	}

	public String getReg_state() {
		return reg_state;
	}

	public String getCoverageDate() {
		return coverageDate;
	}

	public String getReporterName() {
		return reporterName;
	}

	public String getReporterEmail() {
		return reporterEmail;
	}

	public String getTitle() {
		return title;
	}

	public String getContent() {
		return content;
	}

	public String getLastModifiedDay() {
		return lastModifiedDay;
	}

	public void setCtgr(String ctgr) {
		this.ctgr = ctgr;
	}

	public void setReg_state(String reg_state) {
		this.reg_state = reg_state;
	}

	public void setCoverageDate(String coverageDate) {
		this.coverageDate = coverageDate;
	}

	public void setReporterName(String reporterName) {
		this.reporterName = reporterName;
	}

	public void setReporterEmail(String reporterEmail) {
		this.reporterEmail = reporterEmail;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public void setContent(String content) {
		this.content = content;
	}

	public void setLastModifiedDay(String lastModifiedDay) {
		this.lastModifiedDay = lastModifiedDay;
	}
	
}
