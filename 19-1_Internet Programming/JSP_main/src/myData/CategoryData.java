package myData;

public class CategoryData {
	private int categoryNum;
	private String categoryCode;
	private String categoryName;
	
	public CategoryData() {
		categoryNum = 999999;
		categoryCode = "";
		categoryName = "";
	}

	public int getCategoryNum() {
		return categoryNum;
	}

	public String getCategoryCode() {
		return categoryCode;
	}

	public String getCategoryName() {
		return categoryName;
	}

	public void setCategoryNum(int categoryNum) {
		this.categoryNum = categoryNum;
	}

	public void setCategoryCode(String categoryCode) {
		this.categoryCode = categoryCode;
	}

	public void setCategoryName(String categoryName) {
		this.categoryName = categoryName;
	}
	
	
}
