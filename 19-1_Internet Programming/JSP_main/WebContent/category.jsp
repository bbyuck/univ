<%@ page language="java" contentType="text/html; charset=UTF-8" import="java.sql.*"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>기사 분류 관리</title>

<style>
.outWrapper{
	width:100%;
	height:1000px;
	position: relative;
}
.menu{
	border-style :solid;
	width: 14%;
	height: 850px;
	float : left;
	position:relative;
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


td{
	height:34px;
	font-size: 20px;
	text-align:center;
}

/* @제목, 헤더 공통 css*/


table{
	width:85%;
	border-collapse:collapse;
}
th{
	padding-bottom:15px;
	padding-top:5px;
	border-bottom: solid;
}



</style>
<script>
function nextPage(){
	location.href = "category_reg.jsp";
}

</script>


</head>

<body>
<%
request.setCharacterEncoding("utf-8");
String sPage_num = request.getParameter("page_num");
int page_num;											// 분류관리 페이지도 페이징

if(sPage_num == null){
	page_num = 1;
}
else{
	page_num = Integer.parseInt(sPage_num);
	if(page_num < 1){
		page_num = 1;
	}
}
%>

<h1><a href = "./display.jsp">홈</a>	&nbsp;&nbsp;&#124;&nbsp;&nbsp;	기사 분류 관리</h1>
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
		<div style="position:relative; height:875px; float:right; width:85%;" >
			<jsp:include page="category_table.jsp">
				<jsp:param value="<%=page_num %>" name="page_num"/>
			</jsp:include>
		</div>
		<p>
		<input type = "button" value = "신규 분류 등록" style="position:absolute; bottom:100px; right:200px; float: right; height:25px" onclick="nextPage()">
		</p>
	</div>

</body>
</html>