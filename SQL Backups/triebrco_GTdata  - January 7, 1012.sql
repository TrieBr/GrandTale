-- phpMyAdmin SQL Dump
-- version 3.4.9
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jan 07, 2012 at 11:56 PM
-- Server version: 5.1.60
-- PHP Version: 5.2.9

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `triebrco_GTdata`
--

-- --------------------------------------------------------

--
-- Table structure for table `characters`
--

DROP TABLE IF EXISTS `characters`;
CREATE TABLE IF NOT EXISTS `characters` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `userID` int(11) NOT NULL,
  `charName` varchar(255) NOT NULL,
  `mapID` int(11) NOT NULL,
  `x` int(11) NOT NULL,
  `y` int(11) NOT NULL,
  `hairType` int(11) NOT NULL,
  `hairColor` int(11) NOT NULL,
  `facialHairType` int(11) NOT NULL,
  `eyeType` int(11) NOT NULL,
  `mouthType` int(11) NOT NULL,
  `skinColor` int(11) NOT NULL,
  `race` int(11) NOT NULL,
  `gender` int(11) NOT NULL,
  `currentHP` int(11) NOT NULL,
  `maxHP` int(11) NOT NULL,
  `currentMP` int(11) NOT NULL,
  `maxMP` int(11) NOT NULL,
  `container_InventoryEquip` int(11) NOT NULL COMMENT 'ID of a container',
  `container_InventoryUse` int(11) NOT NULL COMMENT 'ID of a container',
  `container_InventoryRegular` int(11) NOT NULL COMMENT 'ID of a container',
  `container_Equipment` int(11) NOT NULL COMMENT 'ID of a container',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=73 ;

--
-- Dumping data for table `characters`
--

INSERT INTO `characters` (`id`, `userID`, `charName`, `mapID`, `x`, `y`, `hairType`, `hairColor`, `facialHairType`, `eyeType`, `mouthType`, `skinColor`, `race`, `gender`, `currentHP`, `maxHP`, `currentMP`, `maxMP`, `container_InventoryEquip`, `container_InventoryUse`, `container_InventoryRegular`, `container_Equipment`) VALUES
(9, 1, 'Seki', 0, 0, 0, 2, 5, 4, 2, 2, 1, 2, 0, 0, 0, 0, 0, 8, 7, 9, 10),
(67, 1, 'Brad', 0, 0, 0, 4, 2, 3, 1, 2, 1, 1, 0, 75, 100, 90, 100, 2, 1, 3, 4),
(70, 4, 'Ethelon', 0, 0, 0, 2, 0, 3, 1, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(69, 4, 'Ethelon', 0, 0, 0, 2, 0, 3, 1, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(72, 1, 'Shura', 0, 0, 0, 2, 7, 0, 1, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `equipment`
--

DROP TABLE IF EXISTS `equipment`;
CREATE TABLE IF NOT EXISTS `equipment` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `characterId` int(11) NOT NULL,
  `equipmentId` int(11) NOT NULL,
  `equipmentType` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=15 ;

--
-- Dumping data for table `equipment`
--

INSERT INTO `equipment` (`id`, `characterId`, `equipmentId`, `equipmentType`) VALUES
(1, 9, 14, 2),
(2, 9, 22, 3),
(3, 9, 21, 4),
(4, 9, 23, 0),
(5, 9, 20, 5),
(6, 9, 19, 6),
(7, 9, 24, 1),
(8, 67, 32, 2),
(9, 67, 0, 0),
(10, 67, 0, 1),
(11, 67, 25, 4),
(12, 67, 27, 5),
(13, 67, 0, 6),
(14, 67, 26, 3);

-- --------------------------------------------------------

--
-- Table structure for table `itemContainer`
--

DROP TABLE IF EXISTS `itemContainer`;
CREATE TABLE IF NOT EXISTS `itemContainer` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `slotCount` int(11) NOT NULL COMMENT 'How many slots this inventory has',
  `itemTypes` int(11) NOT NULL COMMENT 'types of items this inventory holds',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COMMENT='An array of items. ' AUTO_INCREMENT=11 ;

--
-- Dumping data for table `itemContainer`
--

INSERT INTO `itemContainer` (`id`, `slotCount`, `itemTypes`) VALUES
(1, 15, 1),
(2, 15, 2),
(3, 15, 4),
(4, 13, 2),
(7, 15, 1),
(8, 15, 2),
(9, 15, 4),
(10, 13, 2);

-- --------------------------------------------------------

--
-- Table structure for table `itemContainerEntry`
--

DROP TABLE IF EXISTS `itemContainerEntry`;
CREATE TABLE IF NOT EXISTS `itemContainerEntry` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `containerID` int(11) NOT NULL,
  `isCustom` tinyint(1) NOT NULL DEFAULT '0',
  `stackSize` int(11) NOT NULL,
  `itemID` int(11) NOT NULL,
  `slotID` int(11) NOT NULL,
  `customizationID` int(11) NOT NULL,
  `iconID` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

--
-- Dumping data for table `itemContainerEntry`
--

INSERT INTO `itemContainerEntry` (`id`, `containerID`, `isCustom`, `stackSize`, `itemID`, `slotID`, `customizationID`, `iconID`) VALUES
(1, 4, 0, 1, 30, 2, 0, 30),
(2, 1, 0, 1, 3, 2, 0, 3),
(3, 8, 0, 1, 14, 0, 0, 14);

-- --------------------------------------------------------

--
-- Table structure for table `items`
--

DROP TABLE IF EXISTS `items`;
CREATE TABLE IF NOT EXISTS `items` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `type` int(11) NOT NULL,
  `iconID` int(11) NOT NULL DEFAULT '-1',
  `equipType` int(11) NOT NULL,
  `weaponType` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=71 ;

--
-- Dumping data for table `items`
--

INSERT INTO `items` (`id`, `name`, `type`, `iconID`, `equipType`, `weaponType`) VALUES
(1, 'Leather Belt', 2, 1, 0, 0),
(2, 'Leather Gloves', 2, 2, 1, 0),
(3, 'Leather Hat', 2, 3, 2, 0),
(4, 'Leather Shirt', 2, 4, 4, 0),
(5, 'Leather Shoes', 2, 5, 5, 0),
(6, 'Chain Pads', 2, 6, 6, 0),
(7, 'Leather Pants', 2, 7, 3, 0),
(8, 'Ancient Belt', 2, 8, 0, 0),
(9, 'Ancient Glove', 2, 9, 1, 0),
(10, 'Ancient Shirt', 2, 10, 4, 0),
(11, 'Ancient Shoes', 2, 11, 5, 0),
(12, 'Ancient Pads', 2, 12, 6, 0),
(13, 'Ancient Pants', 2, 13, 3, 0),
(14, 'Minstel Hat', 2, 14, 2, 0),
(15, 'Red Demon Mask', 2, 15, 2, 0),
(16, 'Yellow Demon Mask', 2, 16, 2, 0),
(17, 'Blue Demon Mask', 2, 17, 2, 0),
(18, 'Green Demon Mask', 2, 18, 2, 0),
(19, 'Minstel Pads', 2, 19, 6, 0),
(20, 'Minstel Boots', 2, 20, 5, 0),
(21, 'Minstel Shirt', 2, 21, 4, 0),
(22, 'Minstel Pants', 2, 22, 3, 0),
(23, 'Minstel Belt', 2, 23, 0, 0),
(24, 'Minstel Flares', 2, 24, 1, 0),
(25, 'Tattered Gown', 2, 25, 4, 0),
(26, 'Tattered Pants', 2, 26, 3, 0),
(27, 'Ripped Slippers', 2, 27, 5, 0),
(28, 'Red Demonic Bones', 2, 28, 2, 0),
(29, 'Yellow Demonic Bones', 2, 29, 2, 0),
(30, 'Blue Demonic Bones', 2, 30, 2, 0),
(31, 'Green Demonic Bones', 2, 31, 2, 0),
(32, 'Ancient Helm', 2, 32, 2, 0),
(33, 'Ancient Ram Horns', 2, 33, 2, 0),
(34, 'Ancient Hood', 2, 34, 2, 0),
(35, 'Green Apple', 1, 35, 0, 0),
(36, 'Red Apple', 1, 36, 0, 0),
(37, 'Yellow Apple', 1, 37, 0, 0),
(38, 'Slime', 4, 38, 0, 0),
(39, 'Gore', 4, 39, 0, 0),
(40, 'Undead Blood', 4, 40, 0, 0),
(41, 'Basic Red Potion', 1, 41, 0, 0),
(42, 'Basic Blue Potion', 1, 42, 0, 0),
(43, 'Golden Shoe', 2, 43, 5, 0),
(44, 'Golden Belt', 2, 44, 0, 0),
(45, 'Golden Pants', 2, 45, 3, 0),
(46, 'Golden Gauntlets', 2, 46, 1, 0),
(47, 'Novice Dagger', 2, 47, 13, 1),
(48, 'Novice Sword', 2, 48, 13, 2),
(49, 'Novice Small Axe', 2, 49, 13, 3),
(50, 'Novice Throwing Star', 2, 50, 8, 4),
(51, 'Novice Katar', 2, 51, 13, 5),
(52, 'Novice Hammer', 2, 52, 13, 6),
(53, 'Novice Bow', 2, 53, 8, 7),
(54, 'Novice Great Staff', 2, 54, 14, 8),
(55, 'Novice Wand', 2, 55, 8, 9),
(56, 'Novice Long Sword', 2, 56, 14, 2),
(57, 'Novice Great Hammer', 2, 57, 14, 6),
(58, 'Novice Great Axe', 2, 58, 14, 3),
(59, 'Novice Spear', 2, 59, 14, 10),
(60, 'Novice Shield', 2, 60, 7, 11),
(61, 'Azurai''s Gituar', 2, 61, 8, 7),
(62, 'Azurai''s Axe', 2, 62, 13, 3),
(63, 'Ancient Bow', 2, 63, 8, 7),
(64, 'Ancient Mace', 2, 64, 13, 6),
(65, 'Ancient Spear', 2, 65, 13, 10),
(66, 'Golden Sword', 2, 66, 13, 2),
(67, 'Nubius Dagger', 2, 67, 13, 1),
(68, 'Fulcan Shield', 2, 68, 7, 11),
(69, 'Golden Dagger', 2, 69, 13, 1),
(70, 'Golden Mace', 2, 70, 13, 6);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
