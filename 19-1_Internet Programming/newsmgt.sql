-- MySQL dump 10.17  Distrib 10.3.15-MariaDB, for Win64 (AMD64)
--
-- Host: localhost    Database: newsmgt
-- ------------------------------------------------------
-- Server version	10.3.15-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `article`
--

DROP TABLE IF EXISTS `article`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `article` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `art_ctgr` varchar(120) NOT NULL,
  `imgName` tinytext DEFAULT NULL,
  `thumb` tinytext DEFAULT NULL,
  `title` tinytext DEFAULT NULL,
  `state` varchar(20) DEFAULT NULL,
  `m_date` date DEFAULT NULL,
  `c_date` date DEFAULT NULL,
  `rep_name` varchar(20) DEFAULT NULL,
  `email` varchar(20) DEFAULT NULL,
  `content` longtext DEFAULT NULL,
  `pv` int(11) DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=38 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `article`
--

LOCK TABLES `article` WRITE;
/*!40000 ALTER TABLE `article` DISABLE KEYS */;
INSERT INTO `article` VALUES (36,'스포츠 - 해외축구','daffy.gif','run.gif','이건','등록완료','2019-06-19','2019-06-10','강 혁','reporter_Email@na.ds','제발요 ㅠㅠ',4),(37,'스포츠 - 해외축구','daffy1.gif','sun2.jpg','article_title','등록완료','2019-06-19','2019-06-10','reporter_name','reporter_Email@na.ds','매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용매우 긴 기사내용',1);
/*!40000 ALTER TABLE `article` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `category`
--

DROP TABLE IF EXISTS `category`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `category` (
  `code` int(11) NOT NULL AUTO_INCREMENT,
  `name_1` varchar(60) DEFAULT NULL,
  `name_2` varchar(60) DEFAULT NULL,
  PRIMARY KEY (`code`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `category`
--

LOCK TABLES `category` WRITE;
/*!40000 ALTER TABLE `category` DISABLE KEYS */;
INSERT INTO `category` VALUES (2,'스포츠','해외축구'),(3,'스포츠','해외야구');
/*!40000 ALTER TABLE `category` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-06-19 19:00:54
