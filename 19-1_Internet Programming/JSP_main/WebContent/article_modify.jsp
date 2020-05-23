<%@ page language="java" contentType="text/html; charset=UTF-8"
    import="java.sql.*, java.util.*, java.text.*"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>기사 등록 입력 </title>
<script>
	function cancelOrNot(){	// 취소 버튼을 누르면 뒤로갈지 물어보기
		var flag = confirm('입력한 내용이 모두 사라집니다. 이 페이지를 벗어나시겠습니까?');
		
		if(flag == true){
			document.getElementById("thisPage").reset();
			location.href = "./article.jsp";
		}
	}
</script>

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
	text-decoration: none;
}

li{
	margin-bottom:15px;
	
}

/* @제목, 헤더 공통 css*/

#inWrapper{
	width: 85%;
	float : right;
}

#header{
	width: 100%;
	height: 40px;
	font-weight: bold;
	font-size:23px;
}
#inputWrapper{
	width: 85%;
	float : right;
}

#leftInput{
	width : 20%;
	height : 660px;
	float : left;
	border-right-style: solid;
	border-bottom-style: solid;
	
}

#rightInput{
	width : 79%;
	height : 660px;
	float : right;
}

</style>
</head>
<body>
	<%
	request.setCharacterEncoding("utf-8");
	
	Class.forName("org.mariadb.jdbc.Driver");
	String DB_URL = "jdbc:mariadb://localhost:3306/newsmgt?useSSL=false";
	Connection con = DriverManager.getConnection(DB_URL,"admin","1234");
	String category_sql = "SELECT name_1, name_2 FROM category";
	
	PreparedStatement pstmt = con.prepareStatement(category_sql);
	
	ResultSet rs = pstmt.executeQuery();
	
	java.text.SimpleDateFormat formatter = new java.text.SimpleDateFormat("yyyy-MM-dd");
	String today = formatter.format(new java.util.Date());
	
	String sid = request.getParameter("id");
	int id = Integer.parseInt(sid);
	
	%>

	<h1><a href = "./display.jsp" >홈</a>	&nbsp;&nbsp;&#124;&nbsp;&nbsp;	기사 등록</h1>
	<form action = "./save_article_do.jsp" method="post" id = "thisPage" enctype="multipart/form-data">
		<div class = "outWrapper">
			<div class = "menu">
				<p align= "center" style = "font-size: 20px"><b>MENU</b></p>
				<br>
				<p align="center"><a href = "./display.jsp" style = "text-decoration: none;">기사 게시 화면</a></p>
				<br>
				<p align="center"><a href = "./category.jsp" style = "text-decoration: none;">기사 분류 관리</a></p>
				<br>
				<p align="center"><a href = "./article.jsp" style = "text-decoration: none;">기사 관리</a></p>
			</div>
			<div id = "inWrapper">
				<div id = "header" style = "border-bottom-style: solid;">
				기사 등록
				</div>
			</div>
			<div id = "inputWrapper">
				<div id = "leftInput">
					<br>
					<ul style = "font-size: 14px; text-align: left">
						<li>분류 
							<select size = "1" name = "ctgr" id = "category" style="width: 95%; font-size:14px">
								<optgroup label = "분류">
									<%while(rs.next()){ %>
									<option value = "<%=rs.getString("name_1") %> - <%=rs.getString("name_2") %>"><%=rs.getString("name_1") %> - <%=rs.getString("name_2") %></option>
									<%} %>
								</optgroup>
							</select>
						</li>	
						<br>
	<%
		String sql = "SELECT * FROM article WHERE id=?";
		pstmt = con.prepareStatement(sql);
		pstmt.setInt(1, id);
		rs = pstmt.executeQuery();
		rs.next();
	%>
						<li>등록 상태
							<select size = "1" name= "regState"  id = "reg_state" style="width: 95%; font-size:14px">
								<optgroup label ="등록상태">
									<option value = "등록대기">등록대기</option>
									<option value = "등록완료">등록완료</option>
								</optgroup>
							</select>
						</li>
						<br>
						<li>기사 취재일
							<input type = "date" name = "coverageDay" id = "coverageDay" style= "width: 93%; font-size:14px" required="required" value = "<%=rs.getString("c_date")%>">
						</li>
						<br>
						<li>기자 이름
							<input type = "text" name = "reporterName" id = "reporterName" style = "width: 95%; font-size:14px" maxlength= "10" required="required" value="<%=rs.getString("rep_name") %>">
						</li>
						<br>
						<li>기자 이메일
							<input type = "email" name = "reporterEmail" id = "reporterEmail" style = "width: 95%; font-size:14px" required="required" value="<%=rs.getString("email") %>">
						</li>
						<br>
						<li>썸네일
							<input type = "file" accept="image/*" name = "thumb_img_name" id = "thumb" style = "width: 95%; font-size:14px" required="required"> <br>
							<img src = "./upload/" + <%=rs.getString("thumb") %> style="width: 50px; height: 50px" alt ="썸네일 미리보기" align="right">
						</li>
						<br>
					</ul>
				</div>
				<div id = "rightInput">
					<p style = "border-bottom: solid; width: 100%; height: 40px"> 기사 제목  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type = "text" value = <%=rs.getString("title") %> name = "title" id = "title" style="width: 85%;height: 20px ;font-size: 14px; border-style: solid" required="required"></p>
					<p style = "font-size: 15px">기사 내용
							<textarea rows="50" cols="120" name = "content" style="resize:none; width: 100%; height: 400px; border-style: solid;" required="required"><%=rs.getString("content") %></textarea>
					</p>
					<p style = "font-size: 15px">기사 본문 이미지
						<input type = "file" name = "art_img_name" id= "contentImg" accept="image/*" style = "width: 87%; border-style: ridge;" required="required" value=".upload/" + <%=rs.getString("imgName") %>>
					</p>
					<div style = "padding-right: 20px;">최종 수정일&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
						<input type = "text" id = "lastModifiedDay" style ="width:10%" readonly="readonly" value = "<%=rs.getString("m_date") %>">
					</div>
					<p align = "right">
						<input type ="submit" name = "submit_button" value = "      등록      "> 
						
						<input type = "button" name = "cancel_button" value = "      취소      " onclick = "cancelOrNot()">
					</p>
				</div>
			</div>
		</div>
	</form>	
</body>
</html>