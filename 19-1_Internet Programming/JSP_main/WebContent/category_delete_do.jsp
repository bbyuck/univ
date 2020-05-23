<%@ page language="java" contentType="text/html; charset=UTF-8"
    import="java.sql.*"%>
<%
request.setCharacterEncoding("utf-8");

Class.forName("org.mariadb.jdbc.Driver");

String DB_URL = "jdbc:mariadb://localhost:3306/newsmgt?useSSL=false";

int code = Integer.parseInt(request.getParameter("code"));

try{
	Connection con = DriverManager.getConnection(DB_URL, "admin", "1234");
	String sql = "SELECT * FROM category WHERE code=?";		// 삭제할 분류 id 가져옴
	
	PreparedStatement pstmt = con.prepareStatement(sql);
	
	pstmt.setInt(1, code);
	
	ResultSet rs = pstmt.executeQuery();
	
	rs.next();
	
	String full_category = rs.getString("name_1") + " - " + rs.getString("name_2");		//분류1 + 분류2로 article table에 저장된 형식으로바꿈
	
	sql = "UPDATE article SET art_ctgr='미분류' WHERE art_ctgr=?";	//분류 지정 되어있는 기사들 미분류로 변경
	pstmt = con.prepareStatement(sql);
	pstmt.setString(1, full_category);
	
	pstmt.executeUpdate();
	
	sql = "DELETE FROM category WHERE code=?";	//분류 삭제
	pstmt = con.prepareStatement(sql);
	pstmt.setInt(1, code);
	pstmt.executeUpdate();
	
	rs.close();
	pstmt.close();
	con.close();
}catch(SQLException e){
	out.println(e);
	return;
}

response.sendRedirect("category.jsp");

%>