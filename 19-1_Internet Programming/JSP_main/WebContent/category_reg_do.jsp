<%@ page language="java" contentType="text/html; charset=UTF-8" import="java.sql.*"%>

<%
request.setCharacterEncoding("utf-8");

Class.forName("org.mariadb.jdbc.Driver");

String DB_URL = "jdbc:mariadb://localhost:3306/newsmgt?useSSL=false";
String name_1 = request.getParameter("categoryName_1");
String name_2 = request.getParameter("categoryName_2");
int code = Integer.parseInt(request.getParameter("categoryCode"));

try{
	Connection con = DriverManager.getConnection(DB_URL, "admin", "1234");
	String sql = "INSERT INTO category(code ,name_1, name_2) VALUES(?, ?, ?)";
	
	PreparedStatement pstmt = con.prepareStatement(sql);
	pstmt.setInt(1, code);
	pstmt.setString(2, name_1);
	pstmt.setString(3, name_2);
	
	pstmt.executeUpdate();
	
	pstmt.close();
	con.close();
}catch(SQLException e){
	out.println(e);
	return;
}

response.sendRedirect("category.jsp");

%>
