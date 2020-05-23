<%@ page language="java" contentType="text/html; charset=UTF-8" import="java.sql.*"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>기사 관리</title>

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
	location.href = "article_reg.jsp";
}

</script>

</head>

<body>
<%
request.setCharacterEncoding("utf-8");
String sPage_num = request.getParameter("page_num");

String search_word = request.getParameter("search_word");
String keyword = request.getParameter("keyword");

if(search_word == null){
	search_word = "";
}
if(keyword == null){
	 keyword = "";
}

int page_num;		//페이지의 number get방식으로 받아오기

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


<h1><a href = "./display.jsp">홈</a>	&nbsp;&nbsp;&#124;&nbsp;&nbsp;	기사 관리</h1>
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
		<div style="position:relative; height:875px; float:right; width:85%;" > <!-- article_table.jsp include -->
			<jsp:include page="article_table.jsp">
				<jsp:param value="<%=page_num %>" name="page_num"/>
				<jsp:param value="<%=search_word %>" name="search_word"/>
				<jsp:param value="<%=keyword %>" name="keyword"/>
			</jsp:include>
		</div>
		<p>
		<input type = "button" value = "신규 기사 등록" style="position:absolute; bottom:100px; right:200px; float: right; height:25px" onclick="nextPage()">
		</p>
	</div>

</body>
</html>