-- ============================================================================
-- Last Chaos Episode 4 (เซิร์ฟเวอร์ภาษาไทย) - สร้างฐานข้อมูลและตั้งค่าภาษาไทย TIS-620
-- รองรับ MySQL 5.1 / 5.5 / 5.7 และ MariaDB 10.x (แนะนำสำหรับ libmysql.dll 5.1.72)
-- ============================================================================

CREATE DATABASE IF NOT EXISTS `ep4_db_auth` DEFAULT CHARACTER SET tis620 COLLATE tis620_thai_ci;
CREATE DATABASE IF NOT EXISTS `ep4_db`      DEFAULT CHARACTER SET tis620 COLLATE tis620_thai_ci;
CREATE DATABASE IF NOT EXISTS `ep4_data`    DEFAULT CHARACTER SET tis620 COLLATE tis620_thai_ci;
CREATE DATABASE IF NOT EXISTS `ep4_post`    DEFAULT CHARACTER SET tis620 COLLATE tis620_thai_ci;

-- สร้างผู้ใช้เริ่มต้นตรงกับ newStobm.bin และ Billing/Config.RAWR (User=test / Password=123)
-- หมายเหตุ: หากใช้ MySQL 8.0 ขึ้นไป ให้เปลี่ยนเป็น IDENTIFIED WITH mysql_native_password BY '123'
GRANT ALL PRIVILEGES ON `ep4_db_auth`.* TO 'test'@'localhost' IDENTIFIED BY '123';
GRANT ALL PRIVILEGES ON `ep4_db`.*      TO 'test'@'localhost' IDENTIFIED BY '123';
GRANT ALL PRIVILEGES ON `ep4_data`.*    TO 'test'@'localhost' IDENTIFIED BY '123';
GRANT ALL PRIVILEGES ON `ep4_post`.*    TO 'test'@'localhost' IDENTIFIED BY '123';

GRANT ALL PRIVILEGES ON `ep4_db_auth`.* TO 'test'@'127.0.0.1' IDENTIFIED BY '123';
GRANT ALL PRIVILEGES ON `ep4_db`.*      TO 'test'@'127.0.0.1' IDENTIFIED BY '123';
GRANT ALL PRIVILEGES ON `ep4_data`.*    TO 'test'@'127.0.0.1' IDENTIFIED BY '123';
GRANT ALL PRIVILEGES ON `ep4_post`.*    TO 'test'@'127.0.0.1' IDENTIFIED BY '123';

FLUSH PRIVILEGES;
