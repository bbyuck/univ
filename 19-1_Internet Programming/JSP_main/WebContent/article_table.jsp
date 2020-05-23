<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"
    import="java.sql.*, java.util.*, java.text.*"
    %>
<script>

function checkDelete(id){
var flag = confirm('정말로 이 기사를 삭제할까요?');
	
	if(flag == true){
		location.href = "./article_delete_do.jsp?id=" + id;
	}
}

function paging(n, endPage){
	
	if(endPage < n){
		n = endPage;
	}
	else if(n < 1){
		n = 1;
	}
	location.href = "./article.jsp?page_num=" + n;

}
</script>
  
<%
final int pageNumbers = 10;
int last_page_flag;




request.setCharacterEncoding("utf-8");
Class.forName("org.mariadb.jdbc.Driver");
String DB_URL = "jdbc:mariadb://localhost:3306/newsmgt?useSSL=false";

java.text.SimpleDateFormat formatter = new java.text.SimpleDateFormat("yyyy-MM-dd");
String today = formatter.format(new java.util.Date());


Connection con = DriverManager.getConnection(DB_URL, "admin", "1234");
PreparedStatement pstmt = null;
ResultSet rs = null;
String sql = null;

String search_word = request.getParameter("search_word");
String keyword = request.getParameter("keyword");


if(!search_word.equals("") && !keyword.equals("")){
	sql = "SELECT COUNT(*) FROM article WHERE ? LIKE '%?%'";
	pstmt = con.prepareStatement(sql);
	pstmt.setString(1,search_word);
	pstmt.setString(2,keyword);
	rs = pstmt.executeQuery();

	rs.next();
}
else{
	sql = "SELECT COUNT(*) FROM article";	
	pstmt = con.prepareStatement(sql);
	rs = pstmt.executeQuery();

	rs.next();
}


int record_count = rs.getInt(1);
int page_count;	//페이지의 갯수
if(record_count % 20 == 0){
	page_count = record_count/20;
}
else{
	page_count = (record_count/20) + 1;
}


String sPage_num = request.getParameter("page_num");
int current_page; // 현재 페이지

if(sPage_num == null){
	current_page=0;
}
else if(Integer.parseInt(sPage_num) < 1){
	current_page = 0;
}
else if(Integer.parseInt(sPage_num) > page_count){
	current_page = page_count;
}
else{
	current_page = Integer.parseInt(sPage_num);
	current_page = (current_page - 1) * 20; //0~9
}
	// current_page에 대한 예외들 처리 후 

	last_page_flag = current_page / 10;	

	
if(!search_word.equals("") && !keyword.equals("")){
	sql = "SELECT * FROM article WHERE ? LIKE '%?%' LIMIT ?, 20";
	pstmt = con.prepareStatement(sql);
	pstmt.setString(1, search_word);
	pstmt.setString(2, keyword);
	pstmt.setInt(3, current_page);
	
}
else{
	sql = "SELECT * FROM article LIMIT ?, 20";	
	pstmt = con.prepareStatement(sql);
	pstmt.setInt(1, current_page);
}


rs = pstmt.executeQuery();

%>
<table>
	<br>
	<tr>
		<th></th>
		<th>분류</th>
		<th>&nbsp;&nbsp;&nbsp;</th>
		<th>제목</th>
		<th>등록상태</th>
		<th>최종 수정일</th>
		<th>기사 취재일</th>
		<th>관리</th>
	</tr>
	<%
	while(rs.next()){
	%>
	<tr>
		<td><%	String modified_date = rs.getString("m_date");
		if(modified_date.equals(today)){ %><img src="./images/new_mark.jpg" width="10px" height="10px"><%} %></td> <!-- 최종 수정일이 오늘이면 N마크 띄우기 -->
		<td><%=rs.getString("art_ctgr") %></td>
		<td><img src="./upload/<%=rs.getString("thumb") %>" width = "25px" height = "25px"></td>
		<td><%=rs.getString("title") %></td>
		<td><%=rs.getString("state") %></td>
		<td><%=rs.getString("m_date") %></td>
		<td><%=rs.getString("c_date") %></td>
		<td><a href="article_modify.jsp?id=<%=rs.getInt("id") %>">수정</a>&nbsp;&nbsp;&nbsp;<a href="javascript:void(0);" onclick="checkDelete(<%=rs.getInt("id") %>)">삭제</a></td>
	</tr>
	<%
	}
	%>
	</table>
	
	<div style="text-align: center; position: absolute; bottom:-20px; border-top:solid; width:86%; padding-top: 20px;">
	
		<a style="text-decoration: none;" href="#" onclick="paging(1, <%=page_count %>); return false">&lt;&lt;-처음 페이지</a>&nbsp;
		<%
		int col_num = 0;
		for(int i = 1; i <= page_count; i++){
		col_num++;
		%>
		&nbsp; <a href="#" onclick= "paging(<%=i %>, <%=i %>); return false" style="text-decoration: none;"><%=i %></a>
		<%	
		if(col_num > 10){
			col_num /= 10;
			out.println("<br>");
		}
		} %>
		&nbsp;&nbsp;<a style="text-decoration: none;" href="#" onclick="paging(<%=page_count %>, <%=page_count %>); return false">끝 페이지-&gt;&gt;</a>
	</div>	

	<form action="article.jsp" method="post" style="text-align: center; position: absolute; bottom:-80px; width:86%; padding-top: 20px;">
		<select name="search_word">
			<option value="rep_name">기자 이름</option>
			<option value="title">기사 제목</option>
			<option value="content">기사 내용</option>
		</select>
		<input type="text" name="keyword">
		<input type="submit"value= "검색">
	</form>

		
<%
	rs.close();
	pstmt.close();
	con.close();
%>