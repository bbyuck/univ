<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"
    import="java.sql.*"
    %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>기사 게시 화면</title>
<style>

.outWrapper{
	width:100%;
	height:800px;
	position: relative;
}
.menu{
	border-style :solid;
	width: 14%;
	height: 750px;
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

a:link, a:visited{
	text-decoration: none;  <!--링크는 모두 밑줄 제거-->
}


/* @제목, 헤더 공통 css*/

</style>
</head>
<body>
<%
	request.setCharacterEncoding("utf-8");
	String sPage_num = request.getParameter("page_num");
	int page_num;										//초기 화면인 display의 기사 paging
	
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
	
	<h1><a href = "display.jsp?page_num=1">홈</a>	&nbsp;&nbsp;&#124;&nbsp;&nbsp;	기사 게시 화면</h1>
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
		
		<div style="position:relative; height:775px; float:right; width:85%;">
			<jsp:include page="display_table.jsp">
				<jsp:param value="<%=page_num %>" name="page_num"/>
			</jsp:include>
		</div>

	</div>
	<form>
	
	</form>
</body>
</html>