-- ============================================================================
-- ตารางระบบล็อกอิน / ไอเทมมอลล์ (ep4_db_auth) + ปลดล็อกเวอร์ชันไคลเอนต์ + ไอดี GM
-- อ้างอิงตรงจากคำสั่ง SQL จริงภายใน LoginServer.exe, Connector.exe, ReZasCashServer.exe
-- ============================================================================

USE `ep4_db_auth`;

CREATE TABLE IF NOT EXISTS `bg_user` (
  `user_code` INT(11) NOT NULL AUTO_INCREMENT,
  `user_id` VARCHAR(64) NOT NULL,
  `passwd` VARCHAR(64) NOT NULL,
  `activated` TINYINT(4) NOT NULL DEFAULT 1,
  `cash` INT(11) NOT NULL DEFAULT 0,
  `jumin` VARCHAR(32) NOT NULL DEFAULT '1234567890123',
  `partner_id` VARCHAR(32) NOT NULL DEFAULT 'TH',
  `create_date` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`user_code`),
  UNIQUE KEY `uk_user_id` (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

CREATE TABLE IF NOT EXISTS `t_users` (
  `a_index` INT(11) NOT NULL AUTO_INCREMENT,
  `a_portal_index` INT(11) NOT NULL,
  `a_idname` VARCHAR(64) NOT NULL,
  `a_enable` TINYINT(4) NOT NULL DEFAULT 1,
  `a_server_num` INT(11) NOT NULL DEFAULT -1,
  `a_subnum` INT(11) NOT NULL DEFAULT -1,
  `a_zone_num` INT(11) NOT NULL DEFAULT -1,
  `a_timestamp` INT(11) NOT NULL DEFAULT 0,
  `a_regi_date` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `a_end_date` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`a_index`),
  KEY `idx_portal` (`a_portal_index`),
  KEY `idx_idname` (`a_idname`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620 COLLATE=tis620_thai_ci;

CREATE TABLE IF NOT EXISTS `t_ip_log` (
  `a_index` INT(11) NOT NULL AUTO_INCREMENT,
  `a_ip` VARCHAR(32) NOT NULL,
  `a_date` DATETIME NOT NULL,
  PRIMARY KEY (`a_index`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620;

CREATE TABLE IF NOT EXISTS `t_ip_block` (
  `a_index` INT(11) NOT NULL AUTO_INCREMENT,
  `a_ip` VARCHAR(32) NOT NULL,
  PRIMARY KEY (`a_index`),
  KEY `idx_ip` (`a_ip`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620;

CREATE TABLE IF NOT EXISTS `t_connect_log` (
  `a_index` INT(11) NOT NULL AUTO_INCREMENT,
  `a_idname` VARCHAR(64) NOT NULL,
  `a_date` DATETIME NOT NULL,
  `a_ip` VARCHAR(32) NOT NULL,
  PRIMARY KEY (`a_index`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620;

CREATE TABLE IF NOT EXISTS `rcslog` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `user_code` INT(11) DEFAULT 0,
  `action` VARCHAR(255) DEFAULT '',
  `created_at` DATETIME DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620;

CREATE TABLE IF NOT EXISTS `t_lacarette_log` (
  `a_user_idx` INT(11) NOT NULL,
  `a_char_idx` INT(11) NOT NULL DEFAULT 0,
  `a_date` DATETIME NOT NULL,
  `a_token` INT(11) NOT NULL DEFAULT 0,
  `a_reg_date` DATETIME NOT NULL,
  PRIMARY KEY (`a_user_idx`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620;

CREATE TABLE IF NOT EXISTS `t_event_gomdori_count` (
  `a_server` INT(11) NOT NULL,
  `a_count` INT(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`a_server`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620;

CREATE TABLE IF NOT EXISTS `t_ranking` (
  `a_server` INT(11) NOT NULL,
  `a_rank` INT(11) NOT NULL,
  `a_charindex` INT(11) NOT NULL,
  `a_date` DATETIME NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=tis620;

CREATE TABLE IF NOT EXISTS `t_gmtool_command` (
  `a_index` INT(11) NOT NULL AUTO_INCREMENT,
  `a_gmindex` INT(11) NOT NULL,
  `a_gmname` VARCHAR(64) NOT NULL,
  `a_date` DATETIME NOT NULL,
  `a_gmcommand` VARCHAR(255) NOT NULL,
  PRIMARY KEY (`a_index`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620;

CREATE TABLE IF NOT EXISTS `t_gmtool_chatmonitor` (
  `a_index` INT(11) NOT NULL AUTO_INCREMENT,
  `a_charindex` INT(11) NOT NULL,
  `a_server` INT(11) NOT NULL,
  `a_subno` INT(11) NOT NULL,
  `a_type` INT(11) NOT NULL,
  `a_chat` VARCHAR(255) NOT NULL,
  `a_date` DATETIME NOT NULL,
  PRIMARY KEY (`a_index`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620;

CREATE TABLE IF NOT EXISTS `t_gmtool_chatting` (
  `a_index` INT(11) NOT NULL AUTO_INCREMENT,
  `a_server` INT(11) NOT NULL,
  `a_sub` INT(11) NOT NULL,
  `a_gmindex` INT(11) NOT NULL,
  `a_gmname` VARCHAR(64) NOT NULL,
  `a_charname` VARCHAR(64) NOT NULL,
  `a_chat` VARCHAR(255) NOT NULL,
  `a_date` DATETIME NOT NULL,
  PRIMARY KEY (`a_index`)
) ENGINE=InnoDB DEFAULT CHARSET=tis620;

-- เพิ่มไอดีทดสอบเริ่มต้น: admin / 1234 (999,999 Cash) และ player1 / 1234 (50,000 Cash)
INSERT IGNORE INTO `bg_user` (`user_code`, `user_id`, `passwd`, `activated`, `cash`) VALUES
  (1, 'admin',   '1234', 1, 999999),
  (2, 'player1', '1234', 1, 50000);

INSERT IGNORE INTO `t_users` (`a_portal_index`, `a_idname`, `a_enable`) VALUES
  (1, 'admin',   1),
  (2, 'player1', 1);

-- ปลดล็อกช่วงเวอร์ชันไคลเอนต์ใน ep4_data.t_clientversion เพื่อให้ไคลเอนต์ THAILIVE ที่คอมไพล์เชื่อมต่อได้ทันที
USE `ep4_data`;
CREATE TABLE IF NOT EXISTS `t_clientversion` (
  `a_min` INT(11) NOT NULL DEFAULT 0,
  `a_max` INT(11) NOT NULL DEFAULT 999999
) ENGINE=InnoDB DEFAULT CHARSET=tis620;

DELETE FROM `t_clientversion`;
INSERT INTO `t_clientversion` (`a_min`, `a_max`) VALUES (0, 999999);
