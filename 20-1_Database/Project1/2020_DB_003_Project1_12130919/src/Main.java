import java.sql.*;

public class Main {
	public static void main(String arg[]) {	
		String url = "jdbc:postgresql://127.0.0.1:5432/project_movie";
		String userid = "postgres";
		String pw = "cse3207";
		String desc = "Translated SQL : ";
		String sql;

		
		try {
			Class.forName("org.postgresql.Driver");
		}
		catch (ClassNotFoundException e){
			System.out.println("Where is your PostgresSQL JDBC Driver? Include in your library path");
			e.printStackTrace();
			return;
		}
		
		Connection conn = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		
		try {
			conn = DriverManager.getConnection(url, userid, pw);
			System.out.println("DB ���� ����!");
		}
		catch (SQLException e) {
			System.out.println("Connection Failed! Check output console");
			e.printStackTrace();
			return;
		}
		
		// 1. Create Table and insert initial data
		try {
			sql = "CREATE TABLE director(\r\n" + 
					"	directorID serial primary key,\r\n" + 
					"	directorName varchar(40),\r\n" + 
					"	dateOfBirth char(10),\r\n" + 
					"	dateOfDeath char(10)\r\n" + 
					");\r\n" + 
					"CREATE TABLE actor(\r\n" + 
					"	actorID serial primary key,\r\n" + 
					"	actorName varchar(40),\r\n" + 
					"	dateOfBirth char(10),\r\n" + 
					"	dateOfDeath char(10),\r\n" + 
					"	gender int\r\n" + 
					");\r\n" + 
					"CREATE TABLE movie(\r\n" + 
					"	movieID serial primary key,\r\n" + 
					"	movieName varchar(50),\r\n" + 
					"	releaseYear char(4),\r\n" + 
					"	releaseMonth char(2),\r\n" + 
					"	releaseDate char(2),\r\n" + 
					"	publisherName varchar(50),\r\n" + 
					"	avgRate float\r\n" + 
					");\r\n" + 
					"CREATE TABLE award(\r\n" + 
					"	awardID serial primary key,\r\n" + 
					"	awardName varchar(50)\r\n" + 
					");\r\n" + 
					"CREATE TABLE genre(\r\n" + 
					"	genreName varchar(30) primary key\r\n" + 
					");\r\n" + 
					"CREATE TABLE movieGenre (\r\n" + 
					"	movieID int,\r\n" + 
					"	genreName varchar(30),\r\n" + 
					"	foreign key(movieID) references movie,\r\n" + 
					"	foreign key(genreName) references genre,\r\n" + 
					"	primary key(movieID, genreName)\r\n" + 
					");\r\n" + 
					"CREATE TABLE movieObtain(\r\n" + 
					"	movieID int,\r\n" + 
					"	awardID int,\r\n" + 
					"	year char(4),\r\n" + 
					"	foreign key(movieID) references movie,\r\n" + 
					"	foreign key(awardID) references award,\r\n" + 
					"	primary key(movieID, awardID)\r\n" + 
					");\r\n" + 
					"CREATE TABLE actorObtain(\r\n" + 
					"	actorID int,\r\n" + 
					"	awardID int,\r\n" + 
					"	year char(4),\r\n" + 
					"	foreign key(actorID) references actor,\r\n" + 
					"	foreign key(awardID) references award,\r\n" + 
					"	primary key(actorID, awardID)\r\n" + 
					");\r\n" + 
					"CREATE TABLE directorObtain(\r\n" + 
					"	directorID int,\r\n" + 
					"	awardID int,\r\n" + 
					"	year char(4),\r\n" + 
					"	foreign key(directorID) references director,\r\n" + 
					"	foreign key(awardID) references award,\r\n" + 
					"	primary key(directorID, awardID)\r\n" + 
					");\r\n" + 
					"CREATE TABLE casting(\r\n" + 
					"	movieID int,\r\n" + 
					"	actorID int,\r\n" + 
					"	role int,\r\n" + 
					"	foreign key(movieID) references movie,\r\n" + 
					"	foreign key(actorID) references actor,\r\n" + 
					"	primary key(movieID, actorID)\r\n" + 
					");\r\n" + 
					"CREATE TABLE make(\r\n" + 
					"	movieID int,\r\n" + 
					"	directorID int,\r\n" + 
					"	foreign key(movieID) references movie,\r\n" + 
					"	foreign key(directorID) references director,\r\n" + 
					"	primary key(movieID, directorID)\r\n" + 
					");\r\n" + 
					"CREATE TABLE customer (\r\n" + 
					"	customerID serial,\r\n" + 
					"	customerName varchar(40),\r\n" + 
					"	dateOfBirth char(10),\r\n" + 
					"	gender int,\r\n" + 
					"	primary key(customerID)\r\n" + 
					");\r\n" + 
					"CREATE TABLE customerRate(\r\n" + 
					"	customerID int,\r\n" + 
					"	movieID int,\r\n" + 
					"	rate int,\r\n" + 
					"	foreign key(customerID) references customer,\r\n" + 
					"	foreign key(movieID) references movie,\r\n" + 
					"	primary key(customerID, movieID)\r\n" + 
					");";
			pstmt = conn.prepareStatement(sql);
			pstmt.executeUpdate();
			System.out.println("Table ���� �Ϸ�!");
			
			sql = "INSERT INTO director VALUES(default, 'Tim Burton','1958.08.25',null);\r\n" + 
					"INSERT INTO director VALUES(default, 'David Fincher','1962.08.28',null);\r\n" + 
					"INSERT INTO director VALUES(default, 'Christopher Nolan','1970.07.30',null);\r\n" + 
					"INSERT INTO customer VALUES(default, 'Bob', '1997.11.14', 1);\r\n" + 
					"INSERT INTO customer VALUES(default, 'John', '1978.01.23', 1);\r\n" + 
					"INSERT INTO customer VALUES(default, 'Jack', '1980.05.04', 1);\r\n" + 
					"INSERT INTO customer VALUES(default, 'Jill', '1981.04.17', 0);\r\n" + 
					"INSERT INTO customer VALUES(default, 'Bell', '1990.05.14', 0);\r\n" + 
					"INSERT INTO actor VALUES(default, 'Johnny Depp', '1963.06.09', null, 1);\r\n" + 
					"INSERT INTO actor VALUES(default, 'Winona Ryder', '1971.10.29', null, 0);\r\n" + 
					"INSERT INTO actor VALUES(default, 'Anne Hathaway', '1982.11.12', null, 0);\r\n" + 
					"INSERT INTO actor VALUES(default, 'Christian Bale', '1974.01.30', null, 1);\r\n" + 
					"INSERT INTO actor VALUES(default, 'Heath Ledger', '1979.04.04', '2008.01.22', 1);\r\n" + 
					"INSERT INTO actor VALUES(default, 'Jesse Eisenberg', '1983.10.05', null, 1);\r\n" + 
					"INSERT INTO actor VALUES(default, 'Andrew Garfield', '1983.08.20', null, 1);\r\n" + 
					"INSERT INTO actor VALUES(default, 'Fionn Whitehead', '1997.07.18', null, 1);\r\n" + 
					"INSERT INTO actor VALUES(default, 'Tom Hardy', '1963.09.15', null, 1);\r\n" + 
					"INSERT INTO movie VALUES(default, 'Edward Scissorhands', '1991', '06', '29', '20th Century Fox Presents', default);\r\n" + 
					"INSERT INTO movie VALUES(default, 'Alice In Wonderland', '2010', '03', '04', 'Korea Sony Pictures', default);\r\n" + 
					"INSERT INTO movie VALUES(default, 'The Social Network', '2010', '11', '18', 'Korea Sony Pictures', default);\r\n" + 
					"INSERT INTO movie VALUES(default, 'The Dark Knight', '2008', '08', '06', 'Warner Brothers Korea', default);\r\n" + 
					"INSERT INTO movie VALUES(default, 'Dunkirk', '2017', '07', '13', 'Warner Brothers Korea', default);\r\n" + 
					"INSERT INTO genre VALUES('Fantasy');\r\n" + 
					"INSERT INTO genre VALUES('Romance');\r\n" + 
					"INSERT INTO genre VALUES('Adventure');\r\n" + 
					"INSERT INTO genre VALUES('Family');\r\n" + 
					"INSERT INTO genre VALUES('Drama');\r\n" + 
					"INSERT INTO genre VALUES('Action');\r\n" + 
					"INSERT INTO genre VALUES('Mystery');\r\n" + 
					"INSERT INTO genre VALUES('Thriller');\r\n" + 
					"INSERT INTO genre VALUES('War');\r\n";
			pstmt = conn.prepareStatement(sql);
			pstmt.executeUpdate();
			
			sql = "INSERT INTO movieGenre VALUES(1, 'Fantasy');\r\n" + 
					"INSERT INTO movieGenre VALUES(1, 'Romance');\r\n" + 
					"INSERT INTO movieGenre VALUES(2, 'Fantasy');\r\n" + 
					"INSERT INTO movieGenre VALUES(2, 'Adventure');\r\n" + 
					"INSERT INTO movieGenre VALUES(2, 'Family');\r\n" + 
					"INSERT INTO movieGenre VALUES(3, 'Drama');\r\n" + 
					"INSERT INTO movieGenre VALUES(4, 'Action');\r\n" + 
					"INSERT INTO movieGenre VALUES(4, 'Drama');\r\n" + 
					"INSERT INTO movieGenre VALUES(4, 'Mystery');\r\n" + 
					"INSERT INTO movieGenre VALUES(4, 'Thriller');\r\n" + 
					"INSERT INTO movieGenre VALUES(5, 'Action');\r\n" + 
					"INSERT INTO movieGenre VALUES(5, 'Drama');\r\n" + 
					"INSERT INTO movieGenre VALUES(5, 'Thriller');\r\n" + 
					"INSERT INTO movieGenre VALUES(5, 'War');\r\n" + 
					"INSERT INTO casting VALUES(1, 1, 1);\r\n" + 
					"INSERT INTO casting VALUES(1, 2, 1);\r\n" + 
					"INSERT INTO casting VALUES(2, 1, 1);\r\n" + 
					"INSERT INTO casting VALUES(2, 3, 1);\r\n" + 
					"INSERT INTO casting VALUES(3, 6, 1);\r\n" + 
					"INSERT INTO casting VALUES(3, 7, 2);\r\n" + 
					"INSERT INTO casting VALUES(4, 4, 1);\r\n" + 
					"INSERT INTO casting VALUES(4, 5, 1);\r\n" + 
					"INSERT INTO casting VALUES(5, 8, 1);\r\n" + 
					"INSERT INTO casting VALUES(5, 9, 1);\r\n" + 
					"INSERT INTO make VALUES(1, 1);\r\n" + 
					"INSERT INTO make VALUES(2, 1);\r\n" + 
					"INSERT INTO make VALUES(3, 2);\r\n" + 
					"INSERT INTO make VALUES(4, 3);\r\n" + 
					"INSERT INTO make VALUES(5, 3);";
			pstmt = conn.prepareStatement(sql);
			pstmt.executeUpdate();
			
			System.out.println("initial data �Է� �Ϸ�\n");
		} catch (SQLException e) {
			System.out.println("1�� Query error");
			e.printStackTrace();
			return;
		}
		
		// 2.1
		try {
			System.out.println("2.1");
			int actorID = 0;
			int awardID = 0;
			System.out.println("Statement : Winona Ryder won the \"Best supporting actor\" award in 1994");
			sql = "INSERT INTO award VALUES(default, ?)";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Best supporting actor");
			pstmt.executeUpdate();
			
			System.out.println(desc + "INSERT INTO award VALUES(default, 'Best supporting actor')");
			System.out.println("Update Table");
			
			sql = "SELECT * FROM award";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------award------");
			System.out.println("|awardID\t|awardName");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\n");
			}
			System.out.println("");
			
			sql = "SELECT actorID FROM actor WHERE actorName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Winona Ryder");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				actorID = rs.getInt("actorID");	
			}
			System.out.println(desc + "SELECT actorID FROM actor WHERE actorName='Winona Ryder'");
			System.out.println("Winona Ryder's ID : " + actorID);
			
			sql = "SELECT awardID FROM award WHERE awardName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Best supporting actor");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				awardID = rs.getInt("awardID");	
			}
			System.out.println(desc + "SELECT awardID FROM award WHERE awardName='Best supporting actor'");
			System.out.println("The ID of 'Best supporting actor' award : " + awardID);
			
			
			System.out.println(desc + "INSERT INTO actorObtain VALUES(" + actorID + ", " + awardID + ", " + "1994)");
			sql = "INSERT INTO actorObtain VALUES(?, ?, ?)";
			pstmt = conn.prepareStatement(sql);
			pstmt.setInt(1, actorID);
			pstmt.setInt(2, awardID);
			pstmt.setString(3, "1994");
			pstmt.executeUpdate();
			System.out.println("Update Table");
			
			sql = "SELECT * FROM actorObtain";
			System.out.println("------actorObtain------");
			System.out.println("|actorID\t|awardID\t|year");
			System.out.println("-------------------------------------");
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getInt(2) + "\t\t|" + rs.getString(3) + "\n");
			}
			System.out.println("\n");
			
			
		} catch(SQLException e) {
			System.out.println("2.1�� Query error");
			e.printStackTrace();
			return;
		}
		
		try {
			System.out.println("2.2");
			System.out.println("Statement : Andrew Garfield won the \"Best supporting actor\" award in 2011");
			int actorID = 0;
			int awardID = 0;
			
			sql = "SELECT actorID FROM actor WHERE actorName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Andrew Garfield");
			System.out.println(desc + "SELECT actorID FROM actor WHERE actorName='Andrew Garfiled'");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				actorID = rs.getInt("actorID");
			}
			System.out.println("Andrew Garfiled's ID : " + actorID);
			
			sql = "SELECT awardID FROM award WHERE awardName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Best supporting actor");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				awardID = rs.getInt("awardID");
			}
			System.out.println(desc + "SELECT awardID FROM award WHERE awardName='Best supporting actor'");
			System.out.println("The ID of 'Best supportin actor' award : " + awardID);
			
			System.out.println(desc + "INSERT INTO actorObtain VALUES(" + actorID + ", " + awardID + ", " + "2011)");
			sql = "INSERT INTO actorObtain VALUES(?, ?, ?)";
			pstmt = conn.prepareStatement(sql);
			pstmt.setInt(1, actorID);
			pstmt.setInt(2, awardID);
			pstmt.setString(3, "2011");
			pstmt.executeUpdate();
			System.out.println("Update Table");
			
			sql = "SELECT * FROM actorObtain";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------actorObtain------");
			System.out.println("|actorID\t|awardID\t|year");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getInt(2) + "\t\t|" + rs.getString(3) + "\n");
			}
			System.out.println("\n");
		} catch(SQLException e) {
			System.out.println("2.2�� Query error");
			e.printStackTrace();
			return;
		}
		
		try {
			System.out.println("2.3");
			System.out.println("Statement : Jesse Eisenberg won the \"Best main actor\" award in 2011");
			int actorID = 0;
			int awardID = 0;
			sql = "INSERT INTO award VALUES(default, ?)";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Best main actor");
			pstmt.executeUpdate();
			System.out.println("Translated SQL : INSERT INTO award VALUES(default, 'Best main actor')");
			System.out.println("Update Table");
			sql = "SELECT * FROM award";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------award------");
			System.out.println("|awardID\t|awardName");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\n");
			}
			System.out.println("");
			
			sql = "SELECT actorID FROM actor WHERE actorName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Jesse Eisenberg");
			rs = pstmt.executeQuery();
			System.out.println(desc + "SELECT actorID FROM actor WHERE actorName='Jesse Eisenberg'");
			if(rs.next()) {
				actorID = rs.getInt("actorID");
			}
			System.out.println("Jesse Eisenberg's ID : " + actorID);
			
			sql = "SELECT awardID FROM award WHERE awardName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Best main actor");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				awardID = rs.getInt("awardID");
			}
			System.out.println(desc + "SELECT awardID FROM award WHERE awardName='Best main actor'");
			System.out.println("The ID of 'Best main actor' award : " + awardID);
			System.out.println(desc + "INSERT INTO actorObtain VALUES(" + actorID + ", " + awardID + ", 2011)");
			sql ="INSERT INTO actorObtain VALUES(?, ?, ?)";
			pstmt = conn.prepareStatement(sql);
			pstmt.setInt(1, actorID);
			pstmt.setInt(2, awardID);
			pstmt.setString(3, "2011");
			pstmt.executeUpdate();
			System.out.println("Update Table");
			
			sql = "SELECT * FROM actorObtain";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------actorObtain------");
			System.out.println("|actorID\t|awardID\t|year");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getInt(2) + "\t\t|" + rs.getString(3) + "\n");
			}
			System.out.println("\n");
		} catch(SQLException e) {
			System.out.println("2.3�� Query error");
			e.printStackTrace();
			return;
		}
		
		try {
			System.out.println("2.4");
			System.out.println("Statement : Johnny Depp won the \"Best villain actor\" award in 2011");
			
			int actorID = 0;
			int awardID = 0;
			sql = "INSERT INTO award VALUES(default, ?)";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Best villain actor");
			pstmt.executeUpdate();
			System.out.println("Translated SQL : INSERT INTO award VALUES(default, 'Best villain actor')");
			System.out.println("Update Table");
			sql = "SELECT * FROM award";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------award------");
			System.out.println("|awardID\t|awardName");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\n");
			}
			System.out.println("");
			
			sql = "SELECT actorID FROM actor WHERE actorName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Johnny Depp");
			rs = pstmt.executeQuery();
			System.out.println(desc + "SELECT actorID FROM actor WHERE actorName='Johnny Depp'");
			if(rs.next()) {
				actorID = rs.getInt("actorID");
			}
			System.out.println("Johnny Depp's ID : " + actorID);
			
			sql = "SELECT awardID FROM award WHERE awardName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Best villain actor");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				awardID = rs.getInt("awardID");
			}
			System.out.println(desc + "SELECT awardID FROM award WHERE awardName='Best villain actor'");
			System.out.println("The ID of 'Best main actor' award : " + awardID);
			System.out.println(desc + "INSERT INTO actorObtain VALUES(" + actorID + ", " + awardID + ", 2011)");
			sql ="INSERT INTO actorObtain VALUES(?, ?, ?)";
			pstmt = conn.prepareStatement(sql);
			pstmt.setInt(1, actorID);
			pstmt.setInt(2, awardID);
			pstmt.setString(3, "2011");
			pstmt.executeUpdate();
			System.out.println("Update Table");
			
			sql = "SELECT * FROM actorObtain";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------actorObtain------");
			System.out.println("|actorID\t|awardID\t|year");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getInt(2) + "\t\t|" + rs.getString(3) + "\n");
			}
			System.out.println("\n");
			
		} catch(SQLException e) {
			System.out.println("2.4�� Query error");
			e.printStackTrace();
			return;
		}
		
		try {
			System.out.println("2.5");
			System.out.println("Statement : Edward Scissorhands won the \"Best fantasy movie\" award in 1991");
			
			int movieID = 0;
			int awardID = 0;
			sql = "INSERT INTO award VALUES(default, ?)";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Best fantasy movie");
			pstmt.executeUpdate();
			System.out.println("Translated SQL : INSERT INTO award VALUES(default, 'Best fantasy movie')");
			System.out.println("Update Table");
			sql = "SELECT * FROM award";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------award------");
			System.out.println("|awardID\t|awardName");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\n");
			}
			System.out.println("");
			
			sql = "SELECT movieID FROM movie WHERE movieName=?";
			System.out.println(desc + "SELECT movieID FROM movie WHERE movieName='Edward Scissorhands'");
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Edward Scissorhands");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				movieID = rs.getInt("movieID");
			}
			System.out.println("The ID of 'Edward Scissorhands' : " + movieID);
			sql = "SELECT awardID FROM award WHERE awardName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Best fantasy movie");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				awardID = rs.getInt("awardID");
			}
			System.out.println(desc + "SELECT awardID FROM award WHERE awardName='Best fantasy movie'");
			System.out.println("The ID of 'Best fantasy movie' award : " + awardID);
			
			System.out.println(desc + "INSERT INTO movieObtain VALUES(" + movieID + ", " + awardID + ", 1991)");
			sql ="INSERT INTO movieObtain VALUES(?, ?, ?)";
			pstmt = conn.prepareStatement(sql);
			pstmt.setInt(1, movieID);
			pstmt.setInt(2, awardID);
			pstmt.setString(3, "1991");
			pstmt.executeUpdate();
			System.out.println("Update Table");
			
			sql = "SELECT * FROM movieObtain";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------movieObtain------");
			System.out.println("|movieID\t|awardID\t|year");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getInt(2) + "\t\t|" + rs.getString(3) + "\n");
			}
			System.out.println("\n");
			
			
		} catch(SQLException e) {
			System.out.println("2.5�� Query error");
			e.printStackTrace();
			return;
		}
		
		try {
			System.out.println("2.6");
			System.out.println("Statement : The Dark Knight won the \"Best picture\" award in 2009");
			
			int movieID = 0;
			int awardID = 0;
			sql = "INSERT INTO award VALUES(default, ?)";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Best picture");
			pstmt.executeUpdate();
			System.out.println("Translated SQL : INSERT INTO award VALUES(default, 'Best picture')");
			System.out.println("Update Table");
			sql = "SELECT * FROM award";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------award------");
			System.out.println("|awardID\t|awardName");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\n");
			}
			System.out.println("");
			
			sql = "SELECT movieID FROM movie WHERE movieName=?";
			System.out.println(desc + "SELECT movieID FROM movie WHERE movieName='The Dark Knight'");
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "The Dark Knight");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				movieID = rs.getInt("movieID");
			}
			System.out.println("The ID of 'The Dark Knight' : " + movieID);
			sql = "SELECT awardID FROM award WHERE awardName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Best picture");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				awardID = rs.getInt("awardID");
			}
			System.out.println(desc + "SELECT awardID FROM award WHERE awardName='Best picture'");
			System.out.println("The ID of 'Best picture' award : " + awardID);
			
			System.out.println(desc + "INSERT INTO movieObtain VALUES(" + movieID + ", " + awardID + ", 2009)");
			sql ="INSERT INTO movieObtain VALUES(?, ?, ?)";
			pstmt = conn.prepareStatement(sql);
			pstmt.setInt(1, movieID);
			pstmt.setInt(2, awardID);
			pstmt.setString(3, "2009");
			pstmt.executeUpdate();
			System.out.println("Update Table");
			
			sql = "SELECT * FROM movieObtain";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------movieObtain------");
			System.out.println("|movieID\t|awardID\t|year");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getInt(2) + "\t\t|" + rs.getString(3) + "\n");
			}
			System.out.println("\n");
			
			
		} catch(SQLException e) {
			System.out.println("2.6�� Query error");
			e.printStackTrace();
			return;
		}
		
		try {
			System.out.println("2.7");
			System.out.println("Statement : Alice In Wonderland won the \"Best fantasy movie\" award in 2011");
			
			int movieID = 0;
			int awardID = 0;
			
			sql = "SELECT movieID FROM movie WHERE movieName=?";
			System.out.println(desc + "SELECT movieID FROM movie WHERE movieName='Alice In Wonderland'");
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Alice In Wonderland");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				movieID = rs.getInt("movieID");
			}
			System.out.println("The ID of 'Alice In Wonderland' : " + movieID);
			sql = "SELECT awardID FROM award WHERE awardName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Best fantasy movie");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				awardID = rs.getInt("awardID");
			}
			System.out.println(desc + "SELECT awardID FROM award WHERE awardName='Best fantasy movie'");
			System.out.println("The ID of 'Best fantasy movie' award : " + awardID);
			
			System.out.println(desc + "INSERT INTO movieObtain VALUES(" + movieID + ", " + awardID + ", 2011)");
			sql ="INSERT INTO movieObtain VALUES(?, ?, ?)";
			pstmt = conn.prepareStatement(sql);
			pstmt.setInt(1, movieID);
			pstmt.setInt(2, awardID);
			pstmt.setString(3, "2011");
			pstmt.executeUpdate();
			System.out.println("Update Table");
			
			sql = "SELECT * FROM movieObtain";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------movieObtain------");
			System.out.println("|movieID\t|awardID\t|year");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getInt(2) + "\t\t|" + rs.getString(3) + "\n");
			}
			System.out.println("\n");
			
		} catch(SQLException e) {
			System.out.println("2.7�� Query error");
			e.printStackTrace();
			return;
		}
		
		try {
			System.out.println("2.8");
			System.out.println("Statement : David Fincher won the \"Best Director\" award in 2011");
			
			int directorID = 0;
			int awardID = 0;
			sql = "INSERT INTO award VALUES(default, ?)";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Best director");
			pstmt.executeUpdate();
			System.out.println("Translated SQL : INSERT INTO award VALUES(default, 'Best director')");
			System.out.println("Update Table");
			sql = "SELECT * FROM award";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------award------");
			System.out.println("|awardID\t|awardName");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\n");
			}
			System.out.println("");
			
			sql = "SELECT directorID FROM director WHERE directorName=?";
			System.out.println(desc + "SELECT directorID FROM director WHERE directorName='David Fincher'");
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "David Fincher");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				directorID = rs.getInt("directorID");
			}
			System.out.println("David Fincher's ID : " + directorID);
			sql = "SELECT awardID FROM award WHERE awardName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Best director");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				awardID = rs.getInt("awardID");
			}
			System.out.println(desc + "SELECT awardID FROM award WHERE awardName='Best director'");
			System.out.println("The ID of 'Best director' award : " + awardID);
			
			System.out.println(desc + "INSERT INTO directorObtain VALUES(" + directorID + ", " + awardID + ", 2011)");
			sql ="INSERT INTO directorObtain VALUES(?, ?, ?)";
			pstmt = conn.prepareStatement(sql);
			pstmt.setInt(1, directorID);
			pstmt.setInt(2, awardID);
			pstmt.setString(3, "2011");
			pstmt.executeUpdate();
			System.out.println("Update Table");
			
			sql = "SELECT * FROM directorObtain";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------directorObtain------");
			System.out.println("|directorID\t|awardID\t|year");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getInt(2) + "\t\t|" + rs.getString(3) + "\n");
			}
			System.out.println("\n");
			
		} catch (SQLException e) {
			System.out.println("2.8�� Query error");
			e.printStackTrace();
			return;
		}
		
		try {
			System.out.println("3.1");
			System.out.println("Statement : Bob rates 5 to \"The Dark Knight\"");
			
			int customerID = 0;
			int movieID = 0;
			
			System.out.println(desc + "SELECT customerID FROM customer WHERE customerName='Bob'");
			sql = "SELECT customerID FROM customer WHERE customerName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Bob");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				customerID = rs.getInt("customerID");
			}
			System.out.println("Bob's ID : " + customerID);
			
			System.out.println(desc + "SELECT movieID FROM movie WHERE movieName='The Dark Knight'");
			sql = "SELECT movieID FROM movie WHERE movieName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "The Dark Knight");
			rs = pstmt.executeQuery();
			if (rs.next()) {
				movieID = rs.getInt("movieID");
			}
			System.out.println("The ID of 'The Dark Knight' : " + movieID);
			
			System.out.println(desc + "INSERT INTO customerRate VALUES(" + customerID + ", " + movieID + ", 5)");
			sql = "INSERT INTO customerRate VALUES(?, ?, ?)";
			pstmt = conn.prepareStatement(sql);
			pstmt.setInt(1, customerID);
			pstmt.setInt(2, movieID);
			pstmt.setInt(3, 5);
			pstmt.executeUpdate();
			
			sql = "SELECT * FROM customerRate";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			
			System.out.println("------customerRate------");
			System.out.println("|customerID\t|movieID\t|rate");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getInt(2) + "\t\t|" + rs.getString(3) + "\n");
			}
			System.out.println("");
			
			System.out.println(desc + "UPDATE movie SET avgRate = (SELECT avg(rate) FROM customerRate WHERE movieID=" + movieID + ") WHERE movieID=" + movieID + ")");
			sql = "UPDATE movie SET avgRate=(SELECT avg(rate) FROM customerRate WHERE movieID=?) WHERE movieID=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setInt(1, movieID);
			pstmt.setInt(2, movieID);
			pstmt.executeUpdate();
			
			sql = "SELECT * FROM movie";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------movie------");
			System.out.println("|movieID\t|movieName\t\t\t|releaseYear\t|releaseMonth\t|releaseDate\t|publisherName\t\t\t|avgRate");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				if(rs.getString("movieName").length() < 15) {
					System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\t\t\t|" + rs.getString(3)+ "\t\t|" + rs.getString(4)+ "\t\t|" + rs.getString(5)+ "\t\t|" + rs.getString(6)+ "\t\t|" + rs.getFloat(7) + "\n");
				}
				else if(rs.getString("publisherName").length() > 22) {
					System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\t\t|" + rs.getString(3)+ "\t\t|" + rs.getString(4)+ "\t\t|" + rs.getString(5)+ "\t\t|" + rs.getString(6)+ "\t|" + rs.getFloat(7) + "\n");
				}
				else {
					System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\t\t|" + rs.getString(3)+ "\t\t|" + rs.getString(4)+ "\t\t|" + rs.getString(5)+ "\t\t|" + rs.getString(6)+ "\t\t|" + rs.getFloat(7) + "\n");
				}
			}
			
			System.out.println("\n");
			
		} catch(SQLException e) {
			System.out.println("3.1�� Query error");
			e.printStackTrace();
			return;
		}
		
		try {
			System.out.println("3.2");
			System.out.println("Statement : Bell rates 5 to the moives whose director is \"Tim Burton\"");
			
			int directorID = 0;
			int customerID = 0;
			int movieID = 0;
			
			System.out.println(desc + "SELECT customerID FROM customer WHERE customerName='Bell'");
			sql = "SELECT customerID FROM customer WHERE customerName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Bell");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				customerID = rs.getInt("customerID");
			}
			System.out.println("Bell's ID : " + customerID);
			
			
			System.out.println(desc + "SELECT directorID FROM director WHERE directorName='Tim Burton'");
			sql = "SELECT directorID FROM director WHERE directorName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Tim Burton");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				directorID = rs.getInt("directorID");
			}
			System.out.println("Tim Burton's ID : " + directorID);
			
			System.out.println(desc + "SELECT movieID FROM make WHERE directorID = " + directorID);
			sql = "SELECT movieID FROM make WHERE directorID=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setInt(1, directorID);
			rs = pstmt.executeQuery();
			
			while(rs.next()) {
				movieID = rs.getInt("movieID");
				System.out.println(desc + "INSERT INTO customerRate VALUES (" + customerID + ", " +  movieID + ", 5)");
				sql = "INSERT INTO customerRate VALUES(?, ?, ?)";
				pstmt = conn.prepareStatement(sql);
				pstmt.setInt(1, customerID);
				pstmt.setInt(2, movieID);
				pstmt.setInt(3, 5);
				pstmt.executeUpdate();
			}
			
			sql = "SELECT * FROM customerRate";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			
			System.out.println("------customerRate------");
			System.out.println("|customerID\t|movieID\t|rate");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getInt(2) + "\t\t|" + rs.getString(3) + "\n");
			}
			System.out.println("");
			
			System.out.println(desc + "UPDATE movie M SET avgRate = (SELECT value FROM (SELECT movieID, avg(rate) as value FROM customerRate group by movieID) as R	WHERE M.movieID = R.movieID)");
			sql = "UPDATE movie M SET avgRate = (SELECT value FROM (SELECT movieID, avg(rate) as value FROM customerRate group by movieID) as R	WHERE M.movieID = R.movieID)";
			pstmt = conn.prepareStatement(sql);
			pstmt.executeUpdate();
			
			sql = "SELECT * FROM movie";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------movie------");
			System.out.println("|movieID\t|movieName\t\t\t|releaseYear\t|releaseMonth\t|releaseDate\t|publisherName\t\t\t|avgRate");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				if(rs.getString("movieName").length() < 15) {
					System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\t\t\t|" + rs.getString(3)+ "\t\t|" + rs.getString(4)+ "\t\t|" + rs.getString(5)+ "\t\t|" + rs.getString(6)+ "\t\t|" + rs.getFloat(7) + "\n");
				}
				else if(rs.getString("publisherName").length() > 22) {
					System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\t\t|" + rs.getString(3)+ "\t\t|" + rs.getString(4)+ "\t\t|" + rs.getString(5)+ "\t\t|" + rs.getString(6)+ "\t|" + rs.getFloat(7) + "\n");
				}
				else {
					System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\t\t|" + rs.getString(3)+ "\t\t|" + rs.getString(4)+ "\t\t|" + rs.getString(5)+ "\t\t|" + rs.getString(6)+ "\t\t|" + rs.getFloat(7) + "\n");
				}
			}
			
			System.out.println("\n");
			
		} catch(SQLException e) {
			System.out.println("3.2�� Query error");
			e.printStackTrace();
			return;
		}
		
		try {
			System.out.println("3.3");
			System.out.println("Statement : Jill rates 4 to the movies whose main actor is female");
			int customerID = 0;
			int movieID = 0;
			
			System.out.println(desc + "SELECT customerID FROM customer WHERE customerName='Jill'");
			sql = "SELECT customerID FROM customer WHERE customerName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Jill");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				customerID = rs.getInt("customerID");
			}
			System.out.println("Jill's ID : " + customerID);
			
			System.out.println(desc + "SELECT distinct casting.movieID FROM casting, (SELECT distinct actor.actorID\r\n\t\t\t"
					+ "FROM actor, (SELECT casting.actorID	FROM casting WHERE role=1) as B WHERE gender=0 and actor.actorID = B.actorID) as C WHERE casting.actorID = C.actorID");
			sql = "SELECT distinct casting.movieID FROM casting, (SELECT distinct actor.actorID	FROM actor, (SELECT casting.actorID	FROM casting WHERE role=1) as B WHERE gender=0 and actor.actorID = B.actorID) as C WHERE casting.actorID = C.actorID";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			
			while(rs.next()) {
				movieID = rs.getInt("movieID");
				System.out.println(desc + "INSERT INTO customerRate VALUES (" + customerID + ", " +  movieID + ", 5)");
				sql = "INSERT INTO customerRate VALUES(?, ?, ?)";
				pstmt = conn.prepareStatement(sql);
				pstmt.setInt(1, customerID);
				pstmt.setInt(2, movieID);
				pstmt.setInt(3, 4);
				pstmt.executeUpdate();
			}
			
			sql = "SELECT * FROM customerRate";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			
			System.out.println("------customerRate------");
			System.out.println("|customerID\t|movieID\t|rate");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getInt(2) + "\t\t|" + rs.getString(3) + "\n");
			}
			System.out.println("");
			
			System.out.println(desc + "UPDATE movie M SET avgRate = (SELECT value FROM (SELECT movieID, avg(rate) as value FROM customerRate group by movieID) as R	WHERE M.movieID = R.movieID)");
			sql = "UPDATE movie M SET avgRate = (SELECT value FROM (SELECT movieID, avg(rate) as value FROM customerRate group by movieID) as R	WHERE M.movieID = R.movieID)";
			pstmt = conn.prepareStatement(sql);
			pstmt.executeUpdate();
			
			sql = "SELECT * FROM movie";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------movie------");
			System.out.println("|movieID\t|movieName\t\t\t|releaseYear\t|releaseMonth\t|releaseDate\t|publisherName\t\t\t|avgRate");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				if(rs.getString("movieName").length() < 15) {
					System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\t\t\t|" + rs.getString(3)+ "\t\t|" + rs.getString(4)+ "\t\t|" + rs.getString(5)+ "\t\t|" + rs.getString(6)+ "\t\t|" + rs.getFloat(7) + "\n");
				}
				else if(rs.getString("publisherName").length() > 22) {
					System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\t\t|" + rs.getString(3)+ "\t\t|" + rs.getString(4)+ "\t\t|" + rs.getString(5)+ "\t\t|" + rs.getString(6)+ "\t|" + rs.getFloat(7) + "\n");
				}
				else {
					System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\t\t|" + rs.getString(3)+ "\t\t|" + rs.getString(4)+ "\t\t|" + rs.getString(5)+ "\t\t|" + rs.getString(6)+ "\t\t|" + rs.getFloat(7) + "\n");
				}
			}
			
			System.out.println("\n");
			
		} catch(SQLException e) {
			System.out.println("3.3�� Query error");
			e.printStackTrace();
			return;
		}
		
		try {
			System.out.println("3.4");
			System.out.println("Statement : Jack rates 4 to the fantasy movies");
			int customerID = 0;
			int movieID = 0;
			
			System.out.println(desc + "SELECT customerID FROM customer WHERE customerName='Jack'");
			sql = "SELECT customerID FROM customer WHERE customerName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "Jack");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				customerID = rs.getInt("customerID");
			}
			System.out.println("Jack's ID : " + customerID);
			
			System.out.println(desc + "SELECT movieID FROM movieGenre WHERE genreName='Fantasy'");
			sql = "SELECT movieID FROM movieGenre WHERE genreName='Fantasy'";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			
			while(rs.next()) {
				movieID = rs.getInt("movieID");
				System.out.println(desc + "INSERT INTO customerRate VALUES (" + customerID + ", " +  movieID + ", 5)");
				sql = "INSERT INTO customerRate VALUES(?, ?, ?)";
				pstmt = conn.prepareStatement(sql);
				pstmt.setInt(1, customerID);
				pstmt.setInt(2, movieID);
				pstmt.setInt(3, 4);
				pstmt.executeUpdate();
			}
			
			sql = "SELECT * FROM customerRate";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			
			System.out.println("------customerRate------");
			System.out.println("|customerID\t|movieID\t|rate");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getInt(2) + "\t\t|" + rs.getString(3) + "\n");
			}
			System.out.println("");
			
			System.out.println(desc + "UPDATE movie M SET avgRate = (SELECT value FROM (SELECT movieID, avg(rate) as value FROM customerRate group by movieID) as R	WHERE M.movieID = R.movieID)");
			sql = "UPDATE movie M SET avgRate = (SELECT value FROM (SELECT movieID, avg(rate) as value FROM customerRate group by movieID) as R	WHERE M.movieID = R.movieID)";
			pstmt = conn.prepareStatement(sql);
			pstmt.executeUpdate();
			
			sql = "SELECT * FROM movie";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------movie------");
			System.out.println("|movieID\t|movieName\t\t\t|releaseYear\t|releaseMonth\t|releaseDate\t|publisherName\t\t\t|avgRate");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				if(rs.getString("movieName").length() < 15) {
					System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\t\t\t|" + rs.getString(3)+ "\t\t|" + rs.getString(4)+ "\t\t|" + rs.getString(5)+ "\t\t|" + rs.getString(6)+ "\t\t|" + rs.getFloat(7) + "\n");
				}
				else if(rs.getString("publisherName").length() > 22) {
					System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\t\t|" + rs.getString(3)+ "\t\t|" + rs.getString(4)+ "\t\t|" + rs.getString(5)+ "\t\t|" + rs.getString(6)+ "\t|" + rs.getFloat(7) + "\n");
				}
				else {
					System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\t\t|" + rs.getString(3)+ "\t\t|" + rs.getString(4)+ "\t\t|" + rs.getString(5)+ "\t\t|" + rs.getString(6)+ "\t\t|" + rs.getFloat(7) + "\n");
				}
			}
			
			System.out.println("\n");
			
		} catch(SQLException e) {
			System.out.println("3.4�� Query error");
			e.printStackTrace();
			return;
		}
		
		try {
			System.out.println("3.5");
			System.out.println("Statement : John rates 5 to the movies whose director won the \"Best director\" award");
			
			int customerID = 0;
			int movieID = 0;
			
			System.out.println(desc + "SELECT customerID FROM customer WHERE customerName='John'");
			sql = "SELECT customerID FROM customer WHERE customerName=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "John");
			rs = pstmt.executeQuery();
			if(rs.next()) {
				customerID = rs.getInt("customerID");
			}
			System.out.println("John's ID : " + customerID);
			
			System.out.println(desc + "SELECT movieID FROM make, (SELECT directorID FROM directorObtain, (SELECT awardID FROM award WHERE awardName='Best director')\r\n\t\t\t"
					+ "as best WHERE directorObtain.awardID = best.awardID) as best_director WHERE make.directorID = best_director.directorID");
			sql = "SELECT movieID FROM make, (SELECT directorID FROM directorObtain, (SELECT awardID FROM award WHERE awardName='Best director') as best WHERE directorObtain.awardID = best.awardID) as best_director WHERE make.directorID = best_director.directorID";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			
			while(rs.next()) {
				movieID = rs.getInt("movieID");
				System.out.println(desc + "INSERT INTO customerRate VALUES (" + customerID + ", " +  movieID + ", 5)");
				sql = "INSERT INTO customerRate VALUES(?, ?, ?)";
				pstmt = conn.prepareStatement(sql);
				pstmt.setInt(1, customerID);
				pstmt.setInt(2, movieID);
				pstmt.setInt(3, 5);
				pstmt.executeUpdate();
			}
			
			sql = "SELECT * FROM customerRate";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			
			System.out.println("------customerRate------");
			System.out.println("|customerID\t|movieID\t|rate");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getInt(2) + "\t\t|" + rs.getString(3) + "\n");
			}
			System.out.println("");
			
			System.out.println(desc + "UPDATE movie M SET avgRate = (SELECT value FROM (SELECT movieID, avg(rate) as value FROM customerRate group by movieID) as R	WHERE M.movieID = R.movieID)");
			sql = "UPDATE movie M SET avgRate = (SELECT value FROM (SELECT movieID, avg(rate) as value FROM customerRate group by movieID) as R	WHERE M.movieID = R.movieID)";
			pstmt = conn.prepareStatement(sql);
			pstmt.executeUpdate();
			
			sql = "SELECT * FROM movie";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------movie------");
			System.out.println("|movieID\t|movieName\t\t\t|releaseYear\t|releaseMonth\t|releaseDate\t|publisherName\t\t\t|avgRate");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				if(rs.getString("movieName").length() < 15) {
					System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\t\t\t|" + rs.getString(3)+ "\t\t|" + rs.getString(4)+ "\t\t|" + rs.getString(5)+ "\t\t|" + rs.getString(6)+ "\t\t|" + rs.getFloat(7) + "\n");
				}
				else if(rs.getString("publisherName").length() > 22) {
					System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\t\t|" + rs.getString(3)+ "\t\t|" + rs.getString(4)+ "\t\t|" + rs.getString(5)+ "\t\t|" + rs.getString(6)+ "\t|" + rs.getFloat(7) + "\n");
				}
				else {
					System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\t\t|" + rs.getString(3)+ "\t\t|" + rs.getString(4)+ "\t\t|" + rs.getString(5)+ "\t\t|" + rs.getString(6)+ "\t\t|" + rs.getFloat(7) + "\n");
				}
			}
			
			System.out.println("\n");
			
		} catch(SQLException e) {
			System.out.println("3.5�� Query error");
			e.printStackTrace();
			return;
		}
		
		try {
			System.out.println("4");
			System.out.println("Statement : Select the names of the movies whose actor are dead.");
			String movieName = "";
			
			sql = "SELECT distinct movieName FROM movie, (SELECT movieID FROM casting as C natural join (SELECT actorID FROM actor WHERE dateOfDeath is not null)\r\n\t\t"
					+ " as A) as mov WHERE movie.movieID = mov.movieID";
			System.out.println(desc + sql);
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------result------");
			System.out.println("|movieName");
			System.out.println("-------------------------------------");

			while(rs.next()) {
				movieName = rs.getString("movieName");
				System.out.println("|" + movieName);
			}
			System.out.println("\n");
			
		} catch (SQLException e) {
			System.out.println("4�� Query error");
			e.printStackTrace();
			return;
		}
		
		try {
			System.out.println("5");
			System.out.println("Statement : Select the names of the directors who cast same actor more than once.");
			String directorName = "";
			
			sql = "SELECT distinct directorName FROM\r\n\t\t"
					+ " (SELECT * FROM casting natural join\r\n\t\t"
					+ " (SELECT distinct A.directorID, A.movieID FROM make as A, make as B WHERE A.movieID != B.movieID and A.directorID = B.directorID) as DM\r\n\t\t"
					+ " WHERE casting.movieID = DM.movieID) as LS1, (SELECT * FROM casting natural join\r\n\t\t"
					+ " (SELECT distinct A.directorID, A.movieID FROM make as A, make as B WHERE A.movieID != B.movieID and A.directorID = B.directorID) as DM\r\n\t\t"
					+ " WHERE casting.movieID = DM.movieID) as LS2 natural join director WHERE LS1.movieID != LS2.movieID and LS1.directorID = LS2.directorID and LS1.actorID = LS2.actorID";
			System.out.println(desc + sql);
			
			
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			
			System.out.println("------result------");
			System.out.println("|directorName");
			System.out.println("-------------------------------------");

			while(rs.next()) {
				directorName = rs.getString("directorName");
				System.out.println("|" + directorName);
			}
			System.out.println("\n");
			
		} catch (SQLException e) {
			System.out.println("5�� Query error");
			e.printStackTrace();
			return;
		}
		
		try {
			System.out.println("6");
			System.out.println("Statement : Select the names of the movies and genres, where movies have the common genre.");
			sql = "SELECT genreName FROM (SELECT genreName, COUNT(movieID) as hit FROM movieGenre group by genreName) as genre_per_hit\r\n\t\t"
					+ " WHERE genre_per_hit.hit = (SELECT MAX(hit) as val FROM (SELECT genreName, COUNT(movieID) as hit FROM movieGenre group by genreName) as genre_per_hit2)";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			String genreName = "";
			String movieName = "";
			System.out.println(desc + sql);
			System.out.println("------common genre name (���� ���� �帣 -> ���� ���� ��ȭ�� �� �帣)------");
			System.out.println("|genreName");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				genreName = rs.getString("genreName");
				System.out.println("|" + genreName);
			}
			System.out.println("");
			
			sql = "SELECT genreName, movieName FROM movieGenre natural join movie natural join\r\n\t\t"
					+ " (SELECT genreName FROM (SELECT genreName, COUNT(movieID) as hit FROM movieGenre group by genreName) as genre_per_hit\r\n\t\t"
					+ " WHERE genre_per_hit.hit = (SELECT MAX(hit) as val FROM (SELECT genreName, COUNT(movieID) as hit FROM movieGenre group by genreName) as genre_per_hit2)) as mid";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			
			System.out.println(desc + sql);
			System.out.println("------result------");
			System.out.println("|genreName\t|movieName");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				genreName = rs.getString("genreName");
				movieName = rs.getString("movieName");
				System.out.print("|" + genreName + "\t\t");
				System.out.print("|" + movieName + "\n");
			}
			System.out.println("\n");
		}
		catch(SQLException e) {
			System.out.println("6�� Query error");
			e.printStackTrace();
			return;
		}
		
		try {
			System.out.println("7");
			System.out.println("Statement : Delete the movies which did not get any award(including all directors and actors) and delete data from related tables");
			sql = "DELETE FROM award WHERE not exists (SELECT awardID FROM directorObtain\r\n\t\t"
					+ " WHERE award.awardID = directorObtain.awardID) and\r\n\t\t"
					+ " not exists (SELECT awardID FROM actorObtain WHERE award.awardID = actorObtain.awardID) and\r\n\t\t"
					+ " not exists (SELECT awardID FROM movieObtain WHERE award.awardID = movieObtain.awardID)";
			System.out.println(desc + sql);
			pstmt = conn.prepareStatement(sql);
			pstmt.executeUpdate();
			System.out.println("Update Table");
			
			sql = "SELECT * FROM award";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("------award------");
			System.out.println("|awardID\t|awardName");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\n");
			}
			System.out.println("\n");
			
			
		} catch(SQLException e) {
			System.out.println("7�� Query error");
			e.printStackTrace();
			return;	
		}
		
		try {
			System.out.println("8");
			System.out.println("Statement : Delete all customers and delete data from related tables.");
			sql = "DELETE FROM customerRate";
			System.out.println(desc + sql);
			pstmt = conn.prepareStatement(sql);
			pstmt.executeUpdate();
			
			sql = "SELECT * FROM customerRate";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("Update Table");
			
			System.out.println("------customerRate------");
			System.out.println("|customerID\t|movieID\t|rate");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getInt(2) + "\t\t|" + rs.getString(3) + "\n");
			}
			System.out.println("");

			sql = "UPDATE movie M SET avgRate = (SELECT value FROM (SELECT movieID, avg(rate) as value FROM customerRate group by movieID) as R	WHERE M.movieID = R.movieID)";
			
			System.out.println(desc + sql);
			
			pstmt = conn.prepareStatement(sql);
			pstmt.executeUpdate();
			
			sql = "SELECT * FROM movie";
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			System.out.println("Update Table");
			System.out.println("------movie------");
			System.out.println("|movieID\t|movieName\t\t\t|releaseYear\t|releaseMonth\t|releaseDate\t|publisherName\t\t\t|avgRate");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				if(rs.getString("movieName").length() < 15) {
					System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\t\t\t|" + rs.getString(3)+ "\t\t|" + rs.getString(4)+ "\t\t|" + rs.getString(5)+ "\t\t|" + rs.getString(6)+ "\t\t|" + rs.getFloat(7) + "\n");
				}
				else if(rs.getString("publisherName").length() > 22) {
					System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\t\t|" + rs.getString(3)+ "\t\t|" + rs.getString(4)+ "\t\t|" + rs.getString(5)+ "\t\t|" + rs.getString(6)+ "\t|" + rs.getFloat(7) + "\n");
				}
				else {
					System.out.print("|" + rs.getInt(1) + "\t\t|" + rs.getString(2) + "\t\t|" + rs.getString(3)+ "\t\t|" + rs.getString(4)+ "\t\t|" + rs.getString(5)+ "\t\t|" + rs.getString(6)+ "\t\t|" + rs.getFloat(7) + "\n");
				}
			}
			System.out.println("");
			sql = "DELETE FROM customer";
			System.out.println(desc + sql);
			pstmt = conn.prepareStatement(sql);
			pstmt.executeUpdate();
			
			int customerID = 0;
			String customerName = "";
			String dateOfBirth = "";
			String gender = "";
			int iGender = -1;
			
			System.out.println("Update Table");
			System.out.println("------customer------");
			System.out.println("|customerID\t|customerName\t|dateOfBirth\t|gender");
			System.out.println("-------------------------------------");
			while(rs.next()) {
				customerID = rs.getInt("customerID");
				customerName = rs.getString("customerName");
				dateOfBirth = rs.getString("dateOfBirth");
				iGender = rs.getInt("gender");
				if(iGender == 0) {
					gender = "Female";
				} else if(iGender == 1) {
					gender = "Male";
				}
				System.out.println("|" + customerID + "\t|" + customerName + "\t|" + dateOfBirth + "\t|" + gender + "\n");
			}
			System.out.println("\n");
			
		} catch(SQLException e) {
			System.out.println("8�� Query error");
			e.printStackTrace();
			return;				
		}
		
		try {
			System.out.println("9");
			System.out.println("Statement : Delete all tables and data");
			sql = "DROP TABLE customerRate; DROP TABLE customer;\r\n\t\t"
					+ " DROP TABLE make; DROP TABLE casting; DROP TABLE directorObtain; DROP TABLE actorObtain; DROP TABLE movieObtain; DROP TABLE movieGenre;\r\n\t\t"
					+ " DROP TABLE genre; DROP TABLE award; DROP TABLE movie; DROP TABLE actor; DROP TABLE director;";
			System.out.println(desc + sql);
			pstmt = conn.prepareStatement(sql);
			pstmt.executeUpdate();
			
			System.out.println("��� ���̺� �� ������ ���� �Ϸ�\n");
			
			
		} catch(SQLException e) {
			System.out.println("9�� Query error");
			e.printStackTrace();
			return;	
		}
		
		try {
			if(rs != null) {
				rs.close();
			}
			if(pstmt != null) {
				pstmt.close();
			}
			if(conn != null) {
				conn.close();
			}
		} catch(SQLException e) {
			System.out.println("close error");
			e.printStackTrace();
			return;
		}
		
	}
}