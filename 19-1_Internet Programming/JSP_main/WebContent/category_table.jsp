<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"
    import="java.sql.*"
    %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<script>// 분류 삭제시 삭제 할지 js로 확인
	function checkDelete(code){							
	var flag = confirm('정말로 이 분류를 삭제할까요?');
		
		if(flag == true){
			location.href = "./category_delete_do.jsp?code=" + code;
		}
	}
</script>
</head>
<body>
<%
	request.setCharacterEncoding("utf-8");
	Class.forName("org.mariadb.jdbc.Driver");
	String DB_URL = "jdbc:mariadb://localhost:3306/newsmgt?useSSL=false";

	Connection con = DriverManager.getConnection(DB_URL, "admin", "1234");

	String sql = "SELECT COUNT(*) FROM category";
	PreparedStatement pstmt = con.prepareStatement(sql);
	pstmt = con.prepareStatement(sql);
	ResultSet rs = pstmt.executeQuery();
	rs = pstmt.executeQuery();

	rs.next();
	int record_count = rs.getInt(1);
	int page_count;
	if(record_count % 20 == 0){
		page_count = record_count/20;
	}
	else{
		page_count = (record_count/18) + 1;
	}

	sql = "SELECT * FROM category LIMIT ?, 20";

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
		current_page = (current_page - 1) * 20;
	}
	pstmt = con.prepareStatement(sql);
	pstmt.setInt(1, current_page);
	rs = pstmt.executeQuery();

%>
	<table>
		<br>
		<tr>
			<th>기사 분류 Code.</th>
			<th>대분류</th>
			<th>소분류</th>
			<th>수정</th>
			<th>삭제</th>
		</tr>
		<%
		while(rs.next()){	
		%>
		<tr>
			<td><%=rs.getInt("code") %> </td>
			<td><%=rs.getString("name_1") %></td>
			<td><%=rs.getString("name_2") %></td>
			<td><a href="category_modify.jsp?code=<%=rs.getInt("code") %>">수정</a></td>
			<td><a href="javascript:void(0);" onclick="checkDelete(<%=rs.getInt("code") %>)">삭제</a></td>
		</tr>
		<%
		} 	// while문 끝
		%>
	</table>
	
	
	<div style="text-align: center; position: absolute; bottom:-20px; border-top:solid; width:86%; padding-top: 20px;">
	
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