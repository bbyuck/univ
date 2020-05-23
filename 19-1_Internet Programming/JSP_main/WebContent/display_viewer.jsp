<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"
    import="java.sql.*"
    %>
<!DOCTYPE html>
<html>
<head>
<%
request.setCharacterEncoding("utf-8");
Class.forName("org.mariadb.jdbc.Driver");
String DB_URL = "jdbc:mariadb://localhost:3306/newsmgt?useSSL=false";

Connection con = DriverManager.getConnection(DB_URL, "admin", "1234");


String sql = "SELECT * FROM article WHERE id=?";
String sid = request.getParameter("id");
int id = Integer.parseInt(sid);


PreparedStatement pstmt = con.prepareStatement(sql);
pstmt = con.prepareStatement(sql);
pstmt.setInt(1, id);
ResultSet rs = pstmt.executeQuery();
rs = pstmt.executeQuery();
rs.next();
int cur_pv = rs.getInt("pv");

sql = "UPDATE article SET pv=? WHERE id=?";
pstmt = con.prepareStatement(sql);
pstmt.setInt(1,cur_pv + 1); // 조회수 1 증가
pstmt.setInt(2,id);
pstmt.executeUpdate();

sql ="SELECT * FROM article WHERE id=?";
pstmt = con.prepareStatement(sql);
pstmt.setInt(1,id);
rs = pstmt.executeQuery();
rs.next();
%>

<meta charset="UTF-8">
<title><%=rs.getString("title") %> - 기사 View</title>
<style>

.outWrapper{
	width:100%;
	position: relative;
	height: 1000px;
}
.menu{
	border-style :solid;
	width: 14%;
	height:700px;
	float : left;
	position:fixed;
	text-align: center;
}
h1 {
	border-bottom: solid;
	margin-bottom: 10px;
	padding : 15px;
	text-decoration: none;
}

a:link, a:visited{
	text-decoration: none;  <!--링크는 모두 밑줄 제거-->
}


/* @제목, 헤더 공통 css*/

</style>

</head>
<body>
	<h1><a href = "display.jsp?page_num=1">홈</a>	&nbsp;&nbsp;&#124;&nbsp;&nbsp;	기사 VIEWER</h1>
	<div class = "outWrapper">
		<div class = "menu">
			<p style = "font-size: 20px"><b>MENU</b></p>
				<br>
				<p><a href = "./display.jsp">기사 게시 화면</a></p>
				<br>
				<p><a href = "./category.jsp">기사 분류 관리</a></p>
				<br>
				<p><a href = "./article.jsp">기사 관리</a></p>
		</div>
		<div style="position:relative;">
		<table style="position: absolute; left:240px; width:83%">
			<tr>
				<td style="font-size: 30px; font-weight: bold; border-bottom:solid;padding-bottom:20px"><%=rs.getString("title") %></td>
			</tr>
			<tr>
				<td style="border-bottom:solid 1px; padding:10px;">[언론사 이름] <%=rs.getString("rep_name") %> 기자 &nbsp;&nbsp; <%=rs.getString("email") %> &nbsp;&nbsp; 최종 수정일:<%=rs.getString("m_date") %> &nbsp;&nbsp; 조회수:<%=rs.getInt("pv") %></td>
			</tr>
		</table>
		</div>
		<div style="position: absolute; left:280px; top:130px; width: 1000px">
			<div class="img" style= "left: 400px;">
				<img src="./upload/<%=rs.getString("imgName") %>" width="400px" height="400px">
			</div>
			<div class="art_content" style="padding-bottom:100px">
				<%=rs.getString("content") %>
			</div>
			<div style="border-top:solid 2px; width:100%; ">
			&nbsp;
			</div>
			<p style="float: right; bottom:30px; right: 40px; padding-bottom:80px;">
			<input type = "button" value = "목 록" onclick="window.history.back()">
			</p>
		</div>
	</div>
	
<%
rs.close();
pstmt.close();
con.close();
%>
</body>
</html>