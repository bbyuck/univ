<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"
    import="java.sql.*"
    %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">

<script>
function paging(n, endPage){
	
	if(endPage < n){
		n = endPage;
	}
	else if(n < 1){
		n = 1;
	}
	location.href = "./display.jsp?page_num=" + n;
}

</script>
</head>
<body>
	<%
	request.setCharacterEncoding("utf-8");
	Class.forName("org.mariadb.jdbc.Driver");
	String DB_URL = "jdbc:mariadb://localhost:3306/newsmgt?useSSL=false";
	
	Connection con = DriverManager.getConnection(DB_URL, "admin", "1234");

	String sql = "SELECT COUNT(*) FROM article WHERE state='등록완료'";
	PreparedStatement pstmt = con.prepareStatement(sql);
	pstmt = con.prepareStatement(sql);
	ResultSet rs = pstmt.executeQuery();
	rs = pstmt.executeQuery();
	
	rs.next();
	int record_count = rs.getInt(1);
	int page_count;
	if(record_count % 5 == 0){
		page_count = record_count/5;
	}
	else{
		page_count = (record_count/5) + 1;
	}
	
	sql = "SELECT * FROM article WHERE state='등록완료' LIMIT ?, 5";
	
	String sPage_num = request.getParameter("page_num");
	int current_page;
	
	if(sPage_num == null){
		current_page=0;
	}
	else if(Integer.parseInt(sPage_num) < 1){
		current_page = 1;
	}
	else if(Integer.parseInt(sPage_num) > page_count){
		current_page = page_count;
	}
	else{
		current_page = Integer.parseInt(sPage_num);
		current_page = (current_page - 1) * 5;
	}
	pstmt = con.prepareStatement(sql);
	pstmt.setInt(1, current_page);
	rs = pstmt.executeQuery();
	
	%>
	<table style="padding: 30px;">
		<%while(rs.next()){
			if(rs.getString("state").equals("등록완료")){
		%>
		<tr>
			<th style="width:200px"></th>
			<td><a class = "name" href = "display_viewer.jsp?id=<%=rs.getInt("id") %>" style = "font-size:30px; font-weight: bold;"  target = "_parent"><%=rs.getString("title") %></a>
			</td>
		</tr>
		<tr>
			<td><img class = "thumbnail" src="./upload/<%=rs.getString("thumb") %>" alt="썸네일" width="50px" height= "50px" style=" margin-right: 40px;"></td>
			<%String content = rs.getString("content");
			//기사 내용이 100자가 넘어가면 java string method로 ...
			 if(content.length() > 100){					
				 content = content.substring(0, 100) + "...";
			 }
			%>
			<td><textarea class="ellipsis" style= "width:850px; height:75px; resize: none;" readonly="readonly"><%=content %></textarea></td>
		</tr>
		<%
			}
		}
		%>
	</table>

	<div style="text-align: center; position: absolute; bottom:-20px; border-top:solid; width:86%; padding-top: 20px;">
		<!-- 페이징 부분 -->
		<a style="text-decoration: none;" href="#" onclick="paging(1, <%=page_count %>, <%=page_count %>); return false">&lt;&lt;-처음 페이지</a>&nbsp;
		<%
		int col_num = 0;
		for(int i = 1; i <= page_count; i++){
		col_num++;
		%>
		&nbsp; <a href="#" onclick= "paging(<%=i %>); return false" style="text-decoration: none;"><%=i %></a>
		<%	
		if(col_num > 10){
			col_num /= 10;
			out.println("<br>");
		}
		} %>
		&nbsp;&nbsp;<a style="text-decoration: none;" href="#" onclick="paging(<%=page_count %>, <%=page_count %>); return false">끝 페이지-&gt;&gt;</a>
	</div>	
	
	<%
	rs.close();
	pstmt.close();
	con.close();
	%>
</body>
</html>