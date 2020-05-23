<%@ page language="java" contentType="text/html; charset=UTF-8"
    import="java.sql.*, java.io.*"
    %>
<%
request.setCharacterEncoding("utf-8");

Class.forName("org.mariadb.jdbc.Driver");

String DB_URL = "jdbc:mariadb://localhost:3306/newsmgt?useSSL=false";

int id = Integer.parseInt(request.getParameter("id"));


try{
	ServletContext context = getServletContext();
	String realFolder = context.getRealPath("upload");
	
	
	Connection con = DriverManager.getConnection(DB_URL, "admin", "1234");
	
	
	String sql = "SELECT imgName, thumb FROM article WHERE id=?";
	PreparedStatement pstmt = con.prepareStatement(sql);
	
	pstmt.setInt(1, id);
	
	ResultSet rs = pstmt.executeQuery();
	
	rs.next();
	
	String imgName = rs.getString("imgName");
	String thumb = rs.getString("thumb");
	
	File image = new File(realFolder + "\\" + imgName);
	File thumbFile = new File(realFolder + "\\" + thumb);
	
	image.delete();										// db에서 제거하기전 기사 본문이미지 삭제
	thumbFile.delete();									// 썸네일 파일 삭제
	
	sql = "DELETE FROM article WHERE id=?";
	
	pstmt = con.prepareStatement(sql);
	pstmt.setInt(1, id);
	pstmt.executeUpdate();
	
	rs.close();
	pstmt.close();
	con.close();
}catch(SQLException e){
	out.println(e);
	return;
}catch(Exception e){
	out.println(e);
	return;
}

response.sendRedirect("article.jsp");

%>