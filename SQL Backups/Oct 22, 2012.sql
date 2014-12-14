-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               5.5.28 - MySQL Community Server (GPL)
-- Server OS:                    Win64
-- HeidiSQL version:             7.0.0.4053
-- Date/time:                    2012-10-22 23:21:51
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET FOREIGN_KEY_CHECKS=0 */;

-- Dumping database structure for triebrco_gtdata
CREATE DATABASE IF NOT EXISTS `triebrco_gtdata` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `triebrco_gtdata`;


-- Dumping structure for table triebrco_gtdata.characters
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
  `currentHP` int(11) NOT NULL DEFAULT '0',
  `maxHP` int(11) NOT NULL DEFAULT '100',
  `currentMP` int(11) NOT NULL DEFAULT '0',
  `maxMP` int(11) NOT NULL DEFAULT '100',
  `faction` int(11) NOT NULL DEFAULT '1',
  `container_InventoryEquip` int(11) NOT NULL COMMENT 'ID of a container',
  `container_InventoryUse` int(11) NOT NULL COMMENT 'ID of a container',
  `container_InventoryRegular` int(11) NOT NULL COMMENT 'ID of a container',
  `container_Equipment` int(11) NOT NULL COMMENT 'ID of a container',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table triebrco_gtdata.characterskills
CREATE TABLE IF NOT EXISTS `characterskills` (
  `id` int(11) NOT NULL DEFAULT '0',
  `characterID` int(11) DEFAULT NULL,
  `skillID` int(11) DEFAULT NULL,
  `skillLevel` int(11) DEFAULT NULL,
  `skillCooldown` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table triebrco_gtdata.itemcontainer
CREATE TABLE IF NOT EXISTS `itemcontainer` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `slotCount` int(11) NOT NULL COMMENT 'How many slots this inventory has',
  `itemTypes` int(11) NOT NULL COMMENT 'types of items this inventory holds',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='An array of items. ';

-- Data exporting was unselected.


-- Dumping structure for table triebrco_gtdata.itemcontainerentry
CREATE TABLE IF NOT EXISTS `itemcontainerentry` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `containerID` int(11) NOT NULL,
  `isCustom` tinyint(1) NOT NULL DEFAULT '0',
  `stackSize` int(11) NOT NULL,
  `itemID` int(11) NOT NULL,
  `slotID` int(11) NOT NULL,
  `customizationID` int(11) NOT NULL,
  `iconID` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table triebrco_gtdata.itemcustomizationdata
CREATE TABLE IF NOT EXISTS `itemcustomizationdata` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `stat_base_str` int(10) NOT NULL DEFAULT '0',
  `stat_bonus_str` int(10) NOT NULL DEFAULT '0',
  `stat_base_dex` int(10) NOT NULL DEFAULT '0',
  `stat_bonus_dex` int(10) NOT NULL DEFAULT '0',
  `stat_base_agi` int(10) NOT NULL DEFAULT '0',
  `stat_bonus_agi` int(10) NOT NULL DEFAULT '0',
  `stat_base_vit` int(10) NOT NULL DEFAULT '0',
  `stat_bonus_vit` int(10) NOT NULL DEFAULT '0',
  `stat_base_luk` int(10) NOT NULL DEFAULT '0',
  `stat_bonus_luk` int(10) NOT NULL DEFAULT '0',
  `stat_base_int` int(10) NOT NULL DEFAULT '0',
  `stat_bonus_int` int(10) NOT NULL DEFAULT '0',
  `stat_base_melee_atk` int(10) NOT NULL DEFAULT '0',
  `stat_bonus_melee_atk` int(10) NOT NULL DEFAULT '0',
  `stat_base_ranged_atk` int(10) NOT NULL DEFAULT '0',
  `stat_bonus_ranged_atk` int(10) NOT NULL DEFAULT '0',
  `stat_base_defence` int(10) NOT NULL DEFAULT '0',
  `stat_bonus_defence` int(10) NOT NULL DEFAULT '0',
  `stat_base_magic_def` int(10) NOT NULL DEFAULT '0',
  `stat_bonus_magic_def` int(10) NOT NULL DEFAULT '0',
  `equip_text` varchar(50) NOT NULL DEFAULT '0',
  `equip_scriptID` int(11) NOT NULL DEFAULT '0',
  `active_text` varchar(50) NOT NULL DEFAULT '0',
  `active_scriptID` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table triebrco_gtdata.items
CREATE TABLE IF NOT EXISTS `items` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `type` int(11) NOT NULL,
  `iconID` int(11) NOT NULL DEFAULT '-1',
  `equipType` int(11) NOT NULL,
  `weaponType` int(11) NOT NULL,
  `classRestriction` int(10) unsigned DEFAULT '4294967295',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table triebrco_gtdata.mobs
CREATE TABLE IF NOT EXISTS `mobs` (
  `id` int(10) NOT NULL DEFAULT '0',
  `name` varchar(50) DEFAULT NULL,
  `level` int(10) DEFAULT NULL,
  `maxHP` int(10) DEFAULT NULL,
  `maxMP` int(10) DEFAULT NULL,
  `element` int(10) DEFAULT NULL,
  `size` int(10) DEFAULT NULL,
  `stat_defence` int(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table triebrco_gtdata.npc
CREATE TABLE IF NOT EXISTS `npc` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(10) NOT NULL DEFAULT '0',
  `level` int(10) DEFAULT '1',
  `hairType` int(10) DEFAULT '1',
  `hairColor` int(10) DEFAULT '1',
  `facialHairType` int(10) DEFAULT '0',
  `eyeType` int(10) DEFAULT '1',
  `mouthType` int(10) DEFAULT '2',
  `skinColor` int(10) DEFAULT '0',
  `race` int(10) DEFAULT '1',
  `gender` int(10) DEFAULT '1',
  `maxHP` int(10) DEFAULT '100',
  `maxMP` int(10) DEFAULT '100',
  `faction` int(10) DEFAULT '1',
  `container_Equipment` int(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table triebrco_gtdata.skills
CREATE TABLE IF NOT EXISTS `skills` (
  `id` int(10) NOT NULL DEFAULT '0',
  `skillName` varchar(50) DEFAULT NULL,
  `skillType` int(10) DEFAULT NULL,
  `iconID` int(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.
/*!40014 SET FOREIGN_KEY_CHECKS=1 */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
