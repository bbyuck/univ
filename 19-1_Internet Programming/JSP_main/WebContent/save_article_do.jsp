<%@ page language="java" contentType="text/html; charset=UTF-8"
    import="com.oreilly.servlet.*, com.oreilly.servlet.multipart.*"
    import="java.sql.*, java.io.*, java.util.*, java.text.*"
    %>
<%
request.setCharacterEncoding("utf-8");

Class.forName("org.mariadb.jdbc.Driver");
String DB_URL="jdbc:mariadb://localhost:3306/newsmgt?useSSL=false";

ServletContext context = getServletContext();
String realFolder = context.getRealPath("upload");

int maxsize = 5 * 1024 * 1024; // 이미지파일 최대크기 5MB

try{
	MultipartRequest multi = new MultipartRequest(request, realFolder, maxsize, "utf-8", new DefaultFileRenamePolicy());
	
	 java.text.SimpleDateFormat formatter = new java.text.SimpleDateFormat("yyyyMMdd");
	 String today = formatter.format(new java.util.Date()); 
	
	
	String ctgr = multi.getParameter("ctgr");
	String title = multi.getParameter("title");
	String state = multi.getParameter("regState");
	String rep_name = multi.getParameter("reporterName");
	String email = multi.getParameter("reporterEmail");
	String c_date = multi.getParameter("coverageDay");
	String content = multi.getParameter("content");

	String art_img_name = multi.getFilesystemName("art_img_name");
	String thumb_img_name = multi.getFilesystemName("thumb_img_name");

	Connection con = DriverManager.getConnection(DB_URL, "admin", "1234");
	String sql = "INSERT INTO article(art_ctgr, imgName, thumb, title, state, m_date, c_date, rep_name, email, content) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
	PreparedStatement pstmt = con.prepareStatement(sql);
	
	pstmt.setString(1, ctgr);
	pstmt.setString(2, art_img_name);
	pstmt.setString(3, thumb_img_name);
	pstmt.setString(4, title);
	pstmt.setString(5, state);
	pstmt.setString(6, today);
	pstmt.setString(7, c_date);
	pstmt.setString(8, rep_name);
	pstmt.setString(9, email);
	pstmt.setString(10, content);
	
	pstmt.executeUpdate();
	
	pstmt.close();
	con.close();
	
}catch(IOException e){
	out.println(e);
	return;
}catch(SQLException e){
	out.println(e);
	return;
}

response.sendRedirect("article.jsp");

%>