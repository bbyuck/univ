<%@ page language="java" contentType="text/html; charset=UTF-8" import="java.sql.*"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>기사 분류 등록</title>

<style>
.outWrapper{
	width:100%;
	height:800px;
	float:left;
}
.menu{
	border-style :solid;
	width: 14%;
	height: 700px;
	float : left;
	text-align: center;
}
h1 {
	border-bottom: solid;
	margin-bottom: 10px;
	padding : 15px;
	text-decoration: none;
}

a{
	text-decoration: none;  <!--링크는 모두 밑줄 제거-->
}

/* @제목, 헤더 공통 css*/

.content{
	width:60%;
	float: inherit;
}
.header{
	width :84%;
	float:right;
	border-bottom:solid black 2px;
	font-size:25px;
	font-weight:bold;
	padding-bottom:15px;
	padding-top: 5px;
	padding-left:15px;
}

#prompt{
	font-size:20px;
	font-weight: bold;
	padding-left:60px;
}

.txt{
	float:right;
	height:30px;
	width:70%;
}

.buttons{
	float:right;
	align-self: rigth;
}
</style>
<script>
function cancel(){
	var conf = confirm("이 페이지를 나가면 정보가 사라집니다. 계속할까요?");
	if(conf == true){
	location.href = "category.jsp";
	}
}

</script>

</head>
<body>
<%
request.setCharacterEncoding("utf-8");

Class.forName("org.mariadb.jdbc.Driver");

String DB_URL = "jdbc:mariadb://localhost:3306/newsmgt?useSSl=false";

Connection con = DriverManager.getConnection(DB_URL, "admin", "1234");
String sql = "SELECT * FROM category WHERE code=?";

int code = Integer.parseInt(request.getParameter("code"));

PreparedStatement pstmt = con.prepareStatement(sql);
pstmt.setInt(1, code);

ResultSet rs = pstmt.executeQuery();
rs.next();
%>


<h1><a href = "./display.jsp">홈</a>	&nbsp;&nbsp;&#124;&nbsp;&nbsp;	기사 분류 등록</h1>
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
		<p class = "header">기사 분류 등록</p>
		<form action = "./category_modify_do.jsp" method = "post" class = "content" id = "thisPage">
			<p id = "prompt" style = "padding-top:15px;">기사 분류 Code.<input type = "text" class = "txt" id = "categoryNum" name = "categoryCode" readonly="readonly" value = "<%=code %>"></p>
			<br>
			<p id = "prompt">기사 대분류 <input type = "text" class = "txt" id = "categoryCode" name = "categoryName_1" value = "<%=rs.getString("name_1") %>" required="required"></p>
			<br>
			<p id = "prompt">기사 소분류<input type = "text" class = "txt" id = "categoryName" name = "categoryName_2" value = "<%=rs.getString("name_2") %>" required="required"></p>
			<br>
			<div class = "buttons">
				<input type = "submit" value = "등 록" style = "width:70px; height:40px; margin:20px;">
				<input type = "button" value = "취 소" style = "width:70px; height:40px;" onclick = "cancel()">
			</div>
		</form>
	</div>	
	<%
		rs.close();
		pstmt.close();
		con.close();
	%>
</body>
</html>