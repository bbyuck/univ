<%@ page language="java" contentType="text/html; charset=UTF-8"
    import="java.sql.*"%>
<%
request.setCharacterEncoding("utf-8");

Class.forName("org.mariadb.jdbc.Driver");

String DB_URL = "jdbc:mariadb://localhost:3306/newsmgt?useSSL=false";
String name_1 = request.getParameter("categoryName_1");
String name_2 = request.getParameter("categoryName_2");
int code = Integer.parseInt(request.getParameter("categoryCode"));

try{
	Connection con = DriverManager.getConnection(DB_URL, "admin", "1234");
	String sql = "UPDATE category SET name_1=?, name_2=? WHERE code=?";
	
	PreparedStatement pstmt = con.prepareStatement(sql);
	
	pstmt.setString(1, name_1);
	pstmt.setString(2, name_2);
	pstmt.setInt(3, code);
	
	pstmt.executeUpdate();
	
	pstmt.close();
	con.close();
}catch(SQLException e){
	out.println(e);
	return;
}

response.sendRedirect("category.jsp");

%>